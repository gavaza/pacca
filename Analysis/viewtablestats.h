#ifndef VIEWTABLESTATS_H
#define VIEWTABLESTATS_H

#include <QWidget>
#include <QVariant>

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
    void insertTable2Line(QString subject, QVariant MO, QVariant vobs,
                                         QVariant ME, QVariant vspec,
                                         QVariant MR, QVariant vres);

private:
    Ui::ViewTableStats *ui;
};

#endif // VIEWTABLESTATS_H
