#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QString>
#include <QMap>

class Dictionary
{
public:
    Dictionary();
    void setName(QString name);
    QString getName();
    void insertEntry(QString code, QString word);
    QString getWord(QString code);
    QMap<QString,QString> getEntries();
private:
    QString name;
    QMap<QString,QString> entries;
};

#endif // DICTIONARY_H
