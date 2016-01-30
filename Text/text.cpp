#include "text.h"


Text::Text()
{
}

QList<Sessions> Text::executeImportText(QStringList filename){
    QList<Sessions> sessions;
    for (int q=0; q<filename.size(); q++){
        QFile id_file(filename.at(q));
        bool candidateToTitle=false;
        QString text;
        QList<QString> title;
        types_of_files type;

        if(!(id_file.open(QIODevice::ReadOnly | QIODevice::Text)))
            return sessions;

        QTextStream file(&id_file);
        file.setAutoDetectUnicode(true);

        /* verify */
        //            QPixmap pixmap(":/icons/splash.png");
        //            pixmap.scaled(QApplication::desktop()->screenGeometry().width()*0.1,QApplication::desktop()->screenGeometry().height()*0.1);
        //            QSplashScreen splash(pixmap);
        //            splash.showMessage(tr("Processando ..."),Qt::AlignBottom | Qt::AlignHCenter	,Qt::darkRed);
        //            splash.show();

        while (!file.atEnd()){

            type = unknown;

            /* seek beginning of session */
            do{
                text = file.readLine();

                /* candidate to title information from simple file */
                if (candidateToTitle){
                    title = text.split(QRegExp("\\s"));
                    candidateToTitle=false;
                }

                if (text.contains(QRegExp("\\.CNF")))
                    candidateToTitle = true;

            }while(!file.atEnd() && !text.startsWith("{indvar}") && !text.startsWith("{start}") && !text.startsWith("Observational data file"));


            if (!file.atEnd()){

                bool tagEnd = false;
                bool readhead = false;
                QStringList list;
                double time = 0;
                QString description;
                QString state_description;
                QString session_author;
                int i;

                QList<Actions> actions;

                while(!file.atEnd() && !tagEnd){

                    if (text.startsWith("Observational data file")){
                        type=mdf;
                    }
                    else if (text.startsWith("{indvar}") || text.startsWith("{start}")){
                        type=odf;
                    }

                    i=0;

                    /* read head */
                    if (!file.atEnd() && !readhead){
                        readhead = true;
                        if (type==odf){
                            if (text.startsWith("{indvar}")){
                                /* not processed yet */
                                do{
                                    text = file.readLine();
                                } while(!file.atEnd() && !text.startsWith("{start}"));
                            }
                            if (text.startsWith("{start}")){
                                /* sessions title information from simple file. */
                                text = "Title";
                                if (title.size() >= TITLE_SESSION_SIZE_SIMPLE){
                                    session_author = title[title.size()-2];
                                }
                                else{
                                    /* incomplete title information */
                                }
                            }
                        }
                        else if(type==mdf){
                            text = file.readLine();
                            if (text.startsWith("Title")){
                                /* analysis title information from complex file. */
                                title = text.simplified().split(QRegExp("\\s"),QString::SkipEmptyParts);
                                if (title.size() >= TITLE_SESSION_SIZE_COMPLEX){
                                    session_author = title[title.size()-2];
                                }
                                else{
                                    /* incomplete title information */
                                }
                            }
                            do{
                                text = file.readLine();
                            }while(!file.atEnd() && !text.contains("-----"));
                        }
                    }

                    /* search for information analysis: title or time, event [,state] */
                    if (!file.atEnd()){
                        do{
                            text = file.readLine();
                            list = text.simplified().split(QRegExp("\\s"),QString::SkipEmptyParts);
                            i = 0;
                            //                            while (i<list.size() && !list[i].contains(QRegExp("\\d*\\.\\d+"))){
                            while (i<list.size() && !list[i].contains(QRegExp("\\d+"))){
                                i++;
                            }
                        } while (!file.atEnd() && i==list.size());
                    }

                    /* apply information to fields */
                    if (i+1<list.size()){
                        /* time, event [, state] found or end tag */
                        time = list.at(i).toDouble();
                        description = list.at(i+1);
                        if (description.endsWith("{end}")){
                            /* end tag found, go to new session if exist */
                            tagEnd = true;
                        }
                        else{
                            list = description.simplified().split(QRegExp(","),QString::SkipEmptyParts);
                            state_description = "";
                            if (list.size()>0){
                                description = list.at(0);
                                if (list.size()==2) {
                                    /* state is explicitly defined */
                                    state_description = list.at(1);
                                    if(state_description.at(list.at(i).size()-1) == ','){
                                        state_description = state_description.remove(list.at(i).size()-1,1);
                                    }
                                }
                                if(description.at(list.at(i).size()-1) == ','){
                                    description = description.remove(list.at(i).size()-1,1);
                                }
                            }
                        }
                        actions.push_back(Actions(time, Events(description), States(state_description)));
                        //                            qDebug() << "(time, event, state) = " << time << description << state_description;
                    }
                }
                sessions.push_back(Sessions());
                sessions.last().setDateDecoding(QDateTime::currentDateTime());
                sessions.last().setDateSession(QDateTime::currentDateTime());
                sessions.last().setDescription(filename.at(q));
                sessions.last().setActions(actions);

                //                qDebug() << "Session size = " << actions.size();
            }
        }
        //        qDebug() << "Number of sessions = " << this->sessions.size();
        id_file.close();
        //            splash.finish(this);
    }
    return sessions;
}

void Text::executeExportText(QString filename, QList<Actions> actions, QList<QString> infos){

    QFile id_file(filename);
    if (!id_file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&id_file);


    /* write head to file */
    out << infos.at(5) << "\n";

    out << this->identifySession(infos.at(2), infos.at(1),
                                 infos.at(0), infos.at(3));
    out << "\n";

    QStringList list = infos.at(4).split(QRegExp("\\s"),QString::SkipEmptyParts);

    out << list.at(0) << "\n";
    out << list.at(1) << "\n";

    out << "{media}\n";
    out << infos.at(5) << "\n";

    out << "{indvar}\n";
    out << infos.at(2); // genre
    out << "\n";
    out << infos.at(3); // author
    out << "\n";
    out << infos.at(1); // condition
    out << "\n";

    out << "{start}\n";

    for (int j=0; j<actions.size(); j++){
        out << actions[j].getTimeAction() << " " << actions[j].getEvent().getDescription();

        if (actions[j].getState().getDescription().size()>0){
            out << "," << actions[j].getState().getDescription();
        }

        out << "\n";
    }
    if (actions.size()-1>0){
        if (!actions[actions.size()-1].getEvent().getDescription().endsWith("{end}")){
            out << actions[actions.size()-1].getTimeAction() << " " << "{end}\n";
        }
    }
    out << "{notes}\n";
    id_file.close();
}

void Text::executeExportTextMDF(QString filename, QList< QList<Actions> > list_actions, QList< QList<QString> > list_infos){


    QFile id_file(filename);
    if (!id_file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&id_file);

    /* write head to file */

    out << "+----------------------------------------------------------------+\n";
    out << "|       Pacca 1.0  TIME-EVENT TABLE         "
        << QDateTime::currentDateTime().toString("MM-dd-yyyy  hh:mm:ss") <<" |\n";
    out << "+----------------------------------------------------------------+\n";

    out << "\n";
    out << "Project .....: " << "\n";
    out << "Configuration: " << "\n";
    out << "\n";

    out << "Selected Observational Data Files:\n";
    out << "File name      Date       Start time  Total duration Title\n";
    out << "----------------------------------------------------------\n";

    for (int i=0; i<list_actions.size(); i++){


        QFileInfo info(list_infos.at(i).at(5));
        QString file = info.fileName();

        out.setFieldWidth(15);
        out.setFieldAlignment(QTextStream::AlignLeft);
        out << file;
        out.setFieldWidth(22);
        out << list_infos.at(i).at(4);
        out.setFieldWidth(11);
        out.setFieldAlignment(QTextStream::AlignRight);
        out << "999.9";
        out.reset();
        out << " sec ";
        out << this->identifySession(list_infos.at(i).at(2), list_infos.at(i).at(1),
                                     list_infos.at(i).at(0), list_infos.at(i).at(3));
        out << "\n";
    }

    for (int i=0; i<list_actions.size(); i++){

        QFileInfo info(list_infos.at(i).at(5));
        QString file = info.fileName();

        /* head to analysis */
        out.reset();
        out << "\nObservational data file .....: "
            << file
            << "\n";

        out << "Title .......................: "
            << this->identifySession(list_infos.at(i).at(2),
                                     list_infos.at(i).at(1),
                                     list_infos.at(i).at(0),
                                     list_infos.at(i).at(3))
            << "\n";

        out << "From ........................: "
            << "Start of observation"
            << "\n";

        out << "To ..........................: "
            << "End of observation"
            << "\n";

        out << "\n"
            << "      Time Captura\n"
            << "  -----------------\n";


        for (int j=0; j<list_actions.at(i).size(); j++){
            out.reset();
            out.setFieldWidth(10);
            out.setFieldAlignment(QTextStream::AlignRight);
            out << list_actions[i][j].getTimeAction();
            out.reset();
            out << " " << list_actions[i][j].getEvent().getDescription();

            if (list_actions[i][j].getState().getDescription().size()>0){
                out << "," << list_actions[i][j].getState().getDescription();
            }

            out << "\n";
        }

        if (list_actions.at(i).size()-1>0){
            if (!list_actions[i][list_actions.at(i).size()-1].getEvent().getDescription().endsWith("{end}")){
                out.setFieldWidth(10);
                out.setFieldAlignment(QTextStream::AlignRight);
                out << list_actions[i][list_actions.at(i).size()-1].getTimeAction();
                out.reset();
                out << " " << "{end}\n";
            }
        }
        out << "\n";
    }

    id_file.close();

}

QString Text::identifySession(QString specie, QString individuo, QString id, QString author){
    return specie + " " + individuo + " " + id + " " + author;
}
