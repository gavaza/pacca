#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QList>
#include <QSettings>
#include <QColor>
#include <QVariant>
#include "qcustomplot.h"

#include "plotwindow_global.h"

namespace Ui {
class PlotWindow;
}

class PLOTWINDOWSHARED_EXPORT PlotWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PlotWindow(QWidget *parent = 0);
    ~PlotWindow();
    void showHistogram(QVector<double> data, QVector<double> ticks, QPair<double, double> variances,
                                   QVector<QString> labels, QString labX, QString labY, QString title, QColor color);
    void showHistogram(QVector<double> data, QVector<double> ticks, QVector<double> variances, double mean,
                              QVector<QString> labels, QString labX, QString labY, QString title, QColor color);
    void showStackHistogram(QVector<double> lower, QVector<double> upper, QVector<double> ticks,
                                   QVector<QString> labels, QString labX, QString labY, QString title, QColor lColor, QColor uColor);
    void showFrequenceStats(QMap<QVariant, int> freq, QString xlabel, QString legend, bool sorted);

    QCustomPlot* plot();

private slots:
    void titleDoubleClick(QMouseEvent *event, QCPPlotTitle *title);
    void axisLabelDoubleClick(QCPAxis* axis, QCPAxis::SelectablePart part);
    void legendDoubleClick(QCPLegend* legend, QCPAbstractLegendItem* item);
    void selectionChanged();
    void mousePress();
    void mouseWheel();
    void removeSelectedGraph();
    void removeAllGraphs();
    void contextMenuRequest(QPoint pos);
    void moveLegend();
    void graphClicked(QCPAbstractPlottable *plottable);

    QString getFilename(QString type);
    void rescale();
    void savePdf();
    void savePng();
    void saveJpg();

private:
    Ui::PlotWindow *ui;

    bool showMean;
    bool showVariance;
    bool showLegend;
    bool withZeros;
    bool filterPvalue;
    unsigned int showtype;
    unsigned int testType;
    int tailed;
    int nPermutations;
    double alfa;
    QCPPlotTitle* title;
    QColor colorFrequence;
    QColor colorObserved;
    QColor colorExpected;
    QColor colorResidue;
    QColor colorLower;
    QColor colorUpper;
    QColor colorMean;
    QColor colorVar;

    void createConnections();
    void refreshConfig();
};

#endif // PLOTWINDOW_H
