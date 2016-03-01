#ifndef PHYLOGENETIC_H
#define PHYLOGENETIC_H

#include <QVariant>
#include <QList>
#include <QSettings>
#include <QThread>

#ifdef MAC_OS_X_VERSION_MAX_ALLOWED
#include <QtXlsx>
#else
#include <QtXlsx/xlsxdocument.h>
#endif

#include <QFileDialog>
#include <QString>

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
                  QList<QVariant> species, QList<list_behavior> behavior,
                  int sizeSeq, int sizeIntervals, int sizeStep, bool absolute);
    void calcData();
    bool getStopThreadStatus();
    void setStopThreadStatus(bool stop);
    void saveFile(QString filename);

    QList<QList<QPair<double, double> > > getMO();
    QList<QList<QPair<double, double> > > getME();
    QList<QList<QPair<double, double> > > getMR();
    QList<QList<QPair<double, double> > > getMP();
    QList< QList<significant_type> > getMFs();
    QList<QVariant> getSpecies();
    QList<list_behavior> getBehaviors();

private:
    QMap< QString, StatisticMap > sessions;
    QList<QVariant> species;
    QList<list_behavior> behavior;
    int sizeSeq;
    int sizeIntervals;
    int sizeStep;
    bool dynamic;
    enum types_of_variances observedType;
    QList<QList<QPair<double, double> > > MO;
    QList<QList<QPair<double, double> > > ME;
    QList<QList<QPair<double, double> > > MR;
    QList< QList< QPair<double, double> > > MP;
    QList< QList<significant_type> > MFs;
    Statistics* statsModule;
    bool stopThread;

    void setSpecies(QList<QVariant> species);
    void setBehavior(QList<list_behavior> behavior);
    QList<StatisticMap> randomize(StatisticMap sessions);
    QList<QList<significant_type> > getSignificantPhylogenetic(QList<QList<QPair<double, double> > > statistcs);

signals:
    void dataProcessed();
    void statusProcess(double);
    void statusProcessLabel(QString);
    void threadStopped();

};

#endif // PHYLOGENETIC_H
