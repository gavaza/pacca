#include "phylogenetic.h"

Phylogenetic::Phylogenetic()
{
    this->statsModule = NULL;
    this->stopThread = false;
}

Phylogenetic::~Phylogenetic()
{
    delete this->statsModule;
}

void Phylogenetic::setBehavior(QList<list_behavior> behavior){
    this->behavior = behavior;
}

void Phylogenetic::loadData(QMap<QString, StatisticMap > sessions,
                            QList<QVariant> species, QList<list_behavior> behavior,
                            int sizeSeq, int sizeIntervals, int sizeStep, bool absolute)
{
    this->behavior.clear();
    this->sessions.clear();
    this->species.clear();

    this->behavior = behavior;
    this->sessions = sessions;
    this->species = species;
    this->sizeSeq = sizeSeq;
    this->sizeIntervals = sizeIntervals;
    this->sizeStep = sizeStep;
    this->observedType = Probability;
    if(absolute) this->observedType = Observed;
    if(this->statsModule != NULL) delete this->statsModule;
    this->statsModule = new Statistics(this->dynamic,absolute,this->sizeStep,this->sizeIntervals);
}

void Phylogenetic::calcData()
{
    int nCols = this->behavior.size();
    int nRows = this->species.size();
    this->MO.clear();this->ME.clear();this->MR.clear();this->MP.clear();this->MFs.clear();
    stats_type st = residue;
    int totalCells = nCols*nRows;
    int counter = 0;
    for(int i=0; i < nRows; i++){ //For each specie
        QString spc = this->species.at(i).toString(); //get the specie SPC
        StatisticMap sessions = this->sessions.value(spc); //getting all sessions of SPC
        StatisticMap s = sessions;
        QList< QPair<double, double> > tmpMO, tmpME, tmpMR, tmpMP;
        QList< StatisticMap > randomized = this->randomize(sessions); //ramdomizing the lists
        for(int j=0; j < nCols; j++){ //for each behavior (the permutation of events) eg. all diades
            if(this->stopThread){ //control of thread
                emit this->statusProcess(0.0);
                emit this->statusProcessLabel(tr("Abortado"));
                emit this->threadStopped();
                return;
            }
            counter++;
            list_behavior us = this->behavior.at(j); //getting a specific behavior US
            QPair<double,double> O = this->statsModule->V(this->statsModule->V_Map(us,s,this->observedType)); //calc Observed of US on the sessions of SPC
            QPair<double,double> E = this->statsModule->V(this->statsModule->V_Map(us,s,Expected)); //calc Expected of US on the sessions of SPC
            QPair<double,double> R = this->statsModule->V(this->statsModule->V_Map(us,s,Residue)); //calc Residue of US on the sessions of SPC
            QList<double> dist;
            //for each random list, calculating the statistic (Observed, Expected or Residue) to create a distribution.
            for(int r=0; r<randomized.size(); r++){
                StatisticMap rand_behavior; rand_behavior = randomized[r];
                switch (st) {
                case observed:
                    dist.push_back(this->statsModule->V(this->statsModule->V_Map(us,rand_behavior,this->observedType)).first);
                    break;
                case expected:
                    dist.push_back(this->statsModule->V(this->statsModule->V_Map(us,rand_behavior,Expected)).first);
                    break;
                case residue:
                    dist.push_back(this->statsModule->V(this->statsModule->V_Map(us,rand_behavior,Residue)).first);
                    break;
                default:
                    break;
                }
            }
            //with the distribution calculating the p-value.
            switch (st) {
            case observed:
                tmpMP.push_back(this->statsModule->pvalue(O.first,dist));
                break;
            case expected:
                tmpMP.push_back(this->statsModule->pvalue(E.first,dist));
                break;
            case residue:
                tmpMP.push_back(this->statsModule->pvalue(R.first,dist));
                break;
            default:
                break;
            }
            //giving feedback about the progress
            double ratio = ((double) counter)/totalCells;
            emit this->statusProcess(ratio);
            QString label = QString::number(ratio*100,'f',2)+"% - "+tr("Analisando: ")+spc;
            emit this->statusProcessLabel(label);
            //saving the data
            tmpMO.push_back(O);
            tmpME.push_back(E);
            tmpMR.push_back(R);
        }
        this->MO.push_back(tmpMO);
        this->ME.push_back(tmpME);
        this->MR.push_back(tmpMR);
        this->MP.push_back(tmpMP);
    }
    this->MFs = this->getSignificantPhylogenetic(this->MR);
    emit dataProcessed();
    emit this->statusProcessLabel(tr("Finalizado!"));
}

void Phylogenetic::run()
{
    this->stopThread = false;
    this->calcData();
}

bool Phylogenetic::getStopThreadStatus()
{
    return this->stopThread;
}

void Phylogenetic::setStopThreadStatus(bool stop)
{
    this->stopThread = stop;
}

QList<QList<QPair<double, double> > > Phylogenetic::getMO()
{
    return this->MO;
}

QList<QList<QPair<double, double> > > Phylogenetic::getME()
{
    return this->ME;
}

QList<QList<QPair<double, double> > > Phylogenetic::getMR()
{
    return this->MR;
}

QList<QList< QPair<double, double> > > Phylogenetic::getMP()
{
    return this->MP;
}

QList<QList<significant_type> > Phylogenetic::getMFs()
{
    return this->MFs;
}

QList<QVariant> Phylogenetic::getSpecies()
{
    return this->species;
}

QList<list_behavior> Phylogenetic::getBehaviors()
{
    return this->behavior;
}

void Phylogenetic::setSpecies(QList<QVariant> species){
    this->species = species;
}

void Phylogenetic::saveFile(QString filename)
{
    if(filename != ""){
        char f = 'g';
        int precision = 5;
        QMap<int,QString> sheets;
        sheets.insert(0,tr("Matriz Observados"));
        sheets.insert(1,tr("Matriz Esperados"));
        sheets.insert(2,tr("Matriz Resíduos"));
        sheets.insert(3,tr("Matriz P-Valor"));
        sheets.insert(4,tr("Matriz MFs"));
        QXlsx::Document xlsx;
        QMapIterator<int,QString> sh(sheets);
        while(sh.hasNext()){
            sh.next();
            xlsx.insertSheet(sh.key(),sh.value());
        }

        int nCols = this->behavior.size();
        int nRows = this->species.size();
        for(int i=0; i < nCols; i++){
            int sizeSeq = behavior.at(i).size();
            QString s;
            for(int j=0; j < sizeSeq; j++){
                s.append("{");s.append(behavior.at(i).at(j).first().toString());s.append("}");
            }
            for(int j=0; j < nRows; j++){
                QMapIterator<int,QString> sh(sheets);
                while(sh.hasNext()){
                    sh.next();
                    QString sheetName = sh.value();
                    int sheetNumber = sh.key();
                    xlsx.selectSheet(sheetName);
                    xlsx.write(1,2+i,s);
                    if(i==0) xlsx.write(2+j,1,this->species.at(j).toString());
                    QString content;
                    switch (sheetNumber) {
                    case 0:{
                        content=QString::number(this->MO.at(j).at(i).first,f,precision); content+=" ( ";
                        content+=QString::number(this->MO.at(j).at(i).second,f,precision); content+=" ) ";
                        break;
                    }
                    case 1:{
                        content=QString::number(this->ME.at(j).at(i).first,f,precision); content+=" ( ";
                        content+=QString::number(this->ME.at(j).at(i).second,f,precision); content+=" ) ";
                        break;
                    }
                    case 2:{
                        content=QString::number(this->MR.at(j).at(i).first,f,precision); content+=" ( ";
                        content+=QString::number(this->MR.at(j).at(i).second,f,precision); content+=" ) ";
                        break;
                    }
                    case 3:{
                        double pv = qMin(this->MP.at(j).at(i).first,this->MP.at(j).at(i).second);
                        content=QString::number(pv);
                        break;
                    }
                    case 4:{
                        content=QString::number(this->MFs.at(j).at(i));
                        break;
                    }
                    default:
                        break;
                    }
                    xlsx.write(2+j,2+i,content);
                }
            }
        }
        xlsx.saveAs(filename);
    }
}

QList<StatisticMap> Phylogenetic::randomize(StatisticMap sessions)
{
    QList< StatisticMap > randomized;
    QSettings s("NuEvo","Pacca");
    s.beginGroup("ConfigAnalysis");
    int nperm = s.value("nPermutation",50).toInt();
    s.endGroup();
    QMapIterator<int,QVariantList> j(sessions);
    QList< QList<int> > indexes;
    while(j.hasNext()){
        j.next();
        int size = j.value().size();
        QList<int> idx;
        for(int n=0; n < size; n++) idx.push_back(n);
        indexes.push_back(idx);
    }
    for(int n=0; n<nperm; n++){
        StatisticMap tmp;
        randomized.push_back(tmp);
    }
    unsigned int idx = 0;
    QMapIterator<int,QVariantList> i(sessions);
    while(i.hasNext()){
        i.next();
        QVariantList session = i.value();
        QList<QVariantList> r = this->statsModule->bootstrap(session,indexes.at(idx),nperm);
        for(int n=0; n<nperm; n++)
            randomized[n].insertMulti(i.key(),r.at(n));
        idx++;
    }
    return randomized;
}

QList< QList<significant_type> > Phylogenetic::getSignificantPhylogenetic(QList<QList<QPair<double, double> > > statistcs)
{
    QList< QList<significant_type> > result;
    QSettings s("NuEvo","Pacca");
    s.beginGroup("ConfigAnalysis");
    double alpha = s.value("alfa",5).toDouble();
    s.endGroup();

    for (int i=0; i<statistcs.size(); i++){
        QList<significant_type> tmp;
        for(int j=0; j<statistcs.at(i).size(); j++){
            /* mudar para ZERO as caselas que tiverem, em MP, valores não significativos (Pvalor especificado pelo usuário) */
            double pv = qMin(this->MP.at(i).at(j).first,this->MP.at(i).at(j).first);
            if (pv > alpha){
                tmp.push_back(insignificant);
            }
            else if (statistcs.at(i).at(j).first >= 0){
                tmp.push_back(positive_significant);
            }
            else{
                tmp.push_back(negative_significant);
            }
        }
        result.push_back(tmp);
    }
    return result;
}
