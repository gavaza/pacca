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
#include <QThread>
#include <QtCore>

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

class TEXTSHARED_EXPORT Text : public QThread
{
    Q_OBJECT

public:
    Text();
    ~Text();
    QList<Sessions> executeImportText(QStringList filename);
    void executeExportText(QString filename, QList<Actions> actions, QList<QString> infos);
    void executeExportTextMDF(QString filename, QList< QList<Actions> > list_actions, QList< QList<QString> > list_infos);

private:
    QString identifySession(QString specie, QString individuo, QString id, QString author);
    void run();
    QFile id_file;
    QStringList filename;
    int qtd_files;
    int processed_files;

private slots:
    void update_processed();

signals:
    void percent_files_processed(double);
    void percent_actual_file(double);
};

#endif // TEXT_H
