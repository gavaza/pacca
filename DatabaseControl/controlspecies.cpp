#include "controlspecies.h"
#include "ui_controlspecies.h"

ControlSpecies::ControlSpecies(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlSpecies)
{
    ui->setupUi(this);
    this->refreshList();
    connect(this->ui->insertSpecie,SIGNAL(clicked()),this,SLOT(create()));
    connect(this->ui->name,SIGNAL(returnPressed()),this,SLOT(create()));
    connect(this->ui->listSpecies,SIGNAL(cellChanged(int,int)),this,SLOT(save(int,int)));
    connect(this->ui->listSpecies,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(saveOrigText(int,int)));
    connect(this->ui->listSpecies,SIGNAL(cellEntered(int,int)),this,SLOT(saveOrigText(int,int)));
    connect(this->ui->b_excluir,SIGNAL(clicked()),this,SLOT(remove()));
    connect(this->ui->importFile,SIGNAL(clicked()),this,SLOT(importFromFile()));
}

ControlSpecies::~ControlSpecies()
{
    delete ui;
}

void ControlSpecies::refreshList()
{
    this->ui->listSpecies->setRowCount(0);
    Database db;
    QList<Species> species = db.getAllSpecies();
    for(int i = 0; i < species.size(); i++){
        QTableWidgetItem *item_id = new QTableWidgetItem;
        QTableWidgetItem *item_name = new QTableWidgetItem;
        Species u = species.at(i);
        QString id(u.getId().toString());
        QString name(u.getName().toString());
        item_id->setText(id);
        item_id->setFlags(item_id->flags() & ~Qt::ItemIsEditable);
        item_name->setText(name.left(1).toUpper()+name.mid(1).toLower());
        int row = this->ui->listSpecies->rowCount();
        this->ui->listSpecies->insertRow(row);
        this->ui->listSpecies->setItem(row,0,item_id);
        this->ui->listSpecies->setItem(row,1,item_name);
    }
}

bool ControlSpecies::verify()
{
    bool ok = true;
    if(this->ui->name->text().size()==0){
        ok = false;
        QMessageBox::critical(this,tr("Falha"),tr("O campo nome é obrigatório!"));
    }
    return ok;
}

void ControlSpecies::create()
{
    if(this->verify()){
        Database db;
        if(db.insertSpecie(Species(this->ui->name->text())) > 0){
            QMessageBox::information(this,tr("Sucesso"),tr("Espécie criada com sucesso!"));
            this->ui->name->clear();
            this->refreshList();
        }else{
            QMessageBox::critical(this,tr("Falha"),tr("Não foi possível cadastrar a espécie!"));
        }
    }
    else return;
}

void ControlSpecies::save(int row, int col)
{
    if(this->origText.size() > 0){
        Database db;
        Species u;
        QString last = this->origText;
        u.setId(this->ui->listSpecies->item(row,0)->text());
        u.setName(this->ui->listSpecies->item(row,col)->text());
        if(db.editSpecies(u) == 0){
            this->origText = "";
            this->ui->listSpecies->item(row,col)->setText(last);
        }
    }
}

void ControlSpecies::saveOrigText(int row, int col)
{
    this->origText = this->ui->listSpecies->item(row,col)->text();
}

void ControlSpecies::remove()
{
    if(this->ui->listSpecies->selectedItems().size() > 0){
        Database db;
        int row = this->ui->listSpecies->selectedItems().first()->row();
        QString name = this->ui->listSpecies->selectedItems().first()->text();
        unsigned int id = this->ui->listSpecies->item(row,0)->text().toUInt();
        if(QMessageBox::question(this,tr("Excluir"),tr("Deseja realmente remover a espécie: ")+name) == QMessageBox::Yes){
            db.removeSpecie(id);
            this->ui->listSpecies->removeRow(row);
        }
    }
}

void ControlSpecies::importFromFile()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Importar espécies"), QDir::homePath());
    if(filename != ""){
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        Database db;
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if(db.insertSpecie(Species(line)) <= 0){
                QMessageBox::critical(this,tr("Falha"),tr("Não foi possível importar algumas espécies!"));
                return;
            }
        }
        this->refreshList();
    }
}
