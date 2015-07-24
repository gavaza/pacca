#include "sessions.h"

Sessions::Sessions()
{
}

Sessions::Sessions(QVariant d, QVariant o, QVariant s, QVariant dateD, QVariant dateS, QVariant id)
{
    this->id = id;
    this->decoder = d;
    this->observer = o;
    this->subject = s;
    this->dateDecoding = dateD;
    this->dateSession = dateS;
}

void Sessions::setId(QVariant id)
{
    this->id = id;
}

QVariant Sessions::getId()
{
    return this->id;
}

void Sessions::setDecoder(QVariant decoder)
{
    this->decoder = decoder;
}

QVariant Sessions::getDecoder()
{
    return this->decoder;
}

void Sessions::setObserver(QVariant observer)
{
    this->observer = observer;
}

QVariant Sessions::getObserver()
{
    return this->observer;
}

void Sessions::setSubject(QVariant subject)
{
    this->subject = subject;
}

QVariant Sessions::getSubject()
{
    return this->subject;
}

void Sessions::setDateDecoding(QVariant date)
{
    this->dateDecoding = date;
}

QVariant Sessions::getDateDecoding()
{
    return this->dateDecoding;
}

void Sessions::setDescription(QVariant desc)
{
    this->description = desc;
}

QVariant Sessions::getDescription()
{
    return this->description;
}

void Sessions::setDateSession(QVariant date)
{
    this->dateSession = date;
}

QVariant Sessions::getDateSession()
{
    return this->dateSession;
}

void Sessions::setActions(QList<Actions> action){
    this->actions = action;
}

QList<Actions> Sessions::getActions()
{
    return this->actions;
}

void Sessions::addAction(Actions action)
{
    this->actions.push_back(action);
}

void Sessions::setSpecies(QVariant specie)
{
    this->specie = specie;
}

QVariant Sessions::getSpecies()
{
    return this->specie;
}
