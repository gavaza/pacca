#include "statistics.h"
#include <iostream>

Statistics::Statistics(bool dynamic, bool absolute, int stepSize, int stepStart){
    this->dynamic = dynamic;
    this->absolute = absolute;
    this->stepSize = stepSize;
    this->stepStart = stepStart-1;
}

Statistics::~Statistics()
{
}

void Statistics::run()
{
    switch (this->typeRun) {
    case 'P':
        this->calcPermutation();
        break;
    default:
        break;
    }
}

void Statistics::setTypeRun(char typeRun)
{
    this->typeRun = typeRun;
}

void Statistics::setSessions(list_behavior sessions, QList<int> sessionsSubjects)
{
    this->sessions = sessions;
    this->sessionsSubjects = sessionsSubjects;
}

void Statistics::setSequences(QList<list_behavior> sequences)
{
    this->sequences = sequences;
}

void Statistics::setPermutationList(QList<list_behavior> permutation_list)
{
    this->permutation_list = permutation_list;
}

void Statistics::setPermutationSize(int nPermutations)
{
    this->nPermutations = nPermutations;
}

int Statistics::getPermutationSize(){
    return this->nPermutations;
}

void Statistics::setEvents(QList<QVariantList> events)
{
    this->events = events;
}

void Statistics::setIndexes(QList< QList<int> > indexes)
{
    this->indexes = indexes;
}

QList<QVector<QString> > Statistics::getLabels()
{
    return this->sessionsLabels;
}

QVector<QString> Statistics::getLabels(int i)
{
    return this->sessionsLabels.at(i);
}

QVector<QString> Statistics::getInfos(int i)
{
    return this->infos.at(i);
}

QList<QVector<QString> > Statistics::getInfos()
{
    return this->infos;
}

QVector<double> Statistics::getTicks()
{
    return this->sessionsTicks;
}

void Statistics::setTailedAlpha(int tailed, double alpha)
{
    this->tailed = tailed;
    this->alpha = alpha;
}

void Statistics::setFilterPvalue(bool filter)
{
    this->filterPvalue = filter;
}

QList<double> Statistics::getE(int i)
{
    return this->dataE.at(i);
}

QList<double> Statistics::getO(int i)
{
    return this->dataO.at(i);
}

QList<double> Statistics::getR(int i)
{
    return this->dataR.at(i);
}

QMap<int, QPair<double, double> > Statistics::getVE(int i)
{
    return this->VE.at(i);
}

QMap<int, QPair<double, double> > Statistics::getVO(int i)
{
    return this->VO.at(i);
}

QMap<int, QPair<double, double> > Statistics::getVR(int i)
{
    return this->VR.at(i);
}

QList<QPair<double, double> > Statistics::getP(int i)
{
    return this->dataP.at(i);
}

list_behavior Statistics::getUs(int i){
    return this->set_us.at(i);
}

QList<list_behavior> Statistics::getUs(){
    return this->set_us;
}

QList<QList<double> > Statistics::getE(){
    return this->dataE;
}

QList<QList<double> > Statistics::getR(){
    return this->dataR;
}

QList<QList<double> > Statistics::getO(){
    return this->dataO;
}

QList<QMap<int, QPair<double,double> > > Statistics::getVE(){
    return this->VE;
}

QList<QMap<int, QPair<double,double> > > Statistics::getVO(){
    return this->VO;
}

QList<QMap<int, QPair<double,double> > > Statistics::getVR(){
    return this->VR;
}

QList<QList<QPair<double, double> > > Statistics::getP()
{
    return this->dataP;
}

bool Statistics::getFilterPvalue()
{
    return this->filterPvalue;
}

bool Statistics::getStopThreadStatus()
{
    return this->stopThread;
}

void Statistics::setStopThreadStatus(bool stop)
{
    this->stopThread = stop;
}

QMap<QVariant, int> Statistics::frequence(QVariantList list)
{
    QMap<QVariant, int> freq;
    for(int i = 0; i < list.size(); i++){
        if(freq.contains(list.at(i))){
            freq[list.at(i)]++;
        }
        else{
            freq.insert(list.at(i),1);
        }
    }
    return freq;
}

QMap<QVariant, int> Statistics::frequence(QVariantList list, int nbars)
{
    QMap<QVariant, int> freq;
    QMap<int,QVariant> map;
    double max = 0;
    double min = 0;
    for(int i = 0; i < list.size(); i++){
        double v = list.at(i).toDouble();
        if(i==0){
            max = v;
            min = v;
        } else {
            if(max < v) max = v;
            if(min > v) min = v;
        }
    }\

    double inc = (max-min)/nbars;
    double current = min;
    //    qDebug() << "INC = " << inc;
    for(int m = 0; m < nbars; m++){
        //        qDebug() << m << " " << current;
        map.insert(m,current);
        freq.insert(current,0);
        current+=inc;
    }
    //    qDebug() << "MAP: " << map;
    for(int i = 0; i < list.size(); i++){
        int idx = round((list.at(i).toDouble() - min)/inc);
        //        qDebug() << "Value: " << list.at(i).toDouble() << " | idx: " << idx << " | " << map[idx] << " | " << map.contains(idx);
        QVariant key = map[idx];
        freq[key]++;
    }
    return freq;
}

// investigated = position
// behavior = one
double Statistics::P(QVariantList u,
                     QVariantList behavior){
    if (u.contains("*")) return 1;
    double Pu = 0;
    double n = behavior.size();
    for (int i=0; i<u.size(); i++){
        Pu += (double)behavior.count(u[i])/n;
    }
    return Pu;
}

// investigated = position
// behavior = multiple
double Statistics::P(QVariantList u,
                     list_behavior behavior){
    if (u.contains("*")) return 1;
    double Pu = 0;
    for (int i=0; i<u.size(); i++){
        int n = 0;
        double p = 0;
        for(int b=0; b<behavior.size(); b++){
            p+= behavior.at(b).count(u.at(i));
            n+= behavior.at(b).size();
        }
        Pu+=p/n;
    }
    return Pu;
}

// investigated = one
// behavior = one
double Statistics::P(list_behavior u, QVariantList behavior){
    return this->O(u, behavior)/this->elements(u.size(),behavior.size());
}

// investigated = one
// behavior = multiple
QList<double> Statistics::P(list_behavior u, list_behavior behavior){
    QList<double> Pu;
    for (int i=0; i<behavior.size(); i++){
        int n = this->elements(u.size(),behavior.at(i).size());
        Pu.push_back(this->O(u,behavior.at(i))/n);
    }
    return Pu;
}

// investigated = one
// behavior = one
double Statistics::E(list_behavior u,
                     QVariantList behavior){
    double Eu = 1.0;
    for (int i=0; i<u.size(); i++){
        Eu *= this->P(u.at(i), behavior);
    }
    if (this->absolute){
        Eu *= behavior.size();
    }
    return Eu;
}

// investigated = one
// behavior = multiple
QList<double> Statistics::E(list_behavior u, list_behavior behavior){
    QList<double> Eu;
    for (int i=0; i<behavior.size(); i++){
        Eu.push_back(this->E(u,behavior.at(i)));
    }
    return Eu;
}

// investigated = one
// behavior = multiple
// WHAT : expected in the all list of behaviors
double Statistics::E_all(list_behavior u, list_behavior behavior)
{
    double Eu = 1.0;
    int n = 0;

    for (int i=0; i<u.size(); i++){
        Eu *= this->P(u.at(i), behavior);
    }

    if (this->absolute){
        for (int i=0; i<behavior.size(); i++){
            n += behavior.at(i).size();
        }
        Eu *= n;
    }

    return Eu;

}

// investigated = one
// behavior = one
double Statistics::R(list_behavior u, QVariantList behavior){
    double E = this->E(u, behavior);
    if (absolute){
        return (this->O(u, behavior) - E);
    }
    else{
        return (this->P(u, behavior) - E);
    }
}

// investigated = one
// behavior = multiple
QList<double> Statistics::R(list_behavior u, list_behavior behavior){
    QList<double> Ru;
    for (int i=0; i<behavior.size(); i++){
        Ru.push_back(this->R(u, behavior.at(i)));
    }
    return Ru;
}

// investigated = one
// behavior = species
double Statistics::R_unnamed(list_behavior u, StatisticMap behavior){
    QPair<double,double> Ra;
    Ra = this->V(u,behavior,Residue);
    return Ra.first/sqrt(Ra.second/behavior.size());
}

// investigated = one
// behavior = multiple
double Statistics::R_all(list_behavior u, list_behavior behavior)
{
    double E = this->E_all(u, behavior);
    if (this->absolute){
        return (this->O_all(u, behavior) - E);
    }
    else{
        return (this->P_all(u, behavior) - E);
    }
}

// investigated = size of investigated
// behavior = size of behavior
unsigned int Statistics::elements(int size_u, int size_behavior){
    unsigned int n=0;
    for (int l=this->stepStart; l<=(size_behavior-size_u); l+=this->stepSize){
        n++;
    }
    return n;
}

// investigated = one
// behavior = one
double Statistics::O(list_behavior u, QVariantList behavior){
    int qw = behavior.size();
    int k = u.size();
    QVariantList last_found;
    int last_found_indx;
    double freq = 0;
    for (int l=this->stepStart; l<=(qw-k); l+=this->stepSize){
        bool founded = true;
        for(int j=0; j < k; j++){
            if((!u[j].contains(behavior[l+j])) && (!u[j].contains("*"))){
                founded = false;
                break;
            }
        }
        if (founded){
//            std::cout << "found in l = " << l << std::endl;
            if (this->dynamic){
                QVariantList new_found;
                for(int i=0; i<k; i++){
                    new_found.push_back(behavior[l+i]);
                }
                if ((last_found.size() == 0) || (l >= last_found_indx+k)){
                    last_found_indx = l;
                    last_found = new_found;
                    freq++;
                }
                else{
                    bool repeat_test = true;
                    for (int i=0; i<last_found.size(); i++){
                        if (last_found.at(i) != new_found.at(i)){
                            repeat_test = false;
                            break;
                        }
                    }
                    if (!repeat_test){
                        last_found_indx = l;
                        last_found = new_found;
                        freq++;
                    }
                }
            }
            else{
                freq++;
            }
        }
    }
    return freq;
}

// investigated = one
// behavior = multiple
QList<double> Statistics::O(list_behavior u, list_behavior behavior){
    QList<double> freq;
    int w = behavior.size();
    for (int i=0; i<w; i++){
        freq.push_back(this->O(u, behavior.at(i)));
    }
    return freq;
}

// investigated = one
// behavior = multiple
// WHAT : sum of all observed in the all list of behaviors
double Statistics::O_all(list_behavior u, list_behavior behavior){
    int w = behavior.size();
    double freq = 0;
    for (int i=0; i<w; i++){
        freq += this->O(u, behavior[i]);
    }
    return freq;
}

// investigated = one
// behavior = multiple
// WHAT : probability in the all lists of behaviors
double Statistics::P_all(list_behavior u, list_behavior behavior){
    int w = behavior.size();
    QPair<double,double> freq(0,0);
    for (int i=0; i<w; i++){
        freq.first += this->O(u, behavior[i]);
        freq.second += behavior[i].size()-u.size()+1;
    }
    return freq.first/freq.second;

}

QPair<double,double> Statistics::V(QList<double> list){
    double mean = 0;
    double EV = 0;
    double q = list.size();
    QPair<double,double> pair(0,-1);
    for (int p=0; p<q; p++){
        mean += list.at(p);
    }
    mean /= q;
    pair.first = mean;
    if (q>1){
        for (int p=0; p<q; p++){
            EV += ((list[p] - mean)*(list[p] - mean))/(q-1);
        }
        pair.second = EV;
    }
    return pair;
}

QPair<double, double> Statistics::V(QVariantList list)
{
    double mean = 0;
    double EV = 0;
    double q = list.size();
    QPair<double,double> pair(0,-1);
    for (int p=0; p<q; p++){
        mean += list.at(p).toDouble();
    }
    mean /= q;
    pair.first = mean;
    if (q>1){
        for (int p=0; p<q; p++){
            EV += qPow(list.at(p).toDouble() - mean, 2)/(q-1);
        }

        pair.second = EV;
    }
    return pair;
}

QPair<double,double> Statistics::pvalue(double value, QList<double> distribution)
{
    double sample;
    int greater = 0;
    int lower = 0;
    foreach (sample, distribution) {
        if(value >= sample) lower++;
        else greater++;
    }
    QPair<double,double> result;
    int totalElements = distribution.size();
    result.first = ((double) lower)/totalElements;
    result.second = ((double) greater)/totalElements;
    return result;
}

QList< QPair<double,double> > Statistics::pvalue(QList<double> values, QList<double> distribution)
{
    QList< QPair<double,double> > pvalues;
    double v;
    foreach (v, values) {
        pvalues.push_back(this->pvalue(v,distribution));
    }
    return pvalues;
}


QMap<int, QPair<double,double> > Statistics::V_Map(list_behavior u, StatisticMap behavior,
                                   enum types_of_variances type){
    QMap<int, QPair<double, double> > Mcalc;
    QList<int> keys = behavior.uniqueKeys();
    QListIterator<int> i(keys);

    while (i.hasNext()){
        list_behavior subject_behavior;
        int key = i.next();
        StatisticMap::const_iterator j = behavior.find(key);

        while (j != behavior.end() && j.key() == key) {
            subject_behavior.push_back(j.value());
            j++;
        }

        QList<double> sample;

        if (type==Residue){
            sample = this->R(u,subject_behavior);
        }
        else if (type==Observed){
            sample = this->O(u,subject_behavior);
        }
        else if (type==Expected){
            sample = this->E(u,subject_behavior);
        }
        else if (type==Probability){
            sample = this->P(u,subject_behavior);
        }
        QPair<double,double> result = V(sample);
        Mcalc.insert(key,result);

    }
    return Mcalc;
}

QPair<double, double> Statistics::V(QMap<int, QPair<double, double> > M){
    QList<QPair<double, double> > Mcalc = M.values();
    QList<double> sample;
    for (int i=0; i<Mcalc.size(); i++){
        sample.push_back(Mcalc.at(i).first);
    }
    return this->V(sample);
}

QPair<double, double> Statistics::V(list_behavior u, StatisticMap behavior,
                                   enum types_of_variances type){
    QMap<int, QPair<double, double> > Mcalc_map = this->V_Map(u,behavior,type);
    QList<QPair<double, double> > Mcalc = Mcalc_map.values();
    QList<double> sample;
    for (int i=0; i<Mcalc.size(); i++){
        sample.push_back(Mcalc.at(i).first);
    }
    return this->V(sample);
}

QList<QVariantList> Statistics::bootstrap(QVariantList events, int nsamples)
{
    QSettings s("NuEvo","Pacca");
    s.beginGroup("ConfigAnalysis");
    int seed = s.value("seed",-1).toInt();
    s.endGroup();
    if(seed == -1) seed = QTime::currentTime().msecsSinceStartOfDay();
    srand(seed);
    QList<int> indexes;
    for(int n=0; n < events.size(); n++) indexes.push_back(n);
    int sizeSequence = indexes.size();
    QList< QVariantList > bootstrap_list;
    for(int n=0; n < nsamples; n++){
        QList<int> tmp = indexes;
        QVariantList sample;
        for(int i=0; i < sizeSequence; i++){
            int sorted = rand() % tmp.size();
            sample.push_back(events.at(tmp.at(sorted)));
            tmp.removeAt(sorted);
        }
        bootstrap_list.push_back(sample);
    }
    return bootstrap_list;
}

QList<QVariantList> Statistics::bootstrap(QVariantList events, QList<int> indexes, int nsamples)
{
    QSettings s("NuEvo","Pacca");
    s.beginGroup("ConfigAnalysis");
    int seed = s.value("seed",-1).toInt();
    s.endGroup();
    if(seed == -1) seed = QTime::currentTime().msecsSinceStartOfDay();
    srand(seed);
    int sizeSequence = indexes.size();
    QList< QVariantList > bootstrap_list;
    for(int n=0; n < nsamples; n++){
        QList<int> tmp = indexes;
        QVariantList sample;
        for(int i=0; i < sizeSequence; i++){
            int sorted = rand() % tmp.size();
            sample.push_back(events.at(tmp.at(sorted)));
            tmp.removeAt(sorted);
        }
        bootstrap_list.push_back(sample);
    }
    return bootstrap_list;
}

void Statistics::calcPermutation()
{
    if(sessions.size() > 0 && permutation_list.size() > 0){
        this->stopThread = false;
        this->sessionsLabels.clear();
        this->infos.clear();
        this->sessionsTicks.clear();
        this->dataE.clear();
        this->dataO.clear();
        this->dataR.clear();
        this->dataP.clear();
        this->VE.clear();
        this->VO.clear();
        this->VR.clear();
        this->set_us.clear();

        int totalSessions = sessions.size();
        QList<StatisticMap> distributions;
        StatisticMap behaivors;

        for(int d=0; d < this->nPermutations; d++){
            StatisticMap tmp;
            distributions.push_back(tmp);
        }
        for(int s=0; s < totalSessions; s++){
            list_behavior bootstrap_list = this->bootstrap(this->events.at(s),this->nPermutations);
            int subject = this->sessionsSubjects.at(s);
            behaivors.insertMulti(subject,this->sessions.at(s));
            for(int p=0; p < this->nPermutations; p++){
                distributions[p].insertMulti(subject,bootstrap_list.at(p));
            }
        }
        int totalPermutations = this->permutation_list.size();
        QVector<QString> sessionsLabels;
        QVector<QString> infos;
        for(int s=0; s < totalPermutations; s++){
            list_behavior set_us;
            QString info;
            if(this->stopThread){
                emit this->statusProcess(0.0);
                emit this->threadStopped();
                return;
            }
            set_us = this->permutation_list.at(s);
            this->set_us.push_back(set_us); // keep set_us
            for(int idu=0; idu<this->permutation_list.at(s).size(); idu++){
                info.append(this->permutation_list.at(s).at(idu).first().toString()); info.append(", ");
            }            
            this->dataE.push_back(this->E(set_us,behaivors.values()));
            if (this->absolute){
                this->dataO.push_back(this->O(set_us,behaivors.values()));
            }
            else{
                this->dataO.push_back(this->P(set_us,behaivors.values()));
            }
            this->dataR.push_back(this->R(set_us,behaivors.values()));


            QList<double> rand_dist;
            for(int d=0; d < this->nPermutations; d++){
                rand_dist.push_back(this->V(set_us,distributions.at(d),Residue).first);
            }

            QList<QPair<double,double> > P_value = this->pvalue(this->dataR.last(),rand_dist);
            this->dataP.push_back(P_value);

            sessionsLabels.push_back("P:"+QString::number(s));
            int tick = this->sessionsLabels.size();
            this->sessionsTicks.push_back(tick);
            infos.push_back(info);

            this->VE.push_back(this->V_Map(set_us,behaivors,Expected));
            if (this->absolute){
                this->VO.push_back(this->V_Map(set_us,behaivors,Observed));
            }
            else{
                this->VO.push_back(this->V_Map(set_us,behaivors,Probability));
            }
            this->VR.push_back(this->V_Map(set_us,behaivors,Residue));

            QPair<double, double> E_all = this->V(this->VE.last());
            QPair<double, double> O_all = this->V(this->VO.last());
            QPair<double, double> R_all = this->V(this->VR.last());
            sessionsTicks.push_front(1);
            this->VE.last().insertMulti(-1,E_all);
            this->VO.last().insertMulti(-1,O_all);
            this->VR.last().insertMulti(-1,R_all);

            double ratio = ((double) s)/totalPermutations;
            emit this->statusProcess(ratio);
        }

        this->sessionsLabels.push_back(sessionsLabels);
        this->infos.push_back(infos);
        emit this->dataProcessed();
    }
}

void Statistics::updateAbsolute(bool absolute){
    this->absolute = absolute;
}

void Statistics::updateDynamic(bool dynamic){
    this->dynamic = dynamic;
}

void Statistics::updateStepStart(int stepStart){
    this->stepStart = stepStart;
}

void Statistics::updateStepSize(int stepSize){
    this->stepSize = stepSize;
}
