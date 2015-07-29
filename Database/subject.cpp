#include "subject.h"

Subjects::Subjects()
{
}

Subjects::Subjects(QVariant id, QVariant name)
{
    this->id = id;
    this->name = name;
}

QVariant Subjects::getId()
{
    return this->id;
}

QVariant Subjects::getName()
{
    return this->name;
}

void Subjects::setId(QVariant id)
{
    this->id = id;
}

void Subjects::setName(QVariant name)
{
    this->name = name;
}
