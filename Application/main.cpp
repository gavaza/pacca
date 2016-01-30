#include <QApplication>
#include <QSettings>
#include <QCoreApplication>

#include "mainwindow.h"
#include "dialogchooselanguage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifdef win32
#endif
#ifdef MAC_OS_X_VERSION_MAX_ALLOWED
    setenv("GVBINDIR", QCoreApplication::applicationDirPath().append("/../Frameworks/graphviz").toLocal8Bit().data(),1);
#endif
#ifdef linux
    setenv("GVBINDIR", QCoreApplication::applicationDirPath().append("/../lib").toLocal8Bit().data(),1);
#endif
    QSettings settings("NuEvo","Pacca");
    settings.beginGroup(QApplication::tr("global"));
    QVariant lang = settings.value("language");
    settings.endGroup();
    if(lang.toString() == ""){
        DialogChooseLanguage d;
        d.exec();
        lang = d.getLanguage();
        QSettings settings("NuEvo","Pacca");
        settings.beginGroup(QApplication::tr("global"));
        settings.setValue("language",lang);
        settings.endGroup();
    }
    QTranslator translator;
    if(lang == "English") translator.load(QCoreApplication::applicationDirPath().append("/../Languages/Pacca_Eng.qm").toLocal8Bit().data());
    a.installTranslator(&translator);
    MainWindow w(&a);

    w.showMaximized();
    return a.exec();
}
