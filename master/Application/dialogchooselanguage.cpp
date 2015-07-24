#include "dialogchooselanguage.h"
#include "ui_dialogchooselanguage.h"

DialogChooseLanguage::DialogChooseLanguage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChooseLanguage)
{
    ui->setupUi(this);
    this->ui->languages->addItem("English");
    this->ui->languages->addItem("Português");
}

DialogChooseLanguage::~DialogChooseLanguage()
{
    delete ui;
}

QString DialogChooseLanguage::getLanguage()
{
    return this->ui->languages->currentText();
}

void DialogChooseLanguage::includeMenssage(QString msg)
{
    this->ui->msg->setText(msg);
}
