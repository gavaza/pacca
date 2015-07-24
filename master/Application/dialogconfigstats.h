#ifndef DIALOGCONFIGSTATS_H
#define DIALOGCONFIGSTATS_H

#include <QDialog>
#include <QColor>
#include <QColorDialog>
#include <QSettings>

namespace Ui {
class DialogConfigStats;
}

class DialogConfigStats : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConfigStats(QWidget *parent = 0);
    ~DialogConfigStats();
    Ui::DialogConfigStats *ui;
    QColor colorExpected;
    QColor colorObserved;
    QColor colorResidue;
    QColor colorFrequence;
    QColor colorLower;
    QColor colorUpper;

private:
    QColorDialog *colorDialog;

private slots:
    void load();
    void saveChanges();
    void selectColorExpected();
    void selectColorObserved();
    void selectColorResidue();
    void selectColorFrequence();
    void selectColorLower();
    void selectColorUpper();
};

#endif // DIALOGCONFIGSTATS_H
