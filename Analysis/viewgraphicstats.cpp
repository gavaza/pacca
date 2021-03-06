#include "viewgraphicstats.h"
#include "ui_viewgraphicstats.h"

ViewGraphicStats::ViewGraphicStats(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewGraphicStats)
{
    ui->setupUi(this);
    this->loadConfig();
    this->createConnections();
}

ViewGraphicStats::~ViewGraphicStats()
{
    delete ui;
}

void ViewGraphicStats::setData(QList<QString> set_line, QVector<QString> sessionLabels,
                               QList<QVector<QString> > infos, QList<QList<double> > obs,
                               QList<QList<double> > spec, QList<QList<double> > res,
                               QList< QList< QPair<bool, double> > > pvalor, QList<QMap<int, QPair<double, double> > > VE,
                               QList<QMap<int, QPair<double, double> > > VO, QList<QMap<int, QPair<double, double> > > VR,
                               QList<QMap<int, QPair<bool, double> > > VP)
{
    this->ui->list->addItems(set_line);

    this->session = sessionLabels;
    this->infos = infos;
    this->observed = obs;
    this->expected = spec;
    this->residue = res;
    this->pvalues = pvalor;
    this->VE = VE;
    this->VO = VO;
    this->VR = VR;
    this->VP = VP;
    if(this->ui->list->count() > 0){
        this->ui->list->item(0)->setSelected(true);
        this->alter_line(0);
    }
}

void ViewGraphicStats::createConnections()
{
    connect(this->ui->list,SIGNAL(currentRowChanged(int)),this,SLOT(alter_line(int)));
    connect(this->ui->filter,SIGNAL(clicked(bool)),this,SLOT(update()));
}

void ViewGraphicStats::loadConfig()
{
    QSettings s("NuEvo","Pacca");
    s.beginGroup("ConfigAnalysis");
    this->colorExpected = s.value("colorExpected",QColor("#EB4751")).value<QColor>();
    this->colorObserved = s.value("colorObserved",QColor("#16D600")).value<QColor>();
    this->colorResidue = s.value("colorResidue",QColor("#00D0D6")).value<QColor>();
    this->colorUpper = s.value("colorUpper",QColor(150, 222, 0, 70)).value<QColor>();
    this->filterPvalue = s.value("filterPvalue",false).toBool();
    s.endGroup();

    Database db;
    QList<Subjects> subjects = db.getAllSubjects();
    this->subjectsNames.insert(-1,tr("Todos"));
    for(int k = 0; k < subjects.size(); ++k)
        this->subjectsNames.insert(subjects[k].getId().toInt(),subjects[k].getName().toString());
}

void ViewGraphicStats::alter_line(int i){
    this->currentRow = i;
    this->clearAll();
    int tick = 0;
    for (int j=0; j<this->session.size(); ++j){
        double pv = 0;
        bool signif = true;
        if(this->pvalues.at(i).size() != 0){
            signif = this->pvalues.at(i).at(j).first;
            pv = this->pvalues.at(i).at(j).second;
        }
        if(signif || !this->ui->filter->isChecked()){
            this->pvalData.push_back(pv);
            this->obsData.push_back(this->observed.at(i).at(j));
            this->expData.push_back(this->expected.at(i).at(j));
            this->resData.push_back(this->residue.at(i).at(j));
            this->labels.push_back(this->session.at(j));
            this->voData.push_back(0);
            this->veData.push_back(0);
            this->vrData.push_back(0);
            this->ticks.push_back(++tick);
        }
    }
    this->plotSessions();
    QList<int> keys = this->VE.at(i).uniqueKeys();
    QListIterator<int> j(keys);
    int pos = 0;
    this->clearAll();
    tick=0;
    while (j.hasNext()){
        ++pos;
        int key = j.next();
        QPair<double,double> MeanVarE = this->VE.at(i).value(key);
        QPair<double,double> MeanVarO = this->VO.at(i).value(key);
        QPair<double,double> MeanVarR = this->VR.at(i).value(key);
        double VarE = MeanVarE.second;
        double VarO = MeanVarO.second;
        double VarR = MeanVarR.second;
        if (VarE == -1) VarE = 0;
        if (VarO == -1) VarO = 0;
        if (VarR == -1) VarR = 0;
        double pv = 0;
        bool signif = true;
        if(this->VP.at(i).size() != 0){
            signif = this->VP.at(i).value(key).first;
            pv = this->VP.at(i).value(key).second;
        }
        if(signif || !this->ui->filter->isChecked()){
            this->pvalData.push_back(pv);
            this->ticks.push_back(++tick);
            this->labels.push_back(this->subjectsNames.value(key));
            this->obsData.push_back(MeanVarO.first);
            this->expData.push_back(MeanVarE.first);
            this->resData.push_back(MeanVarR.first);
            this->voData.push_back(VarO);
            this->veData.push_back(VarE);
            this->vrData.push_back(VarR);
        }
    }
    this->plotSubjects();
}

void ViewGraphicStats::plotSessions()
{
    this->ui->plotObsSessions->showHistogram(this->obsData,this->ticks,this->voData,0,this->labels,
                                             tr("Sessões"),tr("Observado"),tr("Valor Observado - Sessões"),this->colorObserved);
    this->ui->plotExpSessions->showHistogram(this->expData,this->ticks,this->veData,0,this->labels,
                                             tr("Sessões"),tr("Esperado"),tr("Valor Esperado - Sessões"),this->colorExpected);
    this->ui->plotResSessions->showHistogram(this->resData,this->ticks,this->vrData,0,this->labels,
                                             tr("Sessões"),tr("Resíduo"),tr("Valor do Resíduo - Sessões"),this->colorResidue);
    this->ui->plotPvalSessions->showHistogram(this->pvalData,this->ticks,QPair<double,double>(0,0),this->labels,
                                             tr("Sessões"),tr("P-Valor"),tr("P-Valores - Sessões"),this->colorUpper);
}

void ViewGraphicStats::plotSubjects()
{
    this->ui->plotObsSubjects->showHistogram(this->obsData,this->ticks,this->voData,0,this->labels,
                                             tr("Indivíduos"),tr("Observado"),tr("Valor Observado - Indivíduos"),this->colorObserved);
    this->ui->plotExpSubjects->showHistogram(this->expData,this->ticks,this->veData,0,this->labels,
                                             tr("Indivíduos"),tr("Esperado"),tr("Valor Esperado - Indivíduos"),this->colorExpected);
    this->ui->plotResSubjects->showHistogram(this->resData,this->ticks,this->vrData,0,this->labels,
                                             tr("Indivíduos"),tr("Resíduo"),tr("Valor do Resíduo - Indivíduos"),this->colorResidue);
    this->ui->plotPvalSubjects->showHistogram(this->pvalData,this->ticks,QPair<double,double>(0,0),this->labels,
                                             tr("Indivíduos"),tr("P-valor"),tr("P-Valores - Indivíduos"),this->colorUpper);
}

void ViewGraphicStats::clearAll()
{
    this->obsData.clear();
    this->expData.clear();
    this->resData.clear();
    this->pvalData.clear();
    this->voData.clear();
    this->veData.clear();
    this->vrData.clear();
    this->labels.clear();
    this->ticks.clear();
}

void ViewGraphicStats::update()
{
    this->alter_line(this->currentRow);
}
