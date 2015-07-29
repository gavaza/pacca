#ifndef SUBJECT_H
#define SUBJECT_H

#include <QVariant>

class Subjects
{
public:
    Subjects();
    Subjects(QVariant id, QVariant name);
    QVariant getId();
    QVariant getName();
    void setId(QVariant id);
    void setName(QVariant name);
private:
    QVariant id;
    QVariant name;

};

#endif // SUBJECT_H
