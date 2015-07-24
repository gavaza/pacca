#ifndef DIALOGCHOOSEDICT_H
#define DIALOGCHOOSEDICT_H

#include <QDialog>
#include <QPushButton>

#include "database.h"

namespace Ui {
class DialogChooseDict;
}

class DialogChooseDict : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChooseDict(QWidget *parent = 0);
    ~DialogChooseDict();
    QString getDictionary();

private:
    Ui::DialogChooseDict *ui;
};

#endif // DIALOGCHOOSEDICT_H
