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

void Phylogenetic::loadData(QMap<QString, QList<QVariantList > > sessions,
                            QMap<QString, QList<QList<int> > > indexes,
                            QList<QVariant> species, QList<QVariantList> behavior,
                            int sizeSeq, int sizeIntervals, int sizeStep, bool absolute)
{
    this->behavior = behavior;
    this->sessions = sessions;
    this->indexes = indexes;
    this->species = species;
    this->sizeSeq = sizeSeq;
    this->sizeIntervals = sizeIntervals;
    this->sizeStep = sizeStep;
    this->absolute = absolute;
}

void Phylogenetic::calcData()
{
    int nCols = this->behavior.size();
    int nRows = this->species.size();
    this->MO.clear();this->ME.clear();this->MR.clear();this->MP.clear();
    stats_type st = residue;
    int totalCells = nCols*nRows;
    int counter = 0;
    for(int i=0; i < nRows; i++){
        QString spc = this->species.at(i).toString();
        QList< QVariantList > sessions = this->sessions.value(spc);
        list_behavior s; s.list = sessions;
        QList< QPair<double, double> > tmpMO, tmpME, tmpMR, tmpMP;
        QList< QList<QVariantList> > randomized = this->ramdomize(sessions,this->indexes.value(spc));
        for(int j=0; j < nCols; j++){
            if(this->stopThread){
                emit this->statusProcess(0.0);
                emit this->threadStopped();
                return;
            }
            counter++;
            list_behavior us; us.list.push_back(this->behavior.at(j));
            QPair<double,double> O = this->statsModule->V(us,s,Observed);
            QPair<double,double> E = this->statsModule->V(us,s,Expected);
            QPair<double,double> R = this->statsModule->V(us,s,Residue);
            QList<double> dist;
            for(int r=0; r<randomized.size(); r++){
                list_behavior rand_behavior; rand_behavior.list = randomized.at(r);
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
            double ratio = ((double) counter)/totalCells;
            emit this->statusProcess(ratio);
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

QList< QList<QVariantList> > Phylogenetic::ramdomize(QList<QVariantList> sessions, QList<QList<int> > indexes)
{
    QList< QList<QVariantList> > randomized;
    QSettings s("NuEvo","Pacca");
    s.beginGroup("ConfigAnalysis");
    int nperm = s.value("nPermutation",50).toInt();
    s.endGroup();
    for(int n=0; n<nperm; n++){
      QList<QVariantList> tmp;
      for(int i=0; i < sessions.size(); i++){
          tmp.push_back(this->statsModule->bootstrap(sessions.at(i),indexes.at(i),1).first());
      }
      randomized.push_back(tmp);
    }
    return randomized;
}