#include "species.h"

Species::Species()
{
}

Species::Species(QVariant n, QVariant id)
{
    this->id = id;
    this->name = n;
}

void Species::setId(QVariant id)
{
    this->id = id;
}

QVariant Species::getId()
{
    return this->id;
}

void Species::setName(QVariant name)
{
    this->name = name;
}

void Species::setName(QString name)
{
    this->name = QVariant(name);
}

QVariant Species::getName()
{
    return this->name;
}
