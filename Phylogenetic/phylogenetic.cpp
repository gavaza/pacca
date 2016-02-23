#include "phylogenetic.h"

Phylogenetic::Phylogenetic()
{
    this->statsModule = new Statistics(this->dynamic,this->absolute,this->sizeStep,this->sizeIntervals);
    this->stopThread = false;
}

Phylogenetic::~Phylogenetic()
{
    delete this->statsModule;
}

void Phylogenetic::setBehavior(QList<QVariantList> behavior){
    this->behavior = behavior;
}

void Phylogenetic::loadData(QMap<QString, StatisticMap > sessions,
                            QList<QVariant> species, QList<QVariantList> behavior,
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
    this->absolute = absolute;
    delete this->statsModule;
    this->statsModule = new Statistics(this->dynamic,this->absolute,this->sizeStep,this->sizeIntervals);
}

void Phylogenetic::calcData()
{
    int nCols = this->behavior.size();
    int nRows = this->species.size();
    this->MO.clear();this->ME.clear();this->MR.clear();this->MP.clear();
    stats_type st = residue;
    int totalCells = nCols*nRows;
    int counter = 0;
    for(int i=0; i < nRows; i++){ //For each specie
        QString spc = this->species.at(i).toString(); //get the specie SPC
        StatisticMap sessions = this->sessions.value(spc); //getting all sessions of SPC
        StatisticMap s = sessions;
        QList< QPair<double, double> > tmpMO, tmpME, tmpMR, tmpMP;
        QList< StatisticMap > randomized = this->randomize2(sessions); //ramdomizing the lists
        for(int j=0; j < nCols; j++){ //for each behavior (the permutation of events) eg. all diades
            if(this->stopThread){ //control of thread
                emit this->statusProcess(0.0);
                emit this->statusProcessLabel(tr("Abortado"));
                emit this->threadStopped();
                return;
            }
            counter++;
            list_behavior us; us.push_back(this->behavior.at(j)); //getting a specific behavior US
            QPair<double,double> O = this->statsModule->V(us,s,Observed); //calc Observed of US on the sessions of SPC
            QPair<double,double> E = this->statsModule->V(us,s,Expected); //calc Expected of US on the sessions of SPC
            QPair<double,double> R = this->statsModule->V(us,s,Residue); //calc Residue of US on the sessions of SPC
            QList<double> dist;
            //for each random list, calculating the statistic (Observed, Expected or Residue) to create a distribution.
            for(int r=0; r<randomized.size(); r++){
                StatisticMap rand_behavior; rand_behavior = randomized[r];
                switch (st) {
                case observed:
                    dist.push_back(this->statsModule->V(us,rand_behavior,Observed).first);
                    break;
                case expected:
                    dist.push_back(this->statsModule->V(us,rand_behavior,Expected).first);
                    break;
                case residue:
                    dist.push_back(this->statsModule->V(us,rand_behavior,Residue).first);
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

QList<QVariant> Phylogenetic::getSpecies()
{
    return this->species;
}

QList<QVariantList> Phylogenetic::getBehaviors()
{
    return this->behavior;
}

void Phylogenetic::setSpecies(QList<QVariant> species){
    this->species = species;
}

QList<StatisticMap> Phylogenetic::randomize(StatisticMap sessions)
{
    QList< StatisticMap > randomized;
    QSettings s("NuEvo","Pacca");
    s.beginGroup("ConfigAnalysis");
    int nperm = s.value("nPermutation",50).toInt();
    s.endGroup();
    QMapIterator<int,QVariantList> i(sessions);
    QList< QList<int> > indexes;
    while(i.hasNext()){
        i.next();
        QVariantList session = i.value();
        QList<int> idx;
        for(int n=0; n < session.size(); n++) idx.push_back(n);
        indexes.push_back(idx);
    }
    for(int n=0; n<nperm; n++){
        StatisticMap tmp;
        unsigned int idx = 0;
        QMapIterator<int,QVariantList> i(sessions);
        while(i.hasNext()){
            i.next();
            QVariantList session = i.value();
            QVariantList r = this->statsModule->bootstrap(session,indexes.at(idx),1).first();
            tmp.insertMulti(i.key(),r);
            idx++;
        }
        randomized.push_back(tmp);
    }
    return randomized;
}

QList<StatisticMap> Phylogenetic::randomize2(StatisticMap sessions)
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
