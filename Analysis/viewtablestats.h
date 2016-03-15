#ifndef VIEWTABLESTATS_H
#define VIEWTABLESTATS_H

#include <QWidget>
#include <QVariant>
#include <QDebug>

#include "database.h"

namespace Ui {
class ViewTableStats;
}

class ViewTableStats : public QWidget
{
    Q_OBJECT

public:
    explicit ViewTableStats(QWidget *parent = 0);
    ~ViewTableStats();
    void insertListLine(QString line);
    void insertTableLine(QString session, QVariant obs, QVariant spec,
                         QVariant res, QVariant pvalor = -1);
    void insertTable2Line(QVariant subject, QVariant MO, QVariant vobs,
                                         QVariant ME, QVariant vspec,
                                         QVariant MR, QVariant vres, QVariant pvalor);

    void setData(QList<QString> set_line,
                 QVector<QString> sessionLabels,
                 QList<QVector<QString> > infos,
                 QList<QList<double> > obs,
                 QList<QList<double> > spec,
                 QList<QList<double> > res,
                 QList<QList<QPair<bool, double> > > pvalor,
                 QList<QMap<int, QPair<double,double> > > VE,
                 QList<QMap<int, QPair<double,double> > > VO,
                 QList<QMap<int, QPair<double,double> > > VR,
                 QList<QMap<int, QPair<bool, double> > > VP);

private slots:
    void alter_line(int i); 
    void update();

private:
    QVector<QString> session;
    QList<QVector<QString> > infos;
    QList<QList<double> > obs;
    QList<QList<double> > spec;
    QList<QList<double> > res;
    QList< QList< QPair<bool, double> > > pvalor;
    QList<QMap<int, QPair<double,double> > > VE;
    QList<QMap<int, QPair<double,double> > > VO;
    QList<QMap<int, QPair<double,double> > > VR;
    QList<QMap<int, QPair<bool, double> > > VP;
    QMap<int,QString> subjectsNames;

    int currentRow;

    Ui::ViewTableStats *ui;
};

#endif // VIEWTABLESTATS_H
