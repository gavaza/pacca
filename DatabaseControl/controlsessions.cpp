#include "controlsessions.h"
#include "ui_controlsessions.h"

ControlSessions::ControlSessions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlSessions)
{
    ui->setupUi(this);
    this->load();
    connect(this->ui->sessions,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(saveOrigText(int,int)));
    connect(this->ui->sessions,SIGNAL(cellEntered(int,int)),this,SLOT(saveOrigText(int,int)));
    connect(this->ui->remove,SIGNAL(clicked()),this,SLOT(remove()));
}

ControlSessions::~ControlSessions()
{
    delete ui;
}

void ControlSessions::save(int r, int c)
{
    disconnect(this->ui->sessions,SIGNAL(cellChanged(int,int)),this,SLOT(save(int,int)));
    QString newContent = this->ui->sessions->item(r,c)->text().simplified();
    if(c!=3) this->ui->sessions->item(r,c)->setText(this->origText);
    if(newContent.size() != 0){
        if(c!=3) this->ui->sessions->item(r,c)->setText(newContent);
        Sessions s;
        s.setId(this->ui->sessions->item(r,0)->text());
        s.setObserver(this->ui->sessions->item(r,1)->text());
        s.setSubject(this->ui->sessions->item(r,2)->text());
        s.setSpecies(this->ui->sessions->item(r,3)->text());
        s.setDescription(this->ui->sessions->item(r,5)->text());
        switch (c) {
        case 1:
            s.setObserver(newContent);
            break;
        case 2:
            s.setSubject(newContent);
            break;
        case 5:
            s.setDescription(newContent);
            break;
        default:
            break;
        }
        Database db;
        db.editSession(s);
    } else {
        this->ui->sessions->item(r,c)->setText(this->origText);
    }
}

void ControlSessions::load()
{
    Database db;
    QList<Sessions> list = db.getAllSessions();

    QSettings settings("NuEvo","Pacca");
    settings.beginGroup("global");
    QVariant user = settings.value("user");
    settings.endGroup();

    this->ui->sessions->setRowCount(0);

    for(int i = 0; i < list.size(); i++){
        Sessions s = list.at(i);
//        if(user == s.getDecoder() || s.getDecoder().toString().isEmpty()){
            QTableWidgetItem *item_id  = new QTableWidgetItem;
            QTableWidgetItem *item_obs = new QTableWidgetItem;
            QTableWidgetItem *item_sub  = new QTableWidgetItem;
            QTableWidgetItem *item_spc  = new QTableWidgetItem;
            QTableWidgetItem *item_dd  = new QTableWidgetItem;
            QTableWidgetItem *item_des = new QTableWidgetItem;

            item_id->setText(s.getId().toString());
            item_id->setFlags(item_id->flags() & ~Qt::ItemIsEditable);
            item_sub->setText(s.getSubject().toString());
            item_sub->setFlags(item_sub->flags() & ~Qt::ItemIsEditable);
            item_spc->setText(s.getSpecies().toString());
            item_spc->setFlags(item_spc->flags() & ~Qt::ItemIsEditable);
            item_dd->setText(s.getDateDecoding().toDateTime().toString("dd/MM/yyyy hh:mm:ss"));
            item_dd->setFlags(item_dd->flags() & ~Qt::ItemIsEditable);
            item_obs->setText(s.getObserver().toString());
            item_des->setText(s.getDescription().toString());

            int row = this->ui->sessions->rowCount();
            this->ui->sessions->insertRow(row);
            this->ui->sessions->setItem(row,0,item_id);
            this->ui->sessions->setItem(row,1,item_obs);
            this->ui->sessions->setItem(row,2,item_sub);
            this->ui->sessions->setItem(row,3,item_spc);
            this->ui->sessions->setItem(row,4,item_dd);
            this->ui->sessions->setItem(row,5,item_des);
//        }
    }
}

void ControlSessions::saveOrigText(int r, int c)
{
    if(c!=3 && c!=2){
        this->origText = this->ui->sessions->item(r,c)->text();
        connect(this->ui->sessions,SIGNAL(cellChanged(int,int)),this,SLOT(save(int,int)));
    } else {
        DialogChooseSpecie spc;
        if(spc.exec()){
            if(c==3){
                this->ui->sessions->item(r,c-1)->setText(spc.getSubjectName());
                this->ui->sessions->item(r,c)->setText(spc.getSpecieName());
                this->save(r,c-1);
                this->save(r,c);
            } else {
                this->ui->sessions->item(r,c)->setText(spc.getSubjectName());
                this->ui->sessions->item(r,c+1)->setText(spc.getSpecieName());
                this->save(r,c);
                this->save(r,c+1);
            }
        }
    }
}

void ControlSessions::remove()
{
    if(this->ui->sessions->selectedItems().size() > 0){
        QString id = this->ui->sessions->selectedItems().first()->text();
        if(QMessageBox::question(this,tr("Apagar sessão"),
                                 tr("Você tem certeza que deseja apagar a sessão selecionada?"))
                == QMessageBox::Yes){
            Database db;
            db.removeSession(id);
        }
    }
    this->load();
}
