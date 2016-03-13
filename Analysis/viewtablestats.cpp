#include "viewtablestats.h"
#include "ui_viewtablestats.h"

ViewTableStats::ViewTableStats(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewTableStats)
{
    ui->setupUi(this);
    Database db;
    QList<Subjects> subjects = db.getAllSubjects();
    this->subjectsNames.insert(-1,tr("Todos"));
    for(int k = 0; k < subjects.size(); ++k)
        this->subjectsNames.insert(subjects[k].getId().toInt(),subjects[k].getName().toString());
    connect(this->ui->list,SIGNAL(currentRowChanged(int)),this,SLOT(alter_line(int)));
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
    if (obs.type()==QVariant::Bool)
        if (obs.toBool()==false) return;
    if (spec.type()==QVariant::Bool)
        if (spec.toBool()==false) return;
    if (res.type()==QVariant::Bool)
        if (res.toBool()==false) return;
    if (pvalor.type()==QVariant::Bool)
        if (pvalor.toBool()==false) return;

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
            item->setText(QString::number(pvalor.toDouble()));
            break;
        default:
            break;
        }
        this->ui->table->setItem(row,c,item);
    }
}

void ViewTableStats::insertTable2Line(QVariant subject, QVariant MO, QVariant vobs,
                                     QVariant ME, QVariant vspec,
                                     QVariant MR, QVariant vres, QVariant pvalor){
    int row = 0;
    for(int c = 0; c < this->ui->table_2->columnCount(); c++){
        if(c==0){
            row = this->ui->table_2->rowCount();
            this->ui->table_2->insertRow(row);
        }
        QTableWidgetItem *item = new QTableWidgetItem();
        switch (c) {
        case 0:
            item->setText(subject.toString());
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
        case 7:
            item->setText(QString::number(pvalor.toDouble()));
            break;
        default:
            break;
        }
        this->ui->table_2->setItem(row,c,item);
    }
}

void ViewTableStats::setData(QList<QString> set_line,
                             QVector<QString> sessionLabels,
                             QList<QVector<QString> > infos,
                             QList<QList<double> > obs, QList<QList<double> > spec, QList<QList<double> > res,
                             QList< QList< QPair<bool, double> > > pvalor,
                             QList<QMap<int, QPair<double, double> > > VE,
                             QList<QMap<int, QPair<double, double> > > VO,
                             QList<QMap<int, QPair<double, double> > > VR,
                             QList<QMap<int, QPair<bool, double> > > VP){

    for (int i=0; i<set_line.size(); i++){
        this->ui->list->addItem(set_line.at(i));
    }

    this->session = sessionLabels;
    this->infos = infos;
    this->obs = obs;
    this->spec = spec;
    this->res = res;
    this->pvalor = pvalor;
    this->VE = VE;
    this->VO = VO;
    this->VR = VR;
    this->VP = VP;
    if(this->ui->list->count() > 0){
        this->ui->list->item(0)->setSelected(true);
        this->alter_line(0);
    }
}

void ViewTableStats::alter_line(int i){
    this->ui->table->setRowCount(0);
    this->ui->table_2->setRowCount(0);
    for (int j=0; j<this->session.size(); j++){
        this->insertTableLine(this->session.at(j),
                              this->obs.at(i).at(j),
                              this->spec.at(i).at(j),
                              this->res.at(i).at(j),
                              this->pvalor.at(i).at(j).second);
    }
    QList<int> keys = this->VE.at(i).uniqueKeys();
    QListIterator<int> j(keys);
    while (j.hasNext()){
        int key = j.next();
        QPair<double,double> MeanVarE = VE.at(i).value(key);
        QPair<double,double> MeanVarO = VO.at(i).value(key);
        QPair<double,double> MeanVarR = VR.at(i).value(key);
        QVariant VarE = MeanVarE.second;
        QVariant VarO = MeanVarO.second;
        QVariant VarR = MeanVarR.second;
        if (VarE.toInt() == -1) VarE = "-";
        if (VarO.toInt() == -1) VarO = "-";
        if (VarR.toInt() == -1) VarR = "-";
        this->insertTable2Line(this->subjectsNames.value(key),
                               MeanVarO.first,
                               VarO,
                               MeanVarE.first,
                               VarE,
                               MeanVarR.first,
                               VarR,this->VP.at(i).value(key).second);
    }
}
