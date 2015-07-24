#include "statistics.h"
#include <iostream>

Statistics::Statistics(bool dynamic, bool absolute, int stepSize, int stepStart){
    this->dynamic = dynamic;
    this->absolute = absolute;
    this->stepSize = stepSize;
    this->stepStart = stepStart;
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

void Statistics::setSessions(QList<list_behavior> sessions)
{
    this->sessions = sessions;
}

void Statistics::setSequences(QList<list_behavior> sequences)
{
    this->sequences = sequences;
}

void Statistics::setPermutationList(QList<QVariantList> permutation_list)
{
    this->permutation_list = permutation_list;
}

void Statistics::setPermutationSize(int nPermutations)
{
    this->nPermutations = nPermutations;
}

void Statistics::setEvents(QList<QVariantList> events)
{
    this->events = events;
}

void Statistics::setIndexes(QList< QList<int> > indexes)
{
    this->indexes = indexes;
}

QVector<QString> Statistics::getLabels()
{
    return this->sessionsLabels;
}

QVector<QString> Statistics::getInfos()
{
    return this->infos;
}

QVector<double> Statistics::getTicks()
{
    return this->sessionsTicks;
}

//void Statistics::setStepSize(int stepSize)
//{
//    this->stepSize = stepSize;
//}

void Statistics::setTailedAlpha(int tailed, double alpha)
{
    this->tailed = tailed;
    this->alpha = alpha;
}

void Statistics::setFilterPvalue(bool filter)
{
    this->filterPvalue = filter;
}

QList<double> Statistics::getE()
{
    return this->dataE;
}

QList<double> Statistics::getO()
{
    return this->dataO;
}

QList<double> Statistics::getR()
{
    return this->dataR;
}

QList<QPair<double, double> > Statistics::getP()
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
    double Pu = 0;
    for (int i=0; i<u.size(); i++){
        int n = 0;
        double p = 0;
        for(int b=0; b<behavior.list.size(); b++){
            p+= behavior.list.at(b).count(u.at(i));
            n+= behavior.list.at(b).size();
        }
        Pu+=p/n;
    }
    return Pu;
}

// investigated = one
// behavior = one
double Statistics::P(list_behavior u, QVariantList behavior){
    return this->O(u, behavior)/this->elements(u.list.size(),behavior.size());
}

// investigated = one
// behavior = multiple
QList<double> Statistics::P(list_behavior u, list_behavior behavior){
    QList<double> Pu;
    for (int i=0; i<behavior.list.size(); i++){
        int n = this->elements(u.list.size(),behavior.list.at(i).size());
        Pu.push_back(this->O(u,behavior.list.at(i))/n);
    }
    return Pu;
}

// investigated = one
// behavior = one
double Statistics::E(list_behavior u,
                     QVariantList behavior){
    double Eu = 1.0;
    for (int i=0; i<u.list.size(); i++){
        Eu *= this->P(u.list.at(i), behavior);
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
    for (int i=0; i<behavior.list.size(); i++){
        Eu.push_back(this->E(u,behavior.list.at(i)));
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

    for (int i=0; i<u.list.size(); i++){
        Eu *= this->P(u.list.at(i), behavior);
    }

    if (this->absolute){
        for (int i=0; i<behavior.list.size(); i++){
            n += behavior.list.at(i).size();
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
    for (int i=0; i<behavior.list.size(); i++){
        Ru.push_back(this->R(u, behavior.list.at(i)));
    }
    return Ru;
}

// investigated = one
// behavior = species
double Statistics::R_unnamed(list_behavior u, QMap<int, list_behavior> behavior){
    QPair<double,double> Ra;
    Ra = this->V(u,behavior,Residue);
    return Ra.first/sqrt(Ra.second/behavior.size());
}

// investigated = one
// behavior = multiple
// for convenince
double Statistics::R_unnamed(list_behavior u, list_behavior behavior){
    QMap<int, list_behavior> tmp;
    tmp.insert(0,behavior);
    return this->R_unnamed(u,tmp);
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
    int k = u.list.size();
    QVariantList last_found;
    int last_found_indx;
    double freq = 0;
    for (int l=this->stepStart; l<=(qw-k); l+=this->stepSize){
        bool founded = true;
        for(int j=0; j < k; j++){
            if((!u.list[j].contains(behavior[l+j])) && (!u.list[j].contains("*"))){
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
    int w = behavior.list.size();
    for (int i=0; i<w; i++){
        freq.push_back(this->O(u, behavior.list.at(i)));
    }
    return freq;
}

// investigated = one
// behavior = multiple
// WHAT : sum of all observed in the all list of behaviors
double Statistics::O_all(list_behavior u, list_behavior behavior){
    int w = behavior.list.size();
    double freq = 0;
    for (int i=0; i<w; i++){
        freq += this->O(u, behavior.list[i]);
    }
    return freq;
}

// investigated = one
// behavior = multiple
// WHAT : probability in the all lists of behaviors
double Statistics::P_all(list_behavior u, list_behavior behavior){
    int w = behavior.list.size();
    QPair<double,double> freq(0,0);
    for (int i=0; i<w; i++){
        freq.first += this->O(u, behavior.list[i]);
        freq.second += behavior.list[i].size()-u.list.size()+1;
    }
    return freq.first/freq.second;

}

QPair<double,double> Statistics::V(QList<double> list){
    double mean = 0;
    double EV = 0;
    double q = list.size();
    QPair<double,double> pair(-1,0);
    for (int p=0; p<q; p++){
        mean += list.at(p);
    }
    mean /= q;
    pair.first = mean;
    if (q>1){
        for (int p=0; p<q; p++){
            EV += (list[p] - mean)*(list[p] - mean)/(q-1);
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
    QPair<double,double> pair(-1,0);
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


QPair<double,double> Statistics::V(list_behavior u, QMap<int, list_behavior> behavior,
                                   enum types_of_variances type){
    QList<double> sample;
    QList<double> Mcalc;
    QMapIterator<int, list_behavior> i(behavior);

    while (i.hasNext()){
        i.next();

        if (type==Residue){
            sample = this->R(u,i.value());
        }
        else if (type==Observed){
            sample = this->O(u,i.value());
        }
        else if (type==Expected){
            sample = this->E(u,i.value());
        }
        else if (type==Probability){
            sample = this->P(u,i.value());
        }
        Mcalc.push_back(this->V(sample).first);
    }
    return this->V(Mcalc);
}


// for convenince
QPair<double,double> Statistics::V(list_behavior u, list_behavior behavior,
                                   enum types_of_variances type){
    QMap<int,list_behavior> tmp;
    tmp.insert(0,behavior);
    return this->V(u,tmp,type);
}

QList<QVariantList> Statistics::bootstrap(QVariantList events, QList<int> indexes, int nsamples)
{
    QSettings s("NuEvo","Pacca");
    s.beginGroup("ConfigAnalysis");
    int seed = s.value("seed",-1).toInt();
    s.endGroup();
    if(seed == -1) seed = QTime::currentTime().msecsSinceStartOfDay();
    srand(seed);
    QList< QVariantList > bootstrap_list;
    for(int n=0; n < nsamples; n++){
        QList<int> tmp = indexes;
        QVariantList sample;
        int sizeSequence = indexes.size();
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

        int totalSessions = sessions.at(0).list.size();
        // TODO : É necessário fazer o controle do indíviduo
        //        Aqui está fazendo ainda a mesma coisa que o
        //        original, então é preciso adicionar indexador
        //        para controlar de qual indíviduo pertence a lista

        //        list_behavior behaivors = sessions.at(0);

        QMap<int,list_behavior> behaivors;
        behaivors.insert(1,sessions.at(0));

        // O comentário referente a este TODO termina na linha acima


        // TODO : É necessário fazer o controle do indíviduo
        //        então é preciso verificar como adicionar o indexador
        //        para controlar de qual indíviduo pertence a lista
        QList<QMap<int,list_behavior> > distributions;
        for(int d=0; d < this->nPermutations; d++){
            QMap<int,list_behavior> tmp;
            distributions.push_back(tmp);
        }
        for(int s=0; s < totalSessions; s++){
            QList< QVariantList > bootstrap_list = this->bootstrap(this->events.at(s),this->indexes.at(s),this->nPermutations);
            for(int p=0; p < this->nPermutations; p++){
//                distributions[p].list.push_back(bootstrap_list.at(p));
            }
        }

        // O comentário referente a este TODO termina na linha acima


        int totalPermutations = this->permutation_list.size();
        for(int s=0; s < totalPermutations; s++){
            list_behavior set_us;
            QString info;
            if(this->stopThread){
                emit this->statusProcess(0.0);
                emit this->threadStopped();
                return;
            }
            set_us.list.push_back(this->permutation_list.at(s));
            for(int idu=0; idu<this->permutation_list.at(s).size(); idu++){
                info.append(this->permutation_list.at(s).at(idu).toString()); info.append(", ");
            }
            QPair<double,double> E_mean = this->V(set_us,behaivors,Expected);
            QPair<double,double> O_mean = this->V(set_us,behaivors,Observed);
            QPair<double,double> R_mean = this->V(set_us,behaivors,Residue);
            QList<double> rand_dist;
            for(int d=0; d < this->nPermutations; d++){
                rand_dist.push_back(this->V(set_us,distributions.at(d),Residue).first);
            }
            QPair<double,double> P_value = this->pvalue(R_mean.first,rand_dist);
            this->sessionsLabels.push_back("P:"+QString::number(s));
            int tick = this->sessionsLabels.size();
            this->sessionsTicks.push_back(tick);
            this->infos.push_back(info);
            this->dataP.push_back(P_value);
            this->dataR.push_front(R_mean.first);
            this->dataO.push_front(O_mean.first);
            this->dataE.push_front(E_mean.first);
            double ratio = ((double) s)/totalPermutations;
            emit this->statusProcess(ratio);
        }
        emit this->dataProcessed();
    }
}