#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QApplication *app, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->app = app;
    this->dirConfig = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    if(!QDir(this->dirConfig).exists()) QDir().mkdir(this->dirConfig);
    this->adjustShortcuts();
    this->linkSignals();
    this->createConnections();
    this->users_ui = NULL;
    this->ctl_sessions = NULL;
    this->ctl_species = NULL;
    this->ctl_subjects = NULL;
    this->dict_ui = NULL;
    this->countAnalysis=1;
}

MainWindow::~MainWindow()
{
    if(this->connectdb){
        this->connectdb->closeConnection();
        delete this->connectdb;
    }
    delete ui;
}

void MainWindow::linkSignals(){
    connect(this->ui->actionText,SIGNAL(triggered()),this,SLOT(executeImportText()));
    connect(this->ui->actionVideo,SIGNAL(triggered()),this,SLOT(executeImportVideo()));
    connect(this->ui->actionAudio,SIGNAL(triggered()),this,SLOT(executeImportAudio()));
    connect(this->ui->actionUsuario,SIGNAL(triggered()),this,SLOT(newuser()));
    connect(this->ui->actionReiniciar_Banco,SIGNAL(triggered()),this,SLOT(resetDatabase()));
    connect(this->ui->actionAnalise,SIGNAL(triggered()),this,SLOT(executeAnalysis()));
    connect(this->ui->actionLogin,SIGNAL(triggered()),this,SLOT(login()));
    connect(this->ui->actionDicion_rio,SIGNAL(triggered()),this,SLOT(managerDict()));
    connect(this->ui->actionSess_es,SIGNAL(triggered()),this,SLOT(managerSessions()));
    connect(this->ui->actionSpecies,SIGNAL(triggered()),this,SLOT(managerSpecies()));
    connect(this->ui->actionIndiv_duos,SIGNAL(triggered()),this,SLOT(managerSubjects()));
    connect(this->ui->aboutQt,SIGNAL(triggered()),this,SLOT(aboutQt()));
    connect(this->ui->aboutPacca,SIGNAL(triggered()),this,SLOT(aboutPacca()));
    connect(this->ui->actionIdioma,SIGNAL(triggered()),this,SLOT(changeLanguage()));
    connect(this->ui->actionCascata,SIGNAL(triggered()),this->ui->mdiArea,SLOT(cascadeSubWindows()));
    connect(this->ui->actionLado_a_Lado,SIGNAL(triggered()),this->ui->mdiArea,SLOT(tileSubWindows()));
    connect(this->ui->actionExportODF,SIGNAL(triggered()),this,SLOT(executeExportText()));
    connect(this->ui->actionExportMDF,SIGNAL(triggered()),this,SLOT(executeExportTextMDF()));
}

void MainWindow::adjustShortcuts()
{
    this->ui->actionText->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
    this->ui->actionVideo->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    this->ui->actionAudio->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    this->ui->actionAnalise->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_G));
    this->ui->actionLogin->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_L));
    this->ui->actionDicion_rio->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
    this->ui->actionSess_es->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    this->ui->actionSpecies->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
    this->ui->actionUsuario->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_U));
    this->ui->actionIndiv_duos->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));
}
void MainWindow::saveSession(Sessions session)
{
    Database db;
    db.saveSession(session);
}

void MainWindow::executeImportAdvanced(){
}

void MainWindow::executeImportVideo()
{
    this->executeImportMedia("video");
}

void MainWindow::executeImportAudio()
{
    this->executeImportMedia("audio");
}

void MainWindow::executeImportMedia(QString type)
{
    QString filename = "";
    DialogChooseDict d;
    if(d.exec()){
        QString dict = d.getDictionary();
        filename = QFileDialog::getOpenFileName(this, tr("Escolha o arquivo:"), QDir::homePath());
        if(filename != ""){
            this->ui->menuBar->setEnabled(false);
            this->video_ui = new VideoWindow(type,this->ui->mdiArea);
            connect(this->video_ui,SIGNAL(destroyed(QObject*)),this,SLOT(videowClosed()));
            this->video_ui->setDictionary(dict);
            this->video_ui->setFilename(filename);
            this->ui->mdiArea->addSubWindow(this->video_ui);
            this->video_ui->showMaximized();
        }
    }
}

void MainWindow::executeAnalysis()
{
    this->analysis_ui = new AnalysisWindow(this->ui->mdiArea,countAnalysis,this->ui->mdiArea);
    this->countAnalysis++;
    this->ui->mdiArea->addSubWindow(this->analysis_ui);
    this->analysis_ui->showMaximized();
}

void MainWindow::createConnections()
{
    QSettings settings("NuEvo","Pacca");
    settings.beginGroup("database");
    bool databaseUnconfigured = settings.value("databaseUnconfigured",true).toBool();
    settings.endGroup();
    this->connectDatabse(databaseUnconfigured || !QDir(this->dirConfig).exists("pacca_database.sqlite"));
}

void MainWindow::connectDatabse(bool makeTables)
{
    QString databaseName = this->dirConfig+"/pacca_database.sqlite";
    this->connectdb = new Connections("QSQLITE",databaseName);
    if(!this->connectdb->openConnection()){
        qDebug("Connection error");
    }
    if(makeTables){
        if(this->connectdb->makeDatabaseTables()){
            QSettings settings("NuEvo","Pacca");
            settings.beginGroup("database");
            settings.setValue("databaseUnconfigured",false);
            settings.endGroup();
        }
    }
}

void MainWindow::resetDatabase()
{
    if(QMessageBox::question(this,tr("Reiniciar Banco de Dados"),
                             tr("Você tem certeza que deseja reiniciar o banco de dado?"
                                " Essa ação irá apagar todas as informações do banco!"))
            == QMessageBox::Yes){
        this->ui->mdiArea->closeAllSubWindows();
        this->connectdb->makeDatabaseTables();
    }
}


void MainWindow::executeImportText(bool append /*true is default */){
    DialogChooseSpecie spc;
    if(spc.exec()){
        int specie = spc.getSpecie().toInt();
        int subject = spc.getSubject().toInt();
        /* import from text */
        QStringList filename = QFileDialog::getOpenFileNames(this, tr("Importar análise do arquivo"), QDir::homePath(), tr("Arquivo ODF (*.odf);;Arquivo MDF (*.mdf)"));

        for (int q=0; q<filename.size(); q++){

            QFile id_file(filename.at(q));
            bool candidateToTitle=false;
            QString text;
            QList<QString> title;
            Database db;
            types_of_files type;

            if (!append){
                /* remove all sessions information from memory */
                this->sessions.clear();
            }

            if(!(id_file.open(QIODevice::ReadOnly | QIODevice::Text)))
                return;

            QTextStream file(&id_file);
            file.setAutoDetectUnicode(true);

            QPixmap pixmap(":/icons/splash.png");
            pixmap.scaled(QApplication::desktop()->screenGeometry().width()*0.1,QApplication::desktop()->screenGeometry().height()*0.1);
            QSplashScreen splash(pixmap);
            splash.showMessage(tr("Processando ..."),Qt::AlignBottom | Qt::AlignHCenter	,Qt::darkRed);
            splash.show();
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
                    this->sessions.push_back(Sessions());
                    this->sessions.last().setDateDecoding(QDateTime::currentDateTime());
                    this->sessions.last().setDateSession(QDateTime::currentDateTime());
                    QSettings settings("NuEvo","Pacca");
                    settings.beginGroup("global");
                    this->sessions.last().setDecoder(settings.value("user"));
                    this->sessions.last().setObserver(settings.value("user"));
                    settings.endGroup();
                    this->sessions.last().setDescription(filename.at(q));
                    this->sessions.last().setActions(actions);
                    this->sessions.last().setSpecies(specie);
                    this->sessions.last().setSubject(subject);
                    db.saveSession(this->sessions.last());
                    //                qDebug() << "Session size = " << actions.size();
                }
            }
            //        qDebug() << "Number of sessions = " << this->sessions.size();
            id_file.close();
            splash.finish(this);
        }
        return;
    }
}


void MainWindow::executeExportText(){
    /* Dialog to choose */
    DialogSelectSession d;
    if(d.exec()){
        QList<QTableWidgetItem*> itens = d.getSelectedItens();

        /* file */
        QString path_base = QFileDialog::getSaveFileName(this, tr("Exportar dados em arquivo"), QDir::homePath(), tr("Arquivo ODF (*.odf)"));
        path_base = path_base.remove(path_base.size()-4,4);

        /* Database */
        Database db;

        for(int i=0; i<itens.size(); i=i+6){
            unsigned int idSession = itens.at(i)->text().toInt();
            QString filename = path_base + QString(itens.at(i)->text());
            filename = filename.append(".odf");

            QFile id_file(filename);
            if (!id_file.open(QIODevice::WriteOnly | QIODevice::Text))
                    return;
            QTextStream out(&id_file);


            /* write head to file */
            out << itens.at(i+5)->text() << "\n";

            out << this->identifySession(itens.at(i+2)->text(), itens.at(i+1)->text(),
                                         itens.at(i)->text(), itens.at(i+3)->text());
            out << "\n";

            QStringList list = itens.at(i+4)->text().split(QRegExp("\\s"),QString::SkipEmptyParts);

            out << list.at(0) << "\n";
            out << list.at(1) << "\n";

            out << "{media}\n";
            out << itens.at(i+5)->text() << "\n";

            out << "{indvar}\n";
            out << itens.at(i+2)->text(); // genre
            out << "\n";
            out << itens.at(i+3)->text(); // author
            out << "\n";
            out << itens.at(i+1)->text(); // condition
            out << "\n";

            out << "{start}\n";

            QList<Actions> actions = db.getSequence(idSession);
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
    }
}

void MainWindow::executeExportTextMDF(){
    /* Dialog to choose */
    DialogSelectSession d;
    if(d.exec()){
        QList<QTableWidgetItem*> itens = d.getSelectedItens();

        /* file */
        QString filename = QFileDialog::getSaveFileName(this, tr("Exportar dados em arquivo"), QDir::homePath(), tr("Arquivo MDF (*.mdf)"));

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

        /* Database */
        Database db;

        for(int i=0; i<itens.size(); i=i+6){
            QFileInfo info(itens.at(i+5)->text());
            QString file = info.fileName();

            out.setFieldWidth(15);
            out.setFieldAlignment(QTextStream::AlignLeft);
            out << file;
            out.setFieldWidth(22);
            out << itens.at(i+4)->text();
            out.setFieldWidth(11);
            out.setFieldAlignment(QTextStream::AlignRight);
            out << "999.9";
            out.reset();
            out << " sec ";
            out << this->identifySession(itens.at(i+2)->text(), itens.at(i+1)->text(),
                                         itens.at(i)->text(), itens.at(i+3)->text());
            out << "\n";
        }

        for(int i=0; i<itens.size(); i=i+6){
            QFileInfo info(itens.at(i+5)->text());
            QString file = info.fileName();

            /* head to analysis */
            out.reset();
            out << "\nObservational data file .....: "
                << file
                << "\n";

            out << "Title .......................: "
                << this->identifySession(itens.at(i+2)->text(),
                                         itens.at(i+1)->text(),
                                         itens.at(i)->text(),
                                         itens.at(i+3)->text())
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

            unsigned int idSession = itens.at(i)->text().toInt();
            QList<Actions> actions = db.getSequence(idSession);
            for (int j=0; j<actions.size(); j++){
                out.reset();
                out.setFieldWidth(10);
                out.setFieldAlignment(QTextStream::AlignRight);
                out << actions[j].getTimeAction();
                out.reset();
                out << " " << actions[j].getEvent().getDescription();

                if (actions[j].getState().getDescription().size()>0){
                    out << "," << actions[j].getState().getDescription();
                }

                out << "\n";
            }

            if (actions.size()-1>0){
                if (!actions[actions.size()-1].getEvent().getDescription().endsWith("{end}")){
                    out.setFieldWidth(10);
                    out.setFieldAlignment(QTextStream::AlignRight);
                    out << actions[actions.size()-1].getTimeAction();
                    out.reset();
                    out << " " << "{end}\n";
                }
            }
            out << "\n";
        }


        id_file.close();

    }
}

QString MainWindow::identifySession(QString specie, QString individuo, QString id, QString author){
    return specie + " " + individuo + " " + id + " " + author;
}

void MainWindow::login()
{
    DialogLogin login;
    if(login.exec()){
        QString username = login.getName();
        QSettings settings("NuEvo","Pacca");
        settings.beginGroup("global");
        settings.setValue("user",username);
        settings.endGroup();
        this->ui->menuNova->setEnabled(true);
        this->ui->menuSess_o->setEnabled(true);
        this->ui->actionSess_es->setEnabled(true);
    }
}

void MainWindow::newuser()
{
    if(this->users_ui  == NULL){
        this->users_ui = new ControlUsers(this->ui->mdiArea);
        connect(this->users_ui,SIGNAL(destroyed(QObject*)),this,SLOT(usersClosed()));
        this->users_ui->setWindowModality(Qt::ApplicationModal);
        this->swUser = this->ui->mdiArea->addSubWindow(this->users_ui);
    }
    this->users_ui->show();
    this->ui->mdiArea->setActiveSubWindow(this->swUser);
}

void MainWindow::managerDict()
{
    if(this->dict_ui == NULL){
        this->dict_ui = new ControlDictionary(this->ui->mdiArea);
        connect(this->dict_ui,SIGNAL(destroyed(QObject*)),this,SLOT(dictClosed()));
        this->dict_ui->setWindowModality(Qt::ApplicationModal);
        this->swDict = this->ui->mdiArea->addSubWindow(this->dict_ui);
    }
    this->dict_ui->show();
    this->ui->mdiArea->setActiveSubWindow(this->swDict);
}

void MainWindow::managerSessions()
{
    if(this->ctl_sessions == NULL){
        this->ctl_sessions = new ControlSessions(this->ui->mdiArea);
        connect(this->ctl_sessions,SIGNAL(destroyed(QObject*)),this,SLOT(sessionsClosed()));
        this->ctl_sessions->setWindowModality(Qt::ApplicationModal);
        this->swSsn = this->ui->mdiArea->addSubWindow(this->ctl_sessions);
    }
    this->ctl_sessions->show();
    this->ui->mdiArea->setActiveSubWindow(this->swSsn);
}

void MainWindow::managerSpecies()
{
    if(this->ctl_species == NULL){
        this->ctl_species = new ControlSpecies(this->ui->mdiArea);
        connect(this->ctl_species,SIGNAL(destroyed(QObject*)),this,SLOT(speciesClosed()));
        this->ctl_species->setWindowModality(Qt::ApplicationModal);
        this->swSpc = this->ui->mdiArea->addSubWindow(this->ctl_species);
    }
    this->ctl_species->show();
    this->ui->mdiArea->setActiveSubWindow(this->swSpc);
}

void MainWindow::managerSubjects()
{
    if(this->ctl_subjects == NULL){
        this->ctl_subjects = new ControlSubjects(this->ui->mdiArea);
        connect(this->ctl_subjects,SIGNAL(destroyed(QObject*)),this,SLOT(subjectsClosed()));
        this->ctl_subjects->setWindowModality(Qt::ApplicationModal);
        this->swSpc = this->ui->mdiArea->addSubWindow(this->ctl_subjects);
    }
    this->ctl_subjects->show();
    this->ui->mdiArea->setActiveSubWindow(this->swSpc);
}

void MainWindow::dictClosed()
{
    this->dict_ui = NULL;
}

void MainWindow::sessionsClosed()
{
    this->ctl_sessions = NULL;
}

void MainWindow::speciesClosed()
{
    this->ctl_species = NULL;
}

void MainWindow::subjectsClosed()
{
    this->ctl_subjects = NULL;
}

void MainWindow::usersClosed()
{
    this->users_ui = NULL;
}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this,tr("Sobre o Qt"));
}

void MainWindow::aboutPacca()
{
    QMessageBox::about(this,tr("Sobre o Pacca"),
                       tr("O aplicativo PACCA visa o estudo do comportamento, entendido como uma rede de ações sequenciais de um indivíduo, "
                          "ou de interações entre indivíduos. Ele permite a detecção de significância estatística em rotinas comportamentais "
                          "específicas (ou conjuntos de rotinas com alguns aspectos em comum), típicas de um indivíduo, de uma população, "
                          "ou de uma espécie, a depender do esquema amostral do estudo.\n\n"
                          "O aplicativo é fruto do trabalho de uma equipe que envolve desenvolvedores (Alex Santana e Luiz Gavaza) e "
                          "estatísticos (Lucas Santana Souza), sob a coordenação de Hilton Ferreira Japyassú, como parte do projeto "
                          "INOMEP (Integrando Níveis de Organização em Modelos Ecológicos Preditivos), coordenado por Charbel Niño El-Hani, e "
                          "financiado pelo CNPq e pela FAPESB, no âmbito do Programa de Apoio a Núcleos de Excelência (PRONEX)."));
}

void MainWindow::changeLanguage()
{
    DialogChooseLanguage d;
    d.includeMenssage(tr("O novo idioma só está disponível após reiniciar a aplicação."));
    if(d.exec()){
        QString lang = d.getLanguage();
        QSettings settings("NuEvo","Pacca");
        settings.beginGroup("global");
        settings.setValue("language",lang);
        settings.endGroup();
    }
}

void MainWindow::videowClosed()
{
    this->ui->menuBar->setEnabled(true);
    this->ui->mdiArea->setFocus();
    disconnect(this->video_ui,SIGNAL(destroyed(QObject*)),this,SLOT(videowClosed()));
}
