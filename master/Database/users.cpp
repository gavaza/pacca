#include "users.h"

Users::Users()
{
}

Users::Users(QVariant n, QVariant id)
{
    this->id = id;
    this->name = n;
}

void Users::setId(QVariant id)
{
    this->id = id;
}

QVariant Users::getId()
{
    return this->id;
}

void Users::setName(QVariant name)
{
    this->name = name;
}

void Users::setName(QString name)
{
    this->name = QVariant(name);
}

QVariant Users::getName()
{
    return this->name;
}
