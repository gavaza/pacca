#include "controlusers.h"
#include "ui_controlusers.h"

ControlUsers::ControlUsers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlUsers)
{
    ui->setupUi(this);
    this->refreshList();
    connect(this->ui->insertUser,SIGNAL(clicked()),this,SLOT(create()));
    connect(this->ui->name,SIGNAL(returnPressed()),this,SLOT(create()));
    connect(this->ui->listUsers,SIGNAL(cellChanged(int,int)),this,SLOT(save(int,int)));
    connect(this->ui->listUsers,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(saveOrigText(int,int)));
    connect(this->ui->listUsers,SIGNAL(cellEntered(int,int)),this,SLOT(saveOrigText(int,int)));
    connect(this->ui->b_excluir,SIGNAL(clicked()),this,SLOT(remove()));
}

ControlUsers::~ControlUsers()
{
    delete ui;
}

void ControlUsers::refreshList()
{
    this->ui->listUsers->clear();
    this->ui->listUsers->setRowCount(0);
    Database db;
    QList<Users> users = db.getAllUsers();
    for(int i = 0; i < users.size(); i++){
        QTableWidgetItem *item_id = new QTableWidgetItem;
        QTableWidgetItem *item_name = new QTableWidgetItem;
        Users u = users.at(i);
        QString id(u.getId().toString());
        QString name(u.getName().toString());
        item_id->setText(id);
        item_id->setFlags(item_id->flags() & ~Qt::ItemIsEditable);
        item_name->setText(name.left(1).toUpper()+name.mid(1).toLower());
        int row = this->ui->listUsers->rowCount();
        this->ui->listUsers->insertRow(row);
        this->ui->listUsers->setItem(row,0,item_id);
        this->ui->listUsers->setItem(row,1,item_name);
    }
}

bool ControlUsers::verify()
{
    bool ok = true;
    if(this->ui->name->text().size()==0){
        ok = false;
        QMessageBox::critical(this,tr("Falha"),tr("O campo nome é obrigatório!"));
    }
    return ok;
}

void ControlUsers::create()
{
    if(this->verify()){
        Database db;
        if(db.insertUser(Users(this->ui->name->text())) > 0){
            QMessageBox::information(this,tr("Sucesso"),tr("Usuário criado com sucesso!"));
            this->ui->name->clear();
            this->refreshList();
        }else{
            QMessageBox::critical(this,tr("Falha"),tr("Não foi possível criar o usuário!"));
        }
    }
    else return;
}

void ControlUsers::save(int row, int col)
{
    if(this->origText.size() > 0){
        Database db;
        Users u;
        QString last = this->origText;
        u.setId(this->ui->listUsers->item(row,0)->text());
        u.setName(this->ui->listUsers->item(row,col)->text());
        if(db.editUsers(u) == 0){
            this->origText = "";
            this->ui->listUsers->item(row,col)->setText(last);
        }
    }
}

void ControlUsers::saveOrigText(int row, int col)
{
    this->origText = this->ui->listUsers->item(row,col)->text();
}

void ControlUsers::remove()
{
    if(this->ui->listUsers->selectedItems().size() > 0){
        Database db;
        int row = this->ui->listUsers->selectedItems().first()->row();
        QString name = this->ui->listUsers->selectedItems().first()->text();
        unsigned int id = this->ui->listUsers->item(row,0)->text().toUInt();
        if(QMessageBox::question(this,tr("Excluir"),tr("Deseja realmente remover o usuário: ")+name) == QMessageBox::Yes){
            db.removeUser(id);
            this->ui->listUsers->removeRow(row);
        }
    }
}
