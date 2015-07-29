#ifndef DIALOGCHOOSESPECIE_H
#define DIALOGCHOOSESPECIE_H

#include <QDialog>
#include <QPushButton>

#include "species.h"
#include "subject.h"
#include "database.h"

namespace Ui {
class DialogChooseSpecie;
}

class DialogChooseSpecie : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChooseSpecie(QWidget *parent = 0);
    ~DialogChooseSpecie();
    QString getSpecieName();
    QVariant getSpecie();
    QString getSubjectName();
    QVariant getSubject();

private:
    Ui::DialogChooseSpecie *ui;
};

#endif // DIALOGCHOOSESPECIE_H
