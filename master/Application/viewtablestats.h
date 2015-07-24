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
    void insertTableLine(QString session, QVariant obs, QVariant MO,
                         QVariant vobs, QVariant spec, QVariant ME, QVariant vspec,
                         QVariant res, QVariant MR, QVariant vres, QVariant pvalor = -1);

private:
    Ui::ViewTableStats *ui;
};

#endif // VIEWTABLESTATS_H
