#include "dialogchoosedict.h"
#include "ui_dialogchoosedict.h"

DialogChooseDict::DialogChooseDict(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChooseDict)
{
    ui->setupUi(this);
    Database db;
    QStringList dictionaries = db.dictNames();
    this->ui->dictionaries->addItems(dictionaries);
    if(dictionaries.size() == 0){
        this->ui->warn->setText(tr("Nenhum dicionário encontrado. Você deve criar um dicionário antes de codificar um vídeo."));
        this->setResult(0);
        this->ui->dictionaries->setEnabled(false);
        this->ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

DialogChooseDict::~DialogChooseDict()
{
    delete ui;
}

QString DialogChooseDict::getDictionary()
{
    return this->ui->dictionaries->currentText();
}
