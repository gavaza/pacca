#include "viewphylogenetics.h"
#include "ui_viewphylogenetics.h"

ViewPhylogenetics::ViewPhylogenetics(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewPhylogenetics)
{
    ui->setupUi(this);
    this->maxdouble = std::numeric_limits<double>::max();
    this->mindbouble = std::numeric_limits<double>::min();

    connect(this->ui->intervalSlider,SIGNAL(valueChanged(int)),this,SLOT(updateMF()));
}

ViewPhylogenetics::~ViewPhylogenetics()
{
    delete ui;
}

void ViewPhylogenetics::showPhylogenetis(QList<QList<QPair<double, double> > > MO, QList<QList<QPair<double, double> > > ME, QList<QList<QPair<double, double> > > MR,
                                         QList<QList< QPair<double,double> > > MP,
                                         QList<QVariant> species, QList<QVariantList> behavior, int sizeIntervals)
{
    this->MO.clear(); this->ME.clear();this->MR.clear();this->MP.clear();this->MF.clear();this->MFs.clear();
    this->behavior = behavior;
    this->species = species;
    this->sizeIntervals = sizeIntervals;
    this->MO = MO;
    this->ME = ME;
    this->MR = MR;
    this->treatMP(MP);
    this->MFs = this->getSignificantPhylogenetic(this->MR);

    this->ui->intervalSlider->setMinimum(1);
    this->ui->intervalSlider->setMaximum(sizeIntervals);

    int nCols = this->behavior.size();
    int nRows = this->species.size();
    this->ui->tableMO->setRowCount(nRows);
    this->ui->tableME->setRowCount(nRows);
    this->ui->tableMR->setRowCount(nRows);
    this->ui->tableMP->setRowCount(nRows);
    this->ui->tableMF->setRowCount(nRows);
    this->ui->tableMFs->setRowCount(nRows);
    this->ui->tableMO->setColumnCount(nCols);
    this->ui->tableME->setColumnCount(nCols);
    this->ui->tableMR->setColumnCount(nCols);
    this->ui->tableMP->setColumnCount(nCols);
    this->ui->tableMF->setColumnCount(nCols);
    this->ui->tableMFs->setColumnCount(nCols);
    QStringList labelsC;
    for(int i=0; i < nCols; i++){
       QString s;
       labelsC.push_back(QString::number(i));
       s.append("SEQ: "); s.append(QString::number(i)); s.append(" :");
       int sizeSeq = behavior.at(i).size();
       for(int j=0; j < sizeSeq; j++){
           s.append("{");s.append(behavior.at(i).at(j).toString());s.append("}");
       }
       this->ui->infos->insertItem(i,s);
    }
    this->ui->tableMO->setHorizontalHeaderLabels(labelsC);
    this->ui->tableME->setHorizontalHeaderLabels(labelsC);
    this->ui->tableMR->setHorizontalHeaderLabels(labelsC);
    this->ui->tableMP->setHorizontalHeaderLabels(labelsC);
    this->ui->tableMF->setHorizontalHeaderLabels(labelsC);
    this->ui->tableMFs->setHorizontalHeaderLabels(labelsC);
    QStringList labelsR;
    for(int i=0; i < nRows; i++)
        labelsR.push_back(this->species.at(i).toString());
    this->ui->tableMO->setVerticalHeaderLabels(labelsR);
    this->ui->tableME->setVerticalHeaderLabels(labelsR);
    this->ui->tableMR->setVerticalHeaderLabels(labelsR);
    this->ui->tableMP->setVerticalHeaderLabels(labelsR);
    this->ui->tableMF->setVerticalHeaderLabels(labelsR);
    this->ui->tableMFs->setVerticalHeaderLabels(labelsR);

    this->showMtx();
}

void ViewPhylogenetics::showMtx()
{
    int nCols = this->behavior.size();
    int nRows = this->species.size();
    QList< QList<bool> > mask = this->getPhylogenetic(this->MR,this->sizeIntervals,1);
    char f = 'g';
    for(int i=0; i < nRows; i++){
        for(int j=0; j < nCols; j++){
            QString l;

            l=QString::number(this->MO.at(i).at(j).first,f,4); l+=" ( ";
            l+=QString::number(this->MO.at(i).at(j).second,f,4); l+=" ) ";
            QTableWidgetItem *itMO = new QTableWidgetItem();
            itMO->setText(l);
            this->ui->tableMO->setItem(i,j,itMO);

            l=QString::number(this->ME.at(i).at(j).first,f,4); l+=" ( ";
            l+=QString::number(this->ME.at(i).at(j).second,f,4); l+=" ) ";
            QTableWidgetItem *itME = new QTableWidgetItem();
            itME->setText(l);
            this->ui->tableME->setItem(i,j,itME);

            l=QString::number(this->MR.at(i).at(j).first,f,4); l+=" ( ";
            l+=QString::number(this->MR.at(i).at(j).second,f,4); l+=" ) ";
            QTableWidgetItem *itMR = new QTableWidgetItem();
            itMR->setText(l);
            this->ui->tableMR->setItem(i,j,itMR);

            l=QString::number(this->MP.at(i).at(j),f,4);
            QTableWidgetItem* itMP = new QTableWidgetItem();
            itMP->setText(l);
            this->ui->tableMP->setItem(i,j,itMP);

            l=QString::number(this->MFs.at(i).at(j));
            QTableWidgetItem* itMFs = new QTableWidgetItem();
            itMFs->setText(l);
            this->ui->tableMFs->setItem(i,j,itMFs);
        }
    }
    this->updateMF();
    this->ui->tableMO->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    this->ui->tableME->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    this->ui->tableMR->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    this->ui->tableMP->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    this->ui->tableMFs->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
}

double ViewPhylogenetics::getMaxStatitcs(QList<QList<QPair<double, double> > > statistcs)
{
    double max_value;
    max_value = this->mindbouble;
    for (int i=0; i<statistcs.size(); i++){
        for(int j=0; j<statistcs.at(i).size(); j++){
            double value = statistcs.at(i).at(j).first;
            max_value = value>max_value?value:max_value;
        }
    }
    return max_value;
}

double ViewPhylogenetics::getMinStatitcs(QList<QList<QPair<double, double> > > statistcs)
{
    double min_value;
    min_value = this->maxdouble;
    for (int i=0; i<statistcs.size(); i++){
        for(int j=0; j<statistcs.at(i).size(); j++){
            double value = statistcs.at(i).at(j).first;
            min_value = value<min_value?value:min_value;
        }
    }
    return min_value;
}

QList<QList<bool> > ViewPhylogenetics::getPhylogenetic(QList<QList<QPair<double, double> > > statistcs, int subdivisions, int element)
{
    QList< QList<bool> > result;
    if (element<=subdivisions){
        double max_value = this->getMaxStatitcs(statistcs);
        double min_value = this->getMinStatitcs(statistcs);
        double step = (max_value-min_value)/subdivisions;
        double value_base = (element)*step + min_value;
        for (int i=0; i<statistcs.size(); i++){
            QList<bool> tmp;
            for(int j=0; j<statistcs.at(i).size(); j++){
                double value = statistcs.at(i).at(j).first;
                if (value<value_base){
                    tmp.push_back(false);
                }
                else{
                    tmp.push_back(true);
                }
            }
            result.push_back(tmp);
        }
    }
    return result;
}

QList< QList<significant_type> > ViewPhylogenetics::getSignificantPhylogenetic(QList<QList<QPair<double, double> > > statistcs)
{
    QList< QList<significant_type> > result;
    QSettings s("NuEvo","Pacca");
    s.beginGroup("ConfigAnalysis");
    double alpha = s.value("alfa",5).toDouble();
    s.endGroup();

    for (int i=0; i<statistcs.size(); i++){
        QList<significant_type> tmp;
        for(int j=0; j<statistcs.at(i).size(); j++){
            /* mudar para ZERO as caselas que tiverem, em MP, valores não significativos (Pvalor especificado pelo usuário) */
            if (this->MP.at(i).at(j) > alpha){
                tmp.push_back(insignificant);
            }
            else if (statistcs.at(i).at(j).first >= 0){
                tmp.push_back(positive_significant);
            }
            else{
                tmp.push_back(negative_significant);
            }
        }
        result.push_back(tmp);
    }
    return result;
}

void ViewPhylogenetics::treatMP(QList<QList<QPair<double,double> > > orig)
{
    QSettings s("NuEvo","Pacca");
    s.beginGroup("ConfigAnalysis");
    bool filterPvalue = s.value("filterPvalue",false).toBool();
    double alfa = s.value("alfa",5).toDouble();
    int tailed = s.value("tailed",0).toInt();
    s.endGroup();

    for(int i = 0; i < orig.size(); i++) {
        QList<double> tmpMP;
        for(int j = 0; j < orig.at(i).size(); j++) {
            QPair<double,double> pv = orig.at(i).at(j);
            if(pv.first < pv.second) tmpMP.push_back(pv.first);
            else tmpMP.push_back(pv.second);
        }
        this->MP.push_back(tmpMP);
    }
}

void ViewPhylogenetics::updateMF()
{
    int nCols = this->behavior.size();
    int nRows = this->species.size();
    int interval = this->ui->intervalSlider->value();
    QList< QList<bool> > mask(this->getPhylogenetic(this->MR,this->sizeIntervals,interval));
    char f = 'f';
    for(int i=0; i < nRows; i++){
        for(int j=0; j < nCols; j++){
            QString l;
            l=QString::number(this->MR.at(i).at(j).first,f,4); l+=" ( ";
            l+=QString::number(this->MR.at(i).at(j).second,f,4); l+=" ) ";
            QTableWidgetItem *itMF = new QTableWidgetItem();
            if(!mask.at(i).at(j)) itMF->setText(l);
            this->ui->tableMF->setItem(i,j,itMF);
        }
    }
    this->ui->tableMF->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
}
