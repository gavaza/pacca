#ifndef TEXT_H
#define TEXT_H

#include "text_global.h"

#include <QDebug>
#include <QDir>

#include <QFile>
#include <QString>
#include <QDataStream>
#include <QList>
#include <QRegExp>

#include "database.h"

enum types_of_files{
    odf, // simple
    mdf, // complex
    unknown
};

#ifndef INPUTTEXT_VARIABLES
const int TITLE_SESSION_SIZE_SIMPLE=3;
const int TITLE_SESSION_SIZE_COMPLEX=7;
#define INPUTTEXT_VARIABLES
#endif

class TEXTSHARED_EXPORT Text
{

public:
    Text();
    QList<Sessions> executeImportText(QStringList filename);
    void executeExportText(QString filename, QList<Actions> actions, QList<QString> infos);
    void executeExportTextMDF(QString filename, QList< QList<Actions> > list_actions, QList< QList<QString> > list_infos);


private:
    QString identifySession(QString specie, QString individuo, QString id, QString author);
};

#endif // TEXT_H
