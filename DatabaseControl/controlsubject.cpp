#include "controlsubject.h"
#include "ui_controlsubject.h"

ControlSubjects::ControlSubjects(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlSubjects)
{
    ui->setupUi(this);
    this->refreshList();
    connect(this->ui->insertSubject,SIGNAL(clicked()),this,SLOT(create()));
    connect(this->ui->name,SIGNAL(returnPressed()),this,SLOT(create()));
    connect(this->ui->listSubjects,SIGNAL(cellChanged(int,int)),this,SLOT(save(int,int)));
    connect(this->ui->listSubjects,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(saveOrigText(int,int)));
    connect(this->ui->listSubjects,SIGNAL(cellEntered(int,int)),this,SLOT(saveOrigText(int,int)));
    connect(this->ui->b_excluir,SIGNAL(clicked()),this,SLOT(remove()));
    connect(this->ui->importFile,SIGNAL(clicked()),this,SLOT(importFromFile()));
    connect(this->parentWidget()->parentWidget()->parentWidget(),SIGNAL(database_updated()),this,SLOT(refreshList()));
}

ControlSubjects::~ControlSubjects()
{
    delete ui;
}

void ControlSubjects::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete){
        this->remove();
    }
}

void ControlSubjects::refreshList()
{
    Database db;
    QList<Subjects> subjects = db.getAllSubjects();

    this->ui->listSubjects->clearSelection();

    for(int i = 0; i < subjects.size(); i++){

        Subjects s = subjects.at(i);

        QTableWidgetItem *item_id;
        QTableWidgetItem *item_name;

        /* find item */
        QString id = s.getId().toString();
        int row = -1;

        QList<QTableWidgetItem*> search_id = this->ui->listSubjects->findItems(id,Qt::MatchExactly);
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

            row = this->ui->listSubjects->rowCount();
            this->ui->listSubjects->insertRow(row);

            /* setting item */
            this->ui->listSubjects->setItem(row,0,item_id);
            this->ui->listSubjects->setItem(row,1,item_name);
        }

        else{
            item_id  = this->ui->listSubjects->item(row,0);
            item_name = this->ui->listSubjects->item(row,1);
        }

        item_id->setText(id);
        QString name(s.getName().toString());
        item_name->setText(name.left(1).toUpper()+name.mid(1).toLower());
    }
}

bool ControlSubjects::verify()
{
    bool ok = true;
    if(this->ui->name->text().size()==0){
        ok = false;
        QMessageBox::critical(this,tr("Falha"),tr("O campo nome é obrigatório!"));
    }
    return ok;
}

void ControlSubjects::create()
{
    if(this->verify()){
        Database db;
        Subjects s; s.setName(this->ui->name->text().simplified());
        if(db.insertSubject(s) > 0){
            QMessageBox::information(this,tr("Sucesso"),tr("Indivíduo criado com sucesso!"));
            this->ui->name->clear();
            this->refreshList();
        }else{
            QMessageBox::critical(this,tr("Falha"),tr("Não foi possível cadastrar o indivíduo!"));
        }
    }
    else return;
}

void ControlSubjects::save(int row, int col)
{
    if(this->origText.size() > 0){
        Database db;
        Subjects u;
        QString last = this->origText;
        u.setId(this->ui->listSubjects->item(row,0)->text());
        u.setName(this->ui->listSubjects->item(row,col)->text());
        if(db.editSubjects(u) == 0){
            this->origText = "";
            this->ui->listSubjects->item(row,col)->setText(last);
        }
    }
}

void ControlSubjects::saveOrigText(int row, int col)
{
    this->origText = this->ui->listSubjects->item(row,col)->text();
}

void ControlSubjects::remove()
{
    if(this->ui->listSubjects->selectedItems().size() > 0){
        if(QMessageBox::question(this,tr("Apagar indivíduos"),
                                 tr("Você tem certeza que deseja apagar os indivíduos selecionados?"))
                == QMessageBox::Yes){
            Database db;
            QList<int> rows;
            for (int i=0; i<this->ui->listSubjects->selectedItems().size(); i+=2){
                QString id = this->ui->listSubjects->selectedItems().at(i)->text();
                db.removeSession(id);
                rows.push_back(this->ui->listSubjects->selectedItems().at(i)->row());
            }
            while(rows.size()>0){
                this->ui->listSubjects->removeRow(rows.last());
                rows.pop_back();
            }
        }
    }
}

void ControlSubjects::importFromFile()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Importar indivíduos"), QDir::homePath());
    if(filename != ""){
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        Database db;
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            Subjects s; s.setName(line.simplified());
            if(db.insertSubject(s) <= 0){
                QMessageBox::critical(this,tr("Falha"),tr("Não foi possível importar alguns indivíduos!"));
                return;
            }
        }
        this->refreshList();
    }
}
