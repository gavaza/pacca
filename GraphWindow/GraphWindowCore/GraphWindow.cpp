/***************************************************************
QGVCore Sample
Copyright (c) 2014, Bergont Nicolas, All rights reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3.0 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library.
***************************************************************/
#include "GraphWindow.h"
#include "moc_GraphWindow.cpp"
#include "ui_GraphWindow.h"
#include <QMessageBox>

GraphWindow::GraphWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);

    _scene = new QGVScene("DEMO", this);
    ui->graphicsView->setScene(_scene);

    connect(_scene, SIGNAL(nodeContextMenu(QGVNode*)), SLOT(nodeContextMenu(QGVNode*)));
    connect(_scene, SIGNAL(nodeDoubleClick(QGVNode*)), SLOT(nodeDoubleClick(QGVNode*)));
    connect(this->_scene, SIGNAL(edgeContextMenu(QGVEdge*)), SLOT(edgeContextMenu(QGVEdge*)));
    connect(this->_scene, SIGNAL(edgeDoubleClick(QGVEdge*)), SLOT(edgeDoubleClick(QGVEdge*)));
}

GraphWindow::~GraphWindow()
{
    delete ui;
}

void GraphWindow::addNode(QString name, QString size){
    QGVNode *node = this->_scene->addNode(name);
    this->nodes.insert(name,node);
    this->updateNode(name,size);
}

void GraphWindow::updateNode(QString name, QString size){
    QGVNode *node = this->nodes.value(name);
    node->setAttribute("height",size);
    node->setAttribute("width",size);
}

void GraphWindow::addEdge(QString name, QString node_from, QString node_to, QString size){
    QGVEdge *edge = this->_scene->addEdge(this->nodes.value(node_from),this->nodes.value(node_to),size);
    this->edges.insert(name,edge);
    this->updateEdge(name,size);
}

void GraphWindow::updateEdge(QString name, QString size){
    QGVEdge *edge = this->edges.value(name);
    edge->setAttribute("width",size);
    edge->setLabel(size);
}

void GraphWindow::drawGraph(QString layout)
{
    //Configure scene attributes
//    _scene->setGraphAttribute("label", "GRAPH");

    _scene->setGraphAttribute("layout", layout);
    _scene->setGraphAttribute("splines", "polyline");
    _scene->setGraphAttribute("rankdir", "LR");
    _scene->setGraphAttribute("nodesep", "0.3");

    _scene->setNodeAttribute("shape","circle");
    _scene->setNodeAttribute("style", "filled");
    _scene->setNodeAttribute("fillcolor", "white");

    //Layout scene
    _scene->applyLayout();

    //Fit in view
    ui->graphicsView->fitInView(_scene->sceneRect(), Qt::KeepAspectRatio);
}

void GraphWindow::nodeContextMenu(QGVNode *node)
{
    //Context menu exemple
    QMenu menu(node->label());

    menu.addSeparator();
    menu.addAction(tr("Informações"));
    menu.addAction(tr("Opções"));

    QAction *action = menu.exec(QCursor::pos());

    if(action == 0){
        /* nothing */
    }
    else if (action == menu.actions().at(1)){
        QMessageBox::information(this, tr("Informações do nó selecionado"), tr("Informações do nó %1").arg(node->label()));
    }
    else if (action == menu.actions().at(2)){
        QMessageBox::information(this, tr("Opções do nó selecionado"), tr("Opções do nó %1").arg(node->label()));
    }
    else{
        /* nothing */
    }
    return;
}

void GraphWindow::nodeDoubleClick(QGVNode *node)
{
    QMessageBox::information(this, tr("Informações do nó"), tr("Valor do nó: %1").arg(node->getAttribute("value")));
}

void GraphWindow::edgeContextMenu(QGVEdge *edge)
{
    //Context menu exemple
    QMenu menu(edge->label());

    menu.addSeparator();
    menu.addAction(tr("Informações"));
    menu.addAction(tr("Opções"));

    QAction *action = menu.exec(QCursor::pos());

    if(action == 0){
        /* nothing */
    }
    else if (action == menu.actions().at(1)){
        QMessageBox::information(this, tr("Informações da aresta selecionada"), tr("Informações da aresta %1").arg(edge->label()));
    }
    else if (action == menu.actions().at(2)){
        QMessageBox::information(this, tr("Opções da aresta selecionada"), tr("Opções da aresta %1").arg(edge->label()));
    }
    else{
        /* nothing */
    }
    return;
}

void GraphWindow::edgeDoubleClick(QGVEdge *edge)
{
    QMessageBox::information(this, tr("Aresta selecionada"), tr("Aresta %1").arg(edge->label()));
}

void GraphWindow::updateEdgesNormalization(){
    double max_size = 0;
    double min_size = -1;
    foreach (QGVEdge* edge, this->edges.values()) {
        double actual_size = edge->getAttribute("width").toDouble();
        max_size = actual_size>max_size?actual_size:max_size;
        min_size = (min_size==-1)?actual_size:(actual_size<min_size?actual_size:min_size);
    }
    foreach (QGVEdge* edge, this->edges.values()) {
        double ratio = max_size/min_size;
        double new_size = (ratio*edge->getAttribute("width").toDouble()/max_size);
        edge->setAttribute("value",edge->getAttribute("width"));
        edge->setAttribute("width",QString::number(new_size));
        edge->setAttribute("color",this->getColor(max_size,new_size));
    }
}

void GraphWindow::updateNodesNormalization(){
    double max_size = 0;
    double min_size = -1;
    foreach (QGVNode* node, this->nodes.values()) {
        double actual_size = node->getAttribute("width").toDouble();
        max_size = actual_size>max_size?actual_size:max_size;
        min_size = (min_size==-1)?actual_size:(actual_size<min_size?actual_size:min_size);
    }
    foreach (QGVNode* node, this->nodes.values()) {
        double ratio = max_size/min_size;
        double new_size = (ratio*node->getAttribute("width").toDouble()/max_size);
        node->setAttribute("value",node->getAttribute("width"));
        node->setAttribute("height",QString::number(new_size));
        node->setAttribute("width",QString::number(new_size));
        node->setAttribute("fillcolor",this->getColor(max_size,new_size));
        node->setAttribute("fillcolor",QColor(150,150,150).name());
    }
}

QString GraphWindow::getColor(double max, double value){
    double ratio = value/max;
    unsigned int green = 0;
    unsigned int blue = 255*(ratio<=0.5?1:(1-ratio));
    unsigned int red = 255*(ratio>=0.5?1:ratio);
    return QColor(red,green,blue).name();
}
