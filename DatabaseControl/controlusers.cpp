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
    connect(this->parentWidget()->parentWidget()->parentWidget(),SIGNAL(database_updated()),this,SLOT(refreshList()));
}

ControlUsers::~ControlUsers()
{
    delete ui;
}

void ControlUsers::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete){
        this->remove();
    }
}

void ControlUsers::refreshList()
{
    Database db;
    QList<Users> users = db.getAllUsers();

    this->ui->listUsers->clearSelection();

    for(int i = 0; i < users.size(); i++){

        Users u = users.at(i);

        QTableWidgetItem *item_id;
        QTableWidgetItem *item_name;

        /* find item */
        QString id = u.getId().toString();
        int row = -1;

        QList<QTableWidgetItem*> search_id = this->ui->listUsers->findItems(id,Qt::MatchExactly);
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

            row = this->ui->listUsers->rowCount();
            this->ui->listUsers->insertRow(row);

            /* setting item */
            this->ui->listUsers->setItem(row,0,item_id);
            this->ui->listUsers->setItem(row,1,item_name);
        }

        else{
            item_id  = this->ui->listUsers->item(row,0);
            item_name = this->ui->listUsers->item(row,1);
        }

        item_id->setText(id);
        QString name(u.getName().toString());
        item_name->setText(name.left(1).toUpper()+name.mid(1).toLower());
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
        if(QMessageBox::question(this,tr("Excluir usuários"),tr("Deseja realmente remover os usuários selecionados?")) == QMessageBox::Yes){
            Database db;
            QList<int> rows;
            for (int i=0; i<this->ui->listUsers->selectedItems().size(); i+=2){
                unsigned int id = this->ui->listUsers->selectedItems().at(i)->text().toUInt();
                db.removeUser(id);
                rows.push_back(this->ui->listUsers->selectedItems().at(i)->row());
            }
            while(rows.size()>0){
                this->ui->listUsers->removeRow(rows.last());
                rows.pop_back();
            }
        }
    }
}
