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
    connect(this->parentWidget()->parentWidget()->parentWidget(),SIGNAL(database_updated()),this,SLOT(load()));

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
        if(c!=3) {
            QList<int> rows;
            for(int i=0; i<this->ui->sessions->selectedItems().size(); i+=6){
                rows.push_back(this->ui->sessions->selectedItems().at(i)->row());
            }
            rows.push_back(r);
            for(int i=0; i<rows.size(); i++){
                this->ui->sessions->item(rows.at(i),c)->setText(newContent);
                Sessions s;
                s.setId(this->ui->sessions->item(rows.at(i),0)->text());
                s.setObserver(this->ui->sessions->item(rows.at(i),1)->text());
                s.setSubject(this->ui->sessions->item(rows.at(i),2)->text());
                s.setSpecies(this->ui->sessions->item(rows.at(i),3)->text());
                s.setDescription(this->ui->sessions->item(rows.at(i),5)->text());
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
            }
        } else {
            this->ui->sessions->item(r,c)->setText(this->origText);
        }
    }
}

void ControlSessions::load()
{
    Database db;
    QList<Sessions> list = db.getAllSessions();

    this->ui->sessions->clearSelection();

    for(int i = 0; i < list.size(); i++){

        Sessions s = list.at(i);

        QTableWidgetItem *item_id;
        QTableWidgetItem *item_obs;
        QTableWidgetItem *item_sub;
        QTableWidgetItem *item_spc;
        QTableWidgetItem *item_dd;
        QTableWidgetItem *item_des;


        /* find item */
        QString id = s.getId().toString();
        int row = -1;

        QList<QTableWidgetItem*> search_id = this->ui->sessions->findItems(id,Qt::MatchExactly);
        for (int j=0; j<search_id.size(); j++){
            if (search_id.at(j)->column()==0){
                row = search_id.at(j)->row();
            }
        }

        /* not find item*/
        if (row<0){

            item_id  = new QTableWidgetItem;
            item_obs = new QTableWidgetItem;
            item_sub  = new QTableWidgetItem;
            item_spc  = new QTableWidgetItem;
            item_dd  = new QTableWidgetItem;
            item_des = new QTableWidgetItem;

            item_id->setFlags(item_id->flags() & ~Qt::ItemIsEditable);
            item_sub->setFlags(item_sub->flags() & ~Qt::ItemIsEditable);
            item_spc->setFlags(item_spc->flags() & ~Qt::ItemIsEditable);
            item_dd->setFlags(item_dd->flags() & ~Qt::ItemIsEditable);

            row = this->ui->sessions->rowCount();
            this->ui->sessions->insertRow(row);

            /* setting item */
            this->ui->sessions->setItem(row,0,item_id);
            this->ui->sessions->setItem(row,1,item_obs);
            this->ui->sessions->setItem(row,2,item_sub);
            this->ui->sessions->setItem(row,3,item_spc);
            this->ui->sessions->setItem(row,4,item_dd);
            this->ui->sessions->setItem(row,5,item_des);


        }
        else{
            item_id  = this->ui->sessions->item(row,0);
            item_obs = this->ui->sessions->item(row,1);
            item_sub  = this->ui->sessions->item(row,2);
            item_spc  = this->ui->sessions->item(row,3);
            item_dd  = this->ui->sessions->item(row,4);
            item_des = this->ui->sessions->item(row,5);
        }

        item_id->setText(s.getId().toString());
        item_sub->setText(s.getSubject().toString());
        item_spc->setText(s.getSpecies().toString());
        item_dd->setText(s.getDateDecoding().toDateTime().toString("dd/MM/yyyy hh:mm:ss"));
        item_obs->setText(s.getObserver().toString());
        item_des->setText(s.getDescription().toString());
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
        if(QMessageBox::question(this,tr("Apagar sessões"),
                                 tr("Você tem certeza que deseja apagar as sessões selecionadas?"))
                == QMessageBox::Yes){
            Database db;
            QList<int> rows;
            for (int i=0; i<this->ui->sessions->selectedItems().size(); i+=6){
                QString id = this->ui->sessions->selectedItems().at(i)->text();
                db.removeSession(id);
                rows.push_back(this->ui->sessions->selectedItems().at(i)->row());
            }
            while(rows.size()>0){
                this->ui->sessions->removeRow(rows.last());
                rows.pop_back();
            }
        }
    }
}
