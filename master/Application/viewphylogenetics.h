#ifndef VIEWPHYLOGENETICS_H
#define VIEWPHYLOGENETICS_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <limits>

#include "phylogenetic.h"

namespace Ui {
class ViewPhylogenetics;
}

class ViewPhylogenetics : public QWidget
{
    Q_OBJECT

public:
    explicit ViewPhylogenetics(QWidget *parent = 0);
    ~ViewPhylogenetics();
    void showPhylogenetis(QList<QList<QPair<double, double> > > MO, QList<QList<QPair<double, double> > > ME,
                          QList<QList<QPair<double, double> > > MR, QList<QList<QPair<double, double> > > MP,
                          QList<QVariant> species, QList<QVariantList> behavior, int sizeIntervals);

private:
    Ui::ViewPhylogenetics *ui;

    QList<QVariant> species;
    QList<QVariantList> behavior;
    int sizeIntervals;
    QList<QList<QPair<double, double> > > MO;
    QList<QList<QPair<double, double> > > ME;
    QList<QList<QPair<double, double> > > MR;
    QList<QList<double> > MP;
    QList<QList<QPair<double, double> > > MF;
    QList< QList<significant_type> > MFs;

    double maxdouble, mindbouble;

    void showMtx();
    double getMaxStatitcs(QList<QList<QPair<double, double> > > statistcs);
    double getMinStatitcs(QList<QList<QPair<double, double> > > statistcs);
    QList<QList<bool> > getPhylogenetic(QList<QList<QPair<double, double> > > statistcs, int subdivisions, int element);
    QList< QList<significant_type> > getSignificantPhylogenetic(QList<QList<QPair<double, double> > > statistcs);
    void treatMP(QList<QList<QPair<double, double> > > orig);

private slots:
    void updateMF();
};

#endif // VIEWPHYLOGENETICS_H
