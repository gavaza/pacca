#ifndef DIALOGCHOOSELANGUAGE_H
#define DIALOGCHOOSELANGUAGE_H

#include <QDialog>

namespace Ui {
class DialogChooseLanguage;
}

class DialogChooseLanguage : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChooseLanguage(QWidget *parent = 0);
    ~DialogChooseLanguage();
    QString getLanguage();
    void includeMenssage(QString msg);

private:
    Ui::DialogChooseLanguage *ui;
};

#endif // DIALOGCHOOSELANGUAGE_H
