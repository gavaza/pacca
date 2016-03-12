#ifndef VIEWGRAPHICSTATS_H
#define VIEWGRAPHICSTATS_H

#include <QWidget>
#include <qcustomplot.h>

#include "plotwindow.h"
#include "database.h"

namespace Ui {
class ViewGraphicStats;
}

class ViewGraphicStats : public QWidget
{
    Q_OBJECT

public:
    explicit ViewGraphicStats(QWidget *parent = 0);
    ~ViewGraphicStats();

    void insertDataSession(double pos, QString session, double obs, double exp,
                         double res, double pvalor = -1);
    void insertDataSubjects(double pos, QString subject, double MO, double vobs,
                                         double ME, double vexp,
                                         double MR, double vres);

    void setData(QList<QString> set_line,
                 QVector<QString> sessionLabels,
                 QList<QVector<QString> > infos,
                 QList<QList<double> > obs,
                 QList<QList<double> > spec,
                 QList<QList<double> > res,
                 QList<QPair<bool, double> > pvalor,
                 QList<QMap<int, QPair<double,double> > > VE,
                 QList<QMap<int, QPair<double,double> > > VO,
                 QList<QMap<int, QPair<double,double> > > VR);


private:
    Ui::ViewGraphicStats *ui;

    QVector<QString> session;
    QList<QVector<QString> > infos;
    QList<QList<double> > observed;
    QList<QList<double> > expected;
    QList<QList<double> > residue;
    QList< QPair<bool,double> > pvalues;
    QList<QMap<int, QPair<double,double> > > VE;
    QList<QMap<int, QPair<double,double> > > VO;
    QList<QMap<int, QPair<double,double> > > VR;

    QVector<double> obsData;
    QVector<double> expData;
    QVector<double> resData;
    QVector<double> pvalData;
    QVector<double> voData;
    QVector<double> veData;
    QVector<double> vrData;
    QVector<double> ticks;
    QVector<double> ticksPvalue;
    QVector<QString> labels;
    QVector<QString> labelsPvalue;
    QMap<int,QString> subjectsNames;

    QColor colorExpected;
    QColor colorObserved;
    QColor colorResidue;
    QColor colorUpper;
    bool filterPvalue;

    void createConnections();
    void loadConfig();

private slots:
    void alter_line(int i);
    void plotSessions();
    void plotSubjects();
    void clearAll();
};

#endif // VIEWGRAPHICSTATS_H
