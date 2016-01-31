#include "graph.h"

Graph::Graph()
{
    this->gw = new GraphWindow();
}

void Graph::addNode(QString name, QString info, double size, double inc)
{
    if(!this->nodes.contains(name)){
        this->gw->addNode(name);
        Node* n = new Node(name,info);
        n->setWeight(size);
        this->nodes.insert(name,n);
        this->gw->updateNode(name,QString::number(size));
    } else {
        Node *n = this->nodes.value(name);
        double w = n->getWeight()+inc;
        n->setWeight(w);
        this->gw->updateNode(name,QString::number(w));
    }
}

void Graph::removeNode(QString name)
{

}

void Graph::addEdge(QString name, QString start, QString end, double size, double inc)
{
    if(!this->edges.contains(name)){
        this->gw->addEdge(name,start,end);
        Edge *e = new Edge(name,start,end);
        e->setWeight(size);
        this->edges.insert(name,e);
    } else {
        Edge *e = this->edges.value(name);
        double w = e->getWeight()+inc;
        e->setWeight(w);
        this->gw->updateEdge(name,QString::number(w));
    }
}

void Graph::removeEdge(QString name)
{
}

GraphWindow *Graph::getGraphWindow()
{
    return this->gw;
}
