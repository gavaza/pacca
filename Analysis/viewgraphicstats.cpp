#include "viewgraphicstats.h"
#include "ui_viewgraphicstats.h"

ViewGraphicStats::ViewGraphicStats(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewGraphicStats)
{
    ui->setupUi(this);
    this->createConnections();
}

ViewGraphicStats::~ViewGraphicStats()
{
    delete ui;
}

void ViewGraphicStats::setData(QList<QString> set_line, QVector<QString> sessionLabels, QList<QVector<QString> > infos, QList<QList<double> > obs, QList<QList<double> > spec, QList<QList<double> > res, QList<QPair<double, double> > pvalor, QList<QMap<int, QPair<double, double> > > VE, QList<QMap<int, QPair<double, double> > > VO, QList<QMap<int, QPair<double, double> > > VR)
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
    if(this->ui->list->count() > 0) this->ui->list->item(0)->setSelected(true);
}

void ViewGraphicStats::createConnections()
{
    connect(this->ui->list,SIGNAL(currentRowChanged(int)),this,SLOT(alter_line(int)));
}

void ViewGraphicStats::alter_line(int i){
    this->clearAll();
    Database db;
    QList<Subjects> subjects = db.getAllSubjects();
    QMap<int,QString> subjectsNames;
    subjectsNames.insert(-1,tr("Todos"));
    for(int k = 0; k < subjects.size(); ++k)
        subjectsNames.insert(subjects[k].getId().toInt(),subjects[k].getName().toString());

    for (int j=0; j<this->session.size(); ++j){
        this->obsData.push_back(this->observed.at(i).at(j));
        this->expData.push_back(this->expected.at(i).at(j));
        this->resData.push_back(this->residue.at(i).at(j));
        this->labels.push_back(this->session.at(j));
        this->ticks.push_back(j+1);
    }

    this->plotSessions();

    QList<int> keys = this->VE.at(i).uniqueKeys();
    QListIterator<int> j(keys);
    int pos = 0;
    this->clearAll();
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
        this->ticks.push_back(pos);
        this->labels.push_back(subjectsNames.value(key));
        this->obsData.push_back(MeanVarO.first);
        this->expData.push_back(MeanVarE.first);
        this->resData.push_back(MeanVarR.first);
        this->voData.push_back(VarO);
        this->veData.push_back(VarE);
        this->vrData.push_back(VarR);
    }
    this->plotSubjects();
}

void ViewGraphicStats::plotSessions()
{
    this->ui->plotObsSessions->showHistogram(this->obsData,this->ticks,QPair<double,double>(0,0),this->labels,
                                             tr("Sessões"),tr("Observado"),tr("Valor Observado - Sessões"),Qt::green);
    this->ui->plotExpSessions->showHistogram(this->expData,this->ticks,QPair<double,double>(0,0),this->labels,
                                             tr("Sessões"),tr("Esperado"),tr("Valor Esperado - Sessões"),Qt::red);
    this->ui->plotResSessions->showHistogram(this->resData,this->ticks,QPair<double,double>(0,0),this->labels,
                                             tr("Sessões"),tr("Resíduo"),tr("Valor do Resíduo - Sessões"),Qt::blue);
}

void ViewGraphicStats::plotSubjects()
{
    this->ui->plotObsSubjects->showHistogram(this->obsData,this->ticks,QPair<double,double>(0,0),this->labels,
                                             tr("Indivíduos"),tr("Observado"),tr("Valor Observado - Indivíduos"),Qt::green);
    this->ui->plotExpSubjects->showHistogram(this->expData,this->ticks,QPair<double,double>(0,0),this->labels,
                                             tr("Indivíduos"),tr("Esperado"),tr("Valor Esperado - Indivíduos"),Qt::red);
    this->ui->plotResSubjects->showHistogram(this->resData,this->ticks,QPair<double,double>(0,0),this->labels,
                                             tr("Indivíduos"),tr("Resíduo"),tr("Valor do Resíduo - Indivíduos"),Qt::blue);
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
