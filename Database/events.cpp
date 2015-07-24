#include "events.h"

Events::Events()
{
}

Events::Events(QString description, unsigned int id){
    this->description = description;
    this->id = id;
}

void Events::setDescription(QString description)
{
    this->description = description;
}

QString Events::getDescription(){
    return this->description;
}

void Events::setId(unsigned int id)
{
    this->id = id;
}

unsigned int Events::getId(){
    return this->id;
}
