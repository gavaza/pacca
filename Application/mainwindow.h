#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QApplication>
#include <QTranslator>
#include <QStandardPaths>
#include <QDir>

#include <QMainWindow>
#include <QFile>
#include <QString>
#include <QFileDialog>
#include <QDataStream>
#include <QList>
#include <QRegExp>
#include <QDebug>
#include <QSettings>
#include <QThread>

#include "connections.h"
#include "sessions.h"
#include "action.h"
#include "database.h"
#include "videowindow.h"
#include "controlusers.h"
#include "analysis.h"
#include "dialoglogin.h"
#include "controldictionary.h"
#include "dialogchoosedict.h"
#include "dialogchoosespecie.h"
#include "controlsessions.h"
#include "controlspecies.h"
#include "controlsubject.h"
#include "dialogchooselanguage.h"
#include "text.h"
#include "Audio.h"


namespace Ui{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QApplication *app, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QApplication *app;
    void linkSignals();
    void adjustShortcuts();
    Connections *connectdb;
    ControlUsers *users_ui;
    ControlDictionary *dict_ui;
    QList<Sessions> sessions;
    ControlSessions *ctl_sessions;
    ControlSpecies *ctl_species;
    ControlSubjects *ctl_subjects;
    void saveSession(Sessions session);
    AnalysisWindow *analysis_ui;
    unsigned int countAnalysis;
    QString dirConfig;
    void setDatabaseStatus(bool status=false);
    QMdiSubWindow *swDict, *swSpc, *swUser, *swSsn;    
    QMap<QObject*, QMdiSubWindow*> swVidMap;
    QString current_user;

private slots:
    void login();
    void logoff(bool status=false);
    void executeImportText(bool append=true);
    void executeImportVideo();
    void executeImportAudio();
    void executeImportMedia(QString type);
    void executeExportText();
    void executeExportTextMDF();
    void executeAnalysis();
    void executeImportDB();
    void executeExportDB();
    void newuser();
    void connectDatabase();
    void resetDatabase();
    void managerDict();
    void managerSessions();
    void managerSpecies();
    void managerSubjects();

    void dictClosed();
    void sessionsClosed();
    void speciesClosed();
    void subjectsClosed();
    void usersClosed();

    void aboutQt();
    void aboutPacca();

    void changeLanguage();
    void videowClosed(QObject* object);

signals:
    void database_updated();
    void users_updated();
    void sessions_updated();
    void species_updated();
    void subjects_updated();
    void dictionary_updated();
};

#endif // MAINWINDOW_H
