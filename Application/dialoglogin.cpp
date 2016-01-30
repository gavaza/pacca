#include "dialoglogin.h"
#include "ui_dialoglogin.h"

DialogLogin::DialogLogin(QList<Users> users, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLogin)
{
    ui->setupUi(this);
    if(users.size() == 0){
        QMessageBox::information(this,tr("Login Impossível"),tr("Nenhum usuário encontrado. Você deve criar um usuário antes de efeutar o login."));
        this->setResult(0);
        this->ui->name->setEnabled(false);
        this->ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
    for(int u = 0; u < users.size(); u++){
        Users user = users.at(u);
        QString n = user.getName().toString();
        this->ui->name->addItem(n.left(1).toUpper()+n.mid(1).toLower());
    }
}

DialogLogin::~DialogLogin()
{
    delete ui;
}

QString DialogLogin::getName()
{
    return this->ui->name->currentText();
}
