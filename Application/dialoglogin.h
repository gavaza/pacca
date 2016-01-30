#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QVariant>

#include "database.h"
#include "users.h"

namespace Ui {
class DialogLogin;
}

class DialogLogin : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLogin(QList<Users> users, QWidget *parent = 0);
    ~DialogLogin();
    QString getName();

private:
    Ui::DialogLogin *ui;
};

#endif // DIALOGLOGIN_H
