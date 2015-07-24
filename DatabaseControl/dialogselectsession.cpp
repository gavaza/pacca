#include "dialogselectsession.h"
#include "ui_dialogselectsession.h"

DialogSelectSession::DialogSelectSession(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSelectSession)
{
    ui->setupUi(this);
    this->ui->lista->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    this->load();
}

DialogSelectSession::~DialogSelectSession()
{
    delete ui;
}

QList<QTableWidgetItem*> DialogSelectSession::getSelectedItens()
{
    return this->ui->lista->selectedItems();
}

void DialogSelectSession::load()
{
    Database db;
    QList<Sessions> sessions;
    sessions = db.getAllSessions();
    for(int i = 0; i < sessions.size(); i++){
        QTableWidgetItem *item_id  = new QTableWidgetItem;
        QTableWidgetItem *item_sub  = new QTableWidgetItem;
        QTableWidgetItem *item_dd  = new QTableWidgetItem;
        QTableWidgetItem *item_dec = new QTableWidgetItem;
        QTableWidgetItem *item_spc = new QTableWidgetItem;
        QTableWidgetItem *item_des = new QTableWidgetItem;

        Sessions s = sessions.at(i);
        item_id->setText(s.getId().toString());
        item_sub->setText(s.getSubject().toString());
        item_dd->setText(s.getDateDecoding().toDateTime().toString("dd/MM/yyyy hh:mm:ss"));
        item_dec->setText(s.getDecoder().toString());
        item_spc->setText(s.getSpecies().toString());
        item_des->setText(s.getDescription().toString());

        int row = this->ui->lista->rowCount();
        this->ui->lista->insertRow(row);
        this->ui->lista->setItem(row,0,item_id);
        this->ui->lista->setItem(row,1,item_sub);
        this->ui->lista->setItem(row,2,item_spc);
        this->ui->lista->setItem(row,3,item_dec);
        this->ui->lista->setItem(row,4,item_dd);
        this->ui->lista->setItem(row,5,item_des);
    }
}
