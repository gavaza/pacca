#include <plotwindow.h>
#include "ui_plotwindow.h"

PlotWindow::PlotWindow(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::PlotWindow)
{
  srand(QDateTime::currentDateTime().toTime_t());
  ui->setupUi(this);
  
  ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                  QCP::iSelectLegend | QCP::iSelectPlottables);
  ui->customPlot->xAxis->setRange(-8, 8);
  ui->customPlot->yAxis->setRange(-5, 5);
  ui->customPlot->axisRect()->setupFullAxesBox();
  
  ui->customPlot->plotLayout()->insertRow(0);
  ui->customPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->customPlot, tr("Título")));
  
  ui->customPlot->xAxis->setLabel("x");
  ui->customPlot->yAxis->setLabel("y");
  ui->customPlot->legend->setVisible(true);
  QFont legendFont = font();
  legendFont.setPointSize(10);
  ui->customPlot->legend->setFont(legendFont);
  ui->customPlot->legend->setSelectedFont(legendFont);
  ui->customPlot->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items  
  // setup policy and connect slot for context menu popup:
  ui->customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
  this->refreshConfig();
  this->createConnections();
}

PlotWindow::~PlotWindow()
{
    delete ui;
}

void PlotWindow::showHistogram(QVector<double> data, QVector<double> ticks, QPair<double, double> variances, QVector<QString> labels, QString labX, QString labY, QString title, QColor color)
{
    ui->customPlot->legend->setVisible(this->showLegend);
    QCPBars *hist = new QCPBars(ui->customPlot->xAxis,ui->customPlot->yAxis);
    hist->setBrush(QBrush(color));
    hist->setPen(QPen(color));
    ui->customPlot->xAxis->setAutoTickLabels(false);
    ui->customPlot->xAxis->setAutoTicks(false);
    ui->customPlot->xAxis->setAutoSubTicks(false);
    ui->customPlot->xAxis->setTickLabelRotation(-90);
    ui->customPlot->xAxis->setLabel(labX);
    ui->customPlot->yAxis->setLabel(labY);
    double miny = 0;
    double maxy = 0;
    QMultiMap<double,QString> map;
    for(int d = 0; d < data.size(); d++){
        map.insertMulti(data.at(d),labels.at(d));
    }
    qSort(data.begin(),data.end(),qGreater<double>());
    int ngraphs = -1;
    if(this->showVariance){
        QPen pen;
        pen.setStyle(Qt::DotLine);
        pen.setWidth(1);
        pen.setColor(QColor(180,180,180));
        ui->customPlot->addGraph(); ngraphs++;
        ui->customPlot->graph(ngraphs)->setName(tr("Variância"));
        ui->customPlot->graph(ngraphs)->setPen(pen);
        ui->customPlot->graph(ngraphs)->setBrush(QBrush(this->colorVar));
        ui->customPlot->addGraph(); ngraphs++;
//        ui->customPlot->legend->removeItem(ui->customPlot->legend->itemCount()-1);
        ui->customPlot->graph(ngraphs)->setPen(pen);
        ui->customPlot->graph(ngraphs-1)->setChannelFillGraph(ui->customPlot->graph(ngraphs));
        ui->customPlot->graph(ngraphs-1)->addData(1,variances.first+variances.second);
        ui->customPlot->graph(ngraphs-1)->addData(data.size(),variances.first+variances.second);
        ui->customPlot->graph(ngraphs)->addData(1,variances.first-variances.second);
        ui->customPlot->graph(ngraphs)->addData(data.size(),variances.first-variances.second);
        ui->customPlot->graph(ngraphs)->rescaleAxes(true);
    }

    if(this->showMean){
        ui->customPlot->addGraph(); ngraphs++;
        ui->customPlot->graph(ngraphs)->setName(tr("Valor Médio"));
        QPen pen; pen.setColor(this->colorMean); pen.setWidth(2); pen.setStyle(Qt::SolidLine);
        ui->customPlot->graph(ngraphs)->setPen(pen);
        ui->customPlot->graph(ngraphs)->setLineStyle(QCPGraph::lsLine);
        ui->customPlot->graph(ngraphs)->addData(1,variances.first);
        ui->customPlot->graph(ngraphs)->addData(data.size(),variances.first);
        ui->customPlot->graph(ngraphs)->rescaleAxes(true);
    }

    for(int d = 0; d < data.size(); d++){
        if(d==0){
            miny = data.at(d);
            maxy = data.at(d);
        } else {
            miny = qMin(data.at(d),miny);
            maxy = qMax(data.at(d),maxy);
        }
        labels.insert(d,map.take(data.at(d)));
        hist->addData(QCPBarData(d+1,data.at(d)));
    }
    double minx = 0;
    double maxx = ticks.last() + 1;
    ui->customPlot->xAxis->setTickVector(ticks);
    ui->customPlot->xAxis->setTickVectorLabels(labels);
    ui->customPlot->xAxis->setRange(minx,maxx);
    ui->customPlot->yAxis->setAutoTickStep(false);
    ui->customPlot->yAxis->setAutoSubTicks(false);
    ui->customPlot->yAxis->setTickStep((maxy-miny)*0.1);
    ui->customPlot->yAxis->setSubTickCount(9);
    ui->customPlot->yAxis->setNumberPrecision(2);
    ui->customPlot->addPlottable(hist);
    ui->customPlot->legend->removeItem(ui->customPlot->legend->itemCount()-1);
    ui->customPlot->rescaleAxes();
    ui->customPlot->plottable(0)->rescaleValueAxis(false);
    ui->customPlot->xAxis->scaleRange(1.1,ui->customPlot->xAxis->range().center());
    ui->customPlot->yAxis->scaleRange(1.1,ui->customPlot->yAxis->range().center());
    ui->customPlot->replot();
}

void PlotWindow::showStackHistogram(QVector<double> lower, QVector<double> upper, QVector<double> ticks, QVector<QString> labels, QString labX, QString labY, QString title, QColor lColor, QColor uColor)
{
    ui->customPlot->legend->setVisible(this->showLegend);
    QCPBars *hLower = new QCPBars(ui->customPlot->xAxis,ui->customPlot->yAxis);
    QCPBars *hUpper = new QCPBars(ui->customPlot->xAxis,ui->customPlot->yAxis);
    hLower->setBrush(QBrush(lColor));
    hLower->setPen(QPen(lColor));
    hUpper->setBrush(QBrush(uColor));
    hUpper->setPen(QPen(uColor));
    hUpper->setName(tr("P-Valor"));
    ui->customPlot->xAxis->setAutoTickLabels(false);
    ui->customPlot->xAxis->setAutoTicks(false);
    ui->customPlot->xAxis->setAutoSubTicks(false);
    ui->customPlot->xAxis->setTickLabelRotation(-90);
    ui->customPlot->xAxis->setLabel(labX);
    ui->customPlot->yAxis->setLabel(labY);
    double miny = 0;
    double maxy = 1.0;
    for(int d = 0; d < lower.size(); d++){
        hLower->addData(QCPBarData(d+1,lower.at(d)));
        hUpper->addData(QCPBarData(d+1,upper.at(d)));
    }
    double minx = 0;
    double maxx = ticks.last() + 1;
    ui->customPlot->xAxis->setTickVector(ticks);
    ui->customPlot->xAxis->setTickVectorLabels(labels);
    ui->customPlot->xAxis->setRange(minx,maxx);
    ui->customPlot->yAxis->setAutoTickStep(false);
    ui->customPlot->yAxis->setAutoSubTicks(false);
    ui->customPlot->yAxis->setTickStep((maxy-miny)*0.1);
    ui->customPlot->yAxis->setSubTickCount(9);
    ui->customPlot->yAxis->setNumberPrecision(2);
    ui->customPlot->addPlottable(hLower);
    ui->customPlot->addPlottable(hUpper);
    hUpper->moveAbove(hLower);

    int ngraph = -1;
    double limits = this->alfa/100;
    if(this->tailed == 0) limits=limits/2;
    if(this->tailed == 1 || this->tailed == 0){
        ngraph++;
        ui->customPlot->addGraph();
        QString name = QString::number(limits*100)+tr("% superior");
        ui->customPlot->graph(ngraph)->setName(name);
        QPen pen; pen.setColor(Qt::black); pen.setWidth(2); pen.setStyle(Qt::DashLine);
        ui->customPlot->graph(ngraph)->setPen(pen);
        ui->customPlot->graph(ngraph)->setLineStyle(QCPGraph::lsLine);
        ui->customPlot->graph(ngraph)->addData(1,1-limits);
        ui->customPlot->graph(ngraph)->addData(upper.size(),1-limits);
        ui->customPlot->graph(ngraph)->rescaleAxes(true);
    }
    if(this->tailed == -1 || this->tailed == 0){
        ngraph++;
        ui->customPlot->addGraph();
        QString name = QString::number(limits*100)+tr("% inferior");
        ui->customPlot->graph(ngraph)->setName(name);
        QPen pen; pen.setColor(Qt::red); pen.setWidth(2); pen.setStyle(Qt::DashLine);
        ui->customPlot->graph(ngraph)->setPen(pen);
        ui->customPlot->graph(ngraph)->setLineStyle(QCPGraph::lsLine);
        ui->customPlot->graph(ngraph)->addData(1,limits);
        ui->customPlot->graph(ngraph)->addData(upper.size(),limits);
        ui->customPlot->graph(ngraph)->rescaleAxes(true);
    }

    ui->customPlot->legend->removeItem(0);
    ui->customPlot->rescaleAxes();
    ui->customPlot->plottable(0)->rescaleValueAxis(false);
    ui->customPlot->xAxis->scaleRange(1.1,ui->customPlot->xAxis->range().center());
    ui->customPlot->yAxis->scaleRange(1.1,ui->customPlot->yAxis->range().center());
    ui->customPlot->replot();
}

void PlotWindow::showFrequenceStats(QMap<QVariant,int> freq, QString xlabel, QString legend, bool sorted)
{
    QCPBars *hist = new QCPBars(ui->customPlot->xAxis,ui->customPlot->yAxis);
    hist->setBrush(QBrush(this->colorFrequence));
    hist->setPen(QPen(this->colorFrequence));
    hist->setName(legend);
    ui->customPlot->xAxis->setAutoTickLabels(false);
    ui->customPlot->xAxis->setAutoTicks(false);
    ui->customPlot->xAxis->setAutoSubTicks(false);
    ui->customPlot->xAxis->setTickLabelRotation(-45);
    ui->customPlot->xAxis->setLabel(xlabel);
    ui->customPlot->yAxis->setLabel("Frequência");
    QVector<QString> labels;
    QVector<double> ticks;
    ticks.push_back(0); labels.push_back("");
    QList<int> values = freq.values();
    if(sorted) qSort(values.begin(),values.end(),qGreater<int>());
    for(int v=0; v < values.size(); v++ ){
        double max = values.at(v);
        labels.push_back(freq.key(max).toString());
        ticks.push_back(v+1);
        hist->addData(QCPBarData(v+1,max));
        freq.remove(freq.key(max));
    }
    ui->customPlot->xAxis->setTickVector(ticks);
    ui->customPlot->xAxis->setTickVectorLabels(labels);
    ui->customPlot->addPlottable(hist);
    ui->customPlot->rescaleAxes();
    ui->customPlot->plottable(0)->rescaleValueAxis(false);

    ui->customPlot->xAxis->scaleRange(1.1,ui->customPlot->xAxis->range().center());
    ui->customPlot->yAxis->scaleRange(1.1,ui->customPlot->yAxis->range().center());
    ui->customPlot->replot();
}

void PlotWindow::createConnections()
{
  // connect slot that ties some axis selections together (especially opposite axes):
  connect(ui->customPlot, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
  // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
  connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
  connect(ui->customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

  // make bottom and left axes transfer their ranges to top and right axes:
  connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

  // connect some interaction slots:
  connect(ui->customPlot, SIGNAL(titleDoubleClick(QMouseEvent*,QCPPlotTitle*)), this, SLOT(titleDoubleClick(QMouseEvent*,QCPPlotTitle*)));
  connect(ui->customPlot, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
  connect(ui->customPlot, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));

  // connect slot that shows a message in the status bar when a graph is clicked:
  connect(ui->customPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*)));
  connect(ui->customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));

  connect(ui->savePdf, SIGNAL(clicked()), this, SLOT(savePdf()));
  connect(ui->savePng, SIGNAL(clicked()), this, SLOT(savePng()));
  connect(ui->saveJpg, SIGNAL(clicked()), this, SLOT(saveJpg()));
  connect(ui->rescale, SIGNAL(clicked()), this, SLOT(rescale()));

}

void PlotWindow::refreshConfig()
{
    QSettings s("NuEvo","Pacca");
    s.beginGroup("ConfigAnalysis");
    this->colorExpected = s.value("colorExpected",QColor("#EB4751")).value<QColor>();
    this->colorObserved = s.value("colorObserved",QColor("#16D600")).value<QColor>();
    this->colorResidue = s.value("colorResidue",QColor("#00D0D6")).value<QColor>();
    this->colorFrequence = s.value("colorFrequence",QColor("#00D0D6")).value<QColor>();
    this->colorLower = s.value("colorLower",QColor(1, 92, 191, 50)).value<QColor>();
    this->colorUpper = s.value("colorUpper",QColor(150, 222, 0, 70)).value<QColor>();
    this->showMean = s.value("showMean",false).toBool();
    this->showVariance = s.value("showVariance",false).toBool();
    this->showLegend = s.value("showLegend",true).toBool();
    this->filterPvalue = s.value("filterPvalue",false).toBool();
    this->showtype = s.value("showType",0).toInt();
    this->testType = s.value("testType",0).toInt();
    this->nPermutations = s.value("nPermutation",50).toInt();
    this->tailed = s.value("tailed",0).toInt();
    this->alfa = s.value("alfa",5).toDouble();
    s.endGroup();
}

void PlotWindow::titleDoubleClick(QMouseEvent* event, QCPPlotTitle* title)
{
  Q_UNUSED(event)
  // Set the plot title by double clicking on it
  bool ok;
  QString newTitle = QInputDialog::getText(this, "", tr("Novo título:"), QLineEdit::Normal, title->text(), &ok);
  if (ok)
  {
    title->setText(newTitle);
    ui->customPlot->replot();
  }
}

void PlotWindow::axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)
{
  // Set an axis label by double clicking on it
  if (part == QCPAxis::spAxisLabel) // only react when the actual axis label is clicked, not tick label or axis backbone
  {
    bool ok;
    QString newLabel = QInputDialog::getText(this, "", tr("Novo nome:"), QLineEdit::Normal, axis->label(), &ok);
    if (ok)
    {
      axis->setLabel(newLabel);
      ui->customPlot->replot();
    }
  }
}

void PlotWindow::legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item)
{
  // Rename a graph by double clicking on its legend item
  Q_UNUSED(legend)
  if (item) // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
  {
    QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
    bool ok;
    QString newName = QInputDialog::getText(this, "", tr("Novo nome do gráfico:"), QLineEdit::Normal, plItem->plottable()->name(), &ok);
    if (ok)
    {
      plItem->plottable()->setName(newName);
      ui->customPlot->replot();
    }
  }
}

void PlotWindow::selectionChanged()
{
  /*
   normally, axis base line, axis tick labels and axis labels are selectable separately, but we want
   the user only to be able to select the axis as a whole, so we tie the selected states of the tick labels
   and the axis base line together. However, the axis label shall be selectable individually.
   
   The selection state of the left and right axes shall be synchronized as well as the state of the
   bottom and top axes.
   
   Further, we want to synchronize the selection of the graphs with the selection state of the respective
   legend item belonging to that graph. So the user can select a graph by either clicking on the graph itself
   or on its legend item.
  */
  
  // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
      ui->customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
  {
    ui->customPlot->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    ui->customPlot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }
  // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
      ui->customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
  {
    ui->customPlot->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    ui->customPlot->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }
  
  // synchronize selection of graphs with selection of corresponding legend items:
  for (int i=0; i<ui->customPlot->graphCount(); ++i)
  {
    QCPGraph *graph = ui->customPlot->graph(i);
    QCPPlottableLegendItem *item = ui->customPlot->legend->itemWithPlottable(graph);
    if (item->selected() || graph->selected())
    {
      item->setSelected(true);
      graph->setSelected(true);
    }
  }
}

void PlotWindow::mousePress()
{
  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged
  
  if (ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot->axisRect()->setRangeDrag(ui->customPlot->xAxis->orientation());
  else if (ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot->axisRect()->setRangeDrag(ui->customPlot->yAxis->orientation());
  else
    ui->customPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void PlotWindow::mouseWheel()
{
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed
  
  if (ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot->axisRect()->setRangeZoom(ui->customPlot->xAxis->orientation());
  else if (ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot->axisRect()->setRangeZoom(ui->customPlot->yAxis->orientation());
  else
    ui->customPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void PlotWindow::removeSelectedGraph()
{
  if (ui->customPlot->selectedGraphs().size() > 0)
  {
    ui->customPlot->removeGraph(ui->customPlot->selectedGraphs().first());
    ui->customPlot->replot();
  }
}

void PlotWindow::removeAllGraphs()
{
  ui->customPlot->clearGraphs();
  ui->customPlot->replot();
}

void PlotWindow::contextMenuRequest(QPoint pos)
{
  QMenu *menu = new QMenu(this);
  menu->setAttribute(Qt::WA_DeleteOnClose);
  
  if (ui->customPlot->legend->selectTest(pos, false) >= 0) // context menu on legend requested
  {
    menu->addAction(tr("Mover para canto superior esquerdo"), this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignLeft));
    menu->addAction(tr("Mover para centro superior"), this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignHCenter));
    menu->addAction(tr("Mover para canto superior direito"), this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignRight));
    menu->addAction(tr("Mover para canto inferior direito"), this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignRight));
    menu->addAction(tr("Mover para centro inferior"), this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignHCenter));
    menu->addAction(tr("Mover para canto inferior esquerdo"), this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
  } else  // general context menu on graphs requested
  {
    if (ui->customPlot->selectedGraphs().size() > 0)
      menu->addAction("Remove selected graph", this, SLOT(removeSelectedGraph()));
    if (ui->customPlot->graphCount() > 0)
      menu->addAction("Remove all graphs", this, SLOT(removeAllGraphs()));
  }
  
  menu->popup(ui->customPlot->mapToGlobal(pos));
}

void PlotWindow::moveLegend()
{
  if (QAction* contextAction = qobject_cast<QAction*>(sender())) // make sure this slot is really called by a context menu action, so it carries the data we need
  {
    bool ok;
    int dataInt = contextAction->data().toInt(&ok);
    if (ok)
    {
      ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
      ui->customPlot->replot();
    }
  }
}

void PlotWindow::graphClicked(QCPAbstractPlottable *plottable)
{
}

QString PlotWindow::getFilename(QString type)
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Salvar Arquivo"), QDir::homePath(),type);
    return filename;
}

void PlotWindow::rescale()
{
    this->ui->customPlot->xAxis->rescale(true);
    this->ui->customPlot->yAxis->rescale(true);
    this->ui->customPlot->xAxis->scaleRange(1.1,this->ui->customPlot->xAxis->range().center());
    this->ui->customPlot->yAxis->scaleRange(1.1,this->ui->customPlot->yAxis->range().center());
    this->ui->customPlot->replot();
}

void PlotWindow::savePdf()
{
    QString filename = this->getFilename("pdf");
    if(filename != ""){
        this->ui->customPlot->saveJpg(filename);
    }
}

void PlotWindow::savePng()
{
    QString filename = this->getFilename("png");
    if(filename != ""){
        this->ui->customPlot->savePng(filename);
    }
}

void PlotWindow::saveJpg()
{
    QString filename = this->getFilename("jpg");
    if(filename != ""){
        this->ui->customPlot->saveJpg(filename);
    }
}




