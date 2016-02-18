#include "viewtablestats.h"
#include "ui_viewtablestats.h"

ViewTableStats::ViewTableStats(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewTableStats)
{
    ui->setupUi(this);
}

ViewTableStats::~ViewTableStats()
{
    delete ui;
}

void ViewTableStats::insertListLine(QString line)
{
    this->ui->list->addItem(line);
}

void ViewTableStats::insertTableLine(QString session, QVariant obs,
                                     QVariant spec, QVariant res,
                                     QVariant pvalor)
{
    int row = 0;
    for(int c = 0; c < this->ui->table->columnCount(); c++){
        if(c==0){
            row = this->ui->table->rowCount();
            this->ui->table->insertRow(row);
        }
        QTableWidgetItem *item = new QTableWidgetItem();
        switch (c) {
        case 0:
            item->setText(session);
            break;
        case 1:
            item->setText(obs.toString());
            break;
        case 2:
            item->setText(spec.toString());
            break;
        case 3:
            item->setText(res.toString());
            break;
        case 4:
            if(pvalor.toDouble() >= 0){
                item->setText(pvalor.toString());
            }
            break;
        default:
            break;
        }
        this->ui->table->setItem(row,c,item);
    }
}

void ViewTableStats::insertTable2Line(QString subject, QVariant MO, QVariant vobs,
                                     QVariant ME, QVariant vspec,
                                     QVariant MR, QVariant vres){
    int row = 0;
    for(int c = 0; c < this->ui->table_2->columnCount(); c++){
        if(c==0){
            row = this->ui->table_2->rowCount();
            this->ui->table_2->insertRow(row);
        }
        QTableWidgetItem *item = new QTableWidgetItem();
        switch (c) {
        case 0:
            item->setText(subject);
            break;
        case 1:
            item->setText(MO.toString());
            break;
        case 2:
            item->setText(vobs.toString());
            break;
        case 3:
            item->setText(ME.toString());
            break;
        case 4:
            item->setText(vspec.toString());
            break;
        case 5:
            item->setText(MR.toString());
            break;
        case 6:
            item->setText(vres.toString());
            break;
        default:
            break;
        }
        this->ui->table_2->setItem(row,c,item);
    }
}
