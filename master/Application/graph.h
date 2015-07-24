#ifndef GRAPH_H
#define GRAPH_H

#include <QMap>
#include <GraphWindow.h>

class Node
{
public:
    Node(){}
    Node(QString name, QString info){
        this->name=name;
        this->info=info;
    }
    void setWeight(double w){this->weight=w;}
    double getWeight(){return this->weight;}
    QString getName(){return this->name;}
    QString getInfo(){return this->info;}
private:
    QString name;
    QString info;
    double weight;
};

class Edge
{
public:
    Edge(){}
    Edge(QString name, QString start, QString end){
        this->name=name;
        this->start=start;
        this->end=end;
    }
    void setWeight(double w){this->weight=w;}
    double getWeight(){return this->weight;}
    QString getStart(){return this->start;}
    QString getEnd(){return this->end;}
private:
    QString name;
    QString start;
    QString end;
    double weight;
};


class Graph
{
public:
    Graph();
    void addNode(QString name, QString info, double size=1, double inc=1);
    void removeNode(QString name);
    void addEdge(QString name, QString start, QString end, double size=1, double inc=1);
    void removeEdge(QString name);
    GraphWindow* getGraphWindow();
private:
    GraphWindow* gw;
    QMap<QString,Node*> nodes;
    QMap<QString,Edge*> edges;
};

#endif // GRAPH_H
