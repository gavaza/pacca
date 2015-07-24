#include "states.h"

States::States()
{
}

States::States(QString description, unsigned int id){
    this->description = description;
    this->id = id;
}

void States::setDescription(QString description)
{
    this->description = description;
}

QString States::getDescription(){
    return this->description;
}

void States::setId(unsigned int id)
{
    this->id = id;
}

unsigned int States::getId(){
    return this->id;
}
