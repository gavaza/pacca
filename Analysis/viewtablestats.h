#ifndef VIEWTABLESTATS_H
#define VIEWTABLESTATS_H

#include <QWidget>
#include <QVariant>
#include <QDebug>

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
                                         QVariant MR, QVariant vres);

    void setData(QList<QString> set_line,
                 QVector<QString> sessionLabels,
                 QList<QVector<QString> > infos,
                 QList<QList<double> > obs,
                 QList<QList<double> > spec,
                 QList<QList<double> > res,
                 QList<QPair<double, double> > pvalor,
                 QList<QMap<int, QPair<double,double> > > VE,
                 QList<QMap<int, QPair<double,double> > > VO,
                 QList<QMap<int, QPair<double,double> > > VR);

private slots:
    void alter_line(int i);

private:
    QVector<QString> session;
    QList<QVector<QString> > infos;
    QList<QList<double> > obs;
    QList<QList<double> > spec;
    QList<QList<double> > res;
    QList<QPair<double,double> > pvalor;
    QList<QMap<int, QPair<double,double> > > VE;
    QList<QMap<int, QPair<double,double> > > VO;
    QList<QMap<int, QPair<double,double> > > VR;

    Ui::ViewTableStats *ui;
};

#endif // VIEWTABLESTATS_H
