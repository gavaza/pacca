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
#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGVScene.h>
#include <QDebug>
#include <QGVNode.h>
#include <QGVEdge.h>
#include <QMenu>

#include "graphwindow_global.h"

namespace Ui {
class GraphWindow;
}

class GRAPHWINDOWSHARED_EXPORT GraphWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit GraphWindow(QWidget *parent = 0);
    ~GraphWindow();
    void drawGraph(QString layout = "dot");
    void addNode(QString name, QString size="1");
    void addEdge(QString name, QString node_from, QString node_to, QString size="1");
    void updateNode(QString name, QString size);
    void getNode(QString name);
    void updateEdge(QString name, QString size);
    void updateEdgesNormalization();
    void updateNodesNormalization();

private slots:
    void nodeContextMenu(QGVNode *node);
    void nodeDoubleClick(QGVNode *node);
    void edgeContextMenu(QGVEdge *edge);
    void edgeDoubleClick(QGVEdge *edge);

private:
    Ui::GraphWindow *ui;
    QMap<QString,QGVNode*> nodes;
    QMap<QString,QGVEdge*> edges;
    QGVScene *_scene;
    QString getColor(double max, double value);
};

#endif // GRAPHWINDOW_H
