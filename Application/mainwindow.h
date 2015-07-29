#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifndef INPUTTEXT_VARIABLES
const int TITLE_SESSION_SIZE_SIMPLE=3;
const int TITLE_SESSION_SIZE_COMPLEX=7;
#define INPUTTEXT_VARIABLES
#endif

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

#include "connections.h"
#include "sessions.h"
#include "action.h"
#include "database.h"
#include "videowindow.h"
#include "statistics.h"
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

#include "GraphWindow.h"

#include "plotwindow.h"


namespace Ui {
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
    VideoWindow *video_ui;
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

    QMdiSubWindow *swDict, *swSpc, *swUser, *swSsn;

public slots:
    void login();

private slots:
    void executeImportText(bool append=true);
    void executeImportAdvanced();
    void executeImportVideo();
    void executeImportAudio();
    void executeImportMedia(QString type);
    void executeAnalysis();
    void createConnections();
    void connectDatabse(bool makeTables = false);
    void resetDatabase();
    void newuser();
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
    void videowClosed();
};

#endif // MAINWINDOW_H
