#include "dictionary.h"

Dictionary::Dictionary()
{
}

void Dictionary::setName(QString name)
{
    this->name = name;
}

QString Dictionary::getName()
{
    return this->name;
}

void Dictionary::insertEntry(QString code, QString word)
{
    this->entries.insert(code,word);
}

QString Dictionary::getWord(QString code)
{
    return this->entries.value(code,"");
}

QMap<QString, QString> Dictionary::getEntries()
{
    return this->entries;
}
