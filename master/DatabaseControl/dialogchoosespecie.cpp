#include "dialogchoosespecie.h"
#include "ui_dialogchoosespecie.h"

DialogChooseSpecie::DialogChooseSpecie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChooseSpecie)
{
    ui->setupUi(this);
    Database db;
    QList<Species> list = db.getAllSpecies();
    for(int i = 0; i < list.size(); i++){
        Species spc = list.at(i);
        this->ui->species->addItem(spc.getName().toString(),spc.getId());
    }
    if(list.size() == 0){
        this->ui->warn->setText(tr("Nenhuma espécie encontrada. Você deve cadastrar ao menos uma espécie antes!"));
        this->setResult(0);
        this->ui->species->setEnabled(false);
        this->ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

DialogChooseSpecie::~DialogChooseSpecie()
{
    delete ui;
}

QString DialogChooseSpecie::getSpecieName()
{
    return this->ui->species->currentText();
}

QVariant DialogChooseSpecie::getSpecie()
{
    return this->ui->species->currentData();
}
