#include "dialogconfigstats.h"
#include "ui_dialogconfigstats.h"

DialogConfigStats::DialogConfigStats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfigStats)
{
    ui->setupUi(this);
    this->colorDialog = new QColorDialog(this);
    connect(this->ui->expected,SIGNAL(clicked()),this,SLOT(selectColorExpected()));
    connect(this->ui->observed,SIGNAL(clicked()),this,SLOT(selectColorObserved()));
    connect(this->ui->residue,SIGNAL(clicked()),this,SLOT(selectColorResidue()));
    connect(this->ui->frequence,SIGNAL(clicked()),this,SLOT(selectColorFrequence()));
    connect(this->ui->cLower,SIGNAL(clicked()),this,SLOT(selectColorFrequence()));
    connect(this->ui->cUpper,SIGNAL(clicked()),this,SLOT(selectColorFrequence()));
    connect(this->ui->buttonBox,SIGNAL(accepted()),this,SLOT(saveChanges()));
    this->load();
}

DialogConfigStats::~DialogConfigStats()
{
    delete ui;
}

void DialogConfigStats::load()
{
    QPixmap px(48,48);
    QSettings s("NuEvo","Pacca");
    s.beginGroup("ConfigAnalysis");
    this->colorExpected = s.value("colorExpected",QColor("#EB4751")).value<QColor>();
    px.fill(this->colorExpected);
    this->ui->expected->setIcon(px);
    this->colorObserved = s.value("colorObserved",QColor("#16D600")).value<QColor>();
    px.fill(this->colorObserved);
    this->ui->observed->setIcon(px);
    this->colorResidue = s.value("colorResidue",QColor("#00D0D6")).value<QColor>();
    px.fill(this->colorResidue);
    this->ui->residue->setIcon(px);
    this->colorFrequence = s.value("colorFrequence",QColor("#00D0D6")).value<QColor>();
    px.fill(this->colorFrequence);
    this->ui->frequence->setIcon(px);
    this->colorLower = s.value("colorLower",QColor(1, 92, 191, 50)).value<QColor>();
    px.fill(this->colorLower);
    this->ui->cLower->setIcon(px);
    this->colorUpper = s.value("colorUpper",QColor(150, 222, 0, 70)).value<QColor>();
    px.fill(this->colorUpper);
    this->ui->cUpper->setIcon(px);
    this->ui->mean->setChecked(s.value("showMean",false).toBool());
    this->ui->variance->setChecked(s.value("showVariance",false).toBool());
    this->ui->legend->setChecked(s.value("showLegend",true).toBool());
    this->ui->filterPvalue->setChecked(s.value("filterPvalue",false).toBool());
    int type = s.value("showType",0).toInt();
    switch (type) {
    case 0:
        this->ui->viewGraph->setChecked(true);
        break;
    case 1:
        this->ui->viewTable->setChecked(true);
        break;
    case 2:
        this->ui->viewNet->setChecked(true);
        break;
    case 3:
        this->ui->viewFile->setChecked(true);
        break;
    default:
        break;
    }
    type = s.value("testType",0).toInt();
    switch (type) {
    case 0:
        this->ui->tResidue->setChecked(true);
        break;
    case 1:
        this->ui->tVariance->setChecked(true);
        break;
    default:
        break;
    }
    this->ui->seed->setValue(s.value("seed",-1).toInt());
    this->ui->nPermutations->setValue(s.value("nPermutation",50).toInt());
    type = s.value("tailed",0).toInt();
    switch (type) {
    case -1:
        this->ui->lower->setChecked(true);
        break;
    case 0:
        this->ui->bitailed->setChecked(true);
        break;
    case 1:
        this->ui->upper->setChecked(true);
        break;
    default:
        break;
    }
    this->ui->alfa->setValue(s.value("alfa",5).toDouble());
    s.endGroup();
}

void DialogConfigStats::saveChanges()
{
    QSettings s("NuEvo","Pacca");
    s.beginGroup("ConfigAnalysis");
    s.setValue("colorExpected",this->colorExpected);
    s.setValue("colorObserved",this->colorObserved);
    s.setValue("colorResidue",this->colorResidue);
    s.setValue("colorFrequence",this->colorFrequence);
    s.setValue("colorLower",this->colorLower);
    s.setValue("colorUpper",this->colorUpper);
    s.setValue("showMean",this->ui->mean->isChecked());
    s.setValue("showVariance",this->ui->variance->isChecked());
    s.setValue("showLegend",this->ui->legend->isChecked());
    int type = -1;
    if(this->ui->viewGraph->isChecked()) type = 0;
    if(this->ui->viewTable->isChecked()) type = 1;
    if(this->ui->viewNet->isChecked()) type = 2;
    if(this->ui->viewFile->isChecked()) type = 3;
    s.setValue("showType",type);
    if(this->ui->tResidue->isChecked()) type = 0;
    if(this->ui->tVariance->isChecked()) type = 1;
    s.setValue("testType",type);
    s.setValue("seed",this->ui->seed->value());
    s.setValue("nPermutation",this->ui->nPermutations->value());
    if(this->ui->lower->isChecked()) type = -1;
    if(this->ui->bitailed->isChecked()) type = 0;
    if(this->ui->upper->isChecked()) type = 1;
    s.setValue("tailed",type);
    s.setValue("alfa",this->ui->alfa->value());
    s.setValue("filterPvalue",this->ui->filterPvalue->isChecked());
    s.endGroup();
}

void DialogConfigStats::selectColorExpected()
{
    QColor newColor = QColorDialog::getColor(colorExpected,this);
    if(newColor.isValid()) {
        QPixmap px(48,48);
        px.fill(newColor);
        this->ui->expected->setIcon(px);
        this->colorExpected = newColor;
    }
}

void DialogConfigStats::selectColorObserved()
{
    QColor newColor = QColorDialog::getColor(colorObserved,this);
    if(newColor.isValid()) {
        QPixmap px(48,48);
        px.fill(newColor);
        this->ui->observed->setIcon(px);
        this->colorObserved = newColor;
    }
}

void DialogConfigStats::selectColorResidue()
{
    QColor newColor = QColorDialog::getColor(colorResidue,this);
    if(newColor.isValid()) {
        QPixmap px(48,48);
        px.fill(newColor);
        this->ui->residue->setIcon(px);
        this->colorExpected = newColor;
    }
}

void DialogConfigStats::selectColorFrequence()
{
    QColor newColor = QColorDialog::getColor(colorFrequence,this);
    if(newColor.isValid()) {
        QPixmap px(48,48);
        px.fill(newColor);
        this->ui->frequence->setIcon(px);
        this->colorFrequence = newColor;
    }
}

void DialogConfigStats::selectColorLower()
{
    QColor newColor = QColorDialog::getColor(colorLower,this);
    if(newColor.isValid()) {
        QPixmap px(48,48);
        px.fill(newColor);
        this->ui->cLower->setIcon(px);
        this->colorLower = newColor;
    }
}

void DialogConfigStats::selectColorUpper()
{
    QColor newColor = QColorDialog::getColor(colorUpper,this);
    if(newColor.isValid()) {
        QPixmap px(48,48);
        px.fill(newColor);
        this->ui->cUpper->setIcon(px);
        this->colorUpper = newColor;
    }
}
