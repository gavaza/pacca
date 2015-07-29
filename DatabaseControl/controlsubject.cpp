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
}

ControlSubjects::~ControlSubjects()
{
    delete ui;
}

void ControlSubjects::refreshList()
{
    this->ui->listSubjects->setRowCount(0);
    Database db;
    QList<Subjects> subjects = db.getAllSubjects();
    for(int i = 0; i < subjects.size(); i++){
        QTableWidgetItem *item_id = new QTableWidgetItem;
        QTableWidgetItem *item_name = new QTableWidgetItem;
        Subjects u = subjects.at(i);
        QString id(u.getId().toString());
        QString name(u.getName().toString());
        item_id->setText(id);
        item_id->setFlags(item_id->flags() & ~Qt::ItemIsEditable);
        item_name->setText(name.left(1).toUpper()+name.mid(1).toLower());
        int row = this->ui->listSubjects->rowCount();
        this->ui->listSubjects->insertRow(row);
        this->ui->listSubjects->setItem(row,0,item_id);
        this->ui->listSubjects->setItem(row,1,item_name);
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
        Database db;
        int row = this->ui->listSubjects->selectedItems().first()->row();
        QString name = this->ui->listSubjects->selectedItems().first()->text();
        unsigned int id = this->ui->listSubjects->item(row,0)->text().toUInt();
        if(QMessageBox::question(this,tr("Excluir"),tr("Deseja realmente remover o indivíduo: ")+name) == QMessageBox::Yes){
            db.removeSubject(id);
            this->ui->listSubjects->removeRow(row);
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
