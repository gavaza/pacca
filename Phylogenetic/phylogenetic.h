#ifndef PHYLOGENETIC_H
#define PHYLOGENETIC_H

#include <QVariant>
#include <QList>
#include <QSettings>
#include <QThread>

#include "statistics.h"

enum significant_type {
    insignificant = 0,
    negative_significant = -1,
    positive_significant = 1,
};

enum stats_type {
    observed = 0,
    expected = 1,
    residue = 2,
};

class Phylogenetic : public QThread
{
    Q_OBJECT
public:
    explicit Phylogenetic();
    ~Phylogenetic();
    void run();
    void loadData(QMap<QString, StatisticMap> sessions,
                  QMap<QString, QMap<int, QList<QList<int> > > > indexes,
                  QList<QVariant> species, QList<QVariantList> behavior,
                  int sizeSeq, int sizeIntervals, int sizeStep, bool absolute);
    void calcData();
    bool getStopThreadStatus();
    void setStopThreadStatus(bool stop);

    QList<QList<QPair<double, double> > > getMO();
    QList<QList<QPair<double, double> > > getME();
    QList<QList<QPair<double, double> > > getMR();
    QList<QList<QPair<double, double> > > getMP();
    QList<QVariant> getSpecies();
    QList<QVariantList> getBehaviors();

private:
    QMap< QString, StatisticMap > sessions;
    QMap< QString, QMap<int, QList< QList<int> > > > indexes;
    QList<QVariant> species;
    QList<QVariantList> behavior;
    int sizeSeq;
    int sizeIntervals;
    int sizeStep;
    bool dynamic;
    bool absolute;
    QList<QList<QPair<double, double> > > MO;
    QList<QList<QPair<double, double> > > ME;
    QList<QList<QPair<double, double> > > MR;
    QList< QList< QPair<double, double> > > MP;
    Statistics* statsModule;
    bool stopThread;

    void setSpecies(QList<QVariant> species);
    void setBehavior(QList<QVariantList> behavior);
    QList<StatisticMap> randomize(StatisticMap sessions, QMap<int, QList< QList<int> > > indexes);

signals:
    void dataProcessed();
    void statusProcess(double);
    void threadStopped();

};

#endif // PHYLOGENETIC_H
