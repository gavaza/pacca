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
    connect(this->parentWidget()->parentWidget()->parentWidget(),SIGNAL(database_updated()),this,SLOT(refreshList()));
}

ControlSpecies::~ControlSpecies()
{
    delete ui;
}

void ControlSpecies::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete){
        this->remove();
    }
}

void ControlSpecies::refreshList()
{
    Database db;
    QList<Species> species = db.getAllSpecies();

    this->ui->listSpecies->clearSelection();

    for(int i = 0; i < species.size(); i++){

        Species s = species.at(i);

        QTableWidgetItem *item_id;
        QTableWidgetItem *item_name;

        /* find item */
        QString id = s.getId().toString();
        int row = -1;

        QList<QTableWidgetItem*> search_id = this->ui->listSpecies->findItems(id,Qt::MatchExactly);
        for (int j=0; j<search_id.size(); j++){
            if (search_id.at(j)->column()==0){
                row = search_id.at(j)->row();
            }
        }

        /* not find item*/
        if (row<0){

            item_id = new QTableWidgetItem;
            item_name = new QTableWidgetItem;
            item_id->setFlags(item_id->flags() & ~Qt::ItemIsEditable);

            row = this->ui->listSpecies->rowCount();
            this->ui->listSpecies->insertRow(row);

            /* setting item */
            this->ui->listSpecies->setItem(row,0,item_id);
            this->ui->listSpecies->setItem(row,1,item_name);
        }

        else{
            item_id  = this->ui->listSpecies->item(row,0);
            item_name = this->ui->listSpecies->item(row,1);
        }

        item_id->setText(id);
        QString name(s.getName().toString());
        item_name->setText(name.left(1).toUpper()+name.mid(1).toLower());
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
        if(QMessageBox::question(this,tr("Excluir"),
                                 tr("Deseja realmente remover as espécies selecionadas?"))
                == QMessageBox::Yes){
            Database db;
            QList<int> rows;
            for (int i=0; i<this->ui->listSpecies->selectedItems().size(); i+=2){
                unsigned int id = this->ui->listSpecies->selectedItems().at(i)->text().toUInt();
                db.removeSpecie(id);
                rows.push_back(this->ui->listSpecies->selectedItems().at(i)->row());
            }
            while(rows.size()>0){
                this->ui->listSpecies->removeRow(rows.last());
                rows.pop_back();
            }
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
