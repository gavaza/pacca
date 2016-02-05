#ifndef VIDEOWINDOW_H
#define VIDEOWINDOW_H

#include <QWidget>
#include <QSettings>
#include <QMdiArea>
#include <QKeyEvent>
#include <QPalette>
#include <QCloseEvent>

#include <QThread>

#include <Common.h>
#include <Instance.h>
#include <Media.h>
#include <MediaPlayer.h>
#include <Error.h>

#include <vlc/vlc.h>

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QList>

#include <QString>
#include <QTime>

#include "database.h"
#include "sessions.h"
#include "action.h"
#include "states.h"
#include "events.h"
#include "dictionary.h"
#include "species.h"
#include "subject.h"

namespace Ui {
class VideoWindow;
}

class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;
class VlcVideo;
class VlcError;

class VideoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit VideoWindow(QString typeMedia, QWidget *parent = 0);
    void setFilename(QString filename);
    void setDictionary(QString dict_view);
    ~VideoWindow();

protected:
    void closeEvent(QCloseEvent* ev);

private:
    Ui::VideoWindow *ui;
    VlcInstance *_instance;
    VlcMedia *_media;
    VlcMediaPlayer *_player;
    QString filename;
    QString origText;
    qreal ratioVideoProgress;
    QMap<QString,QString> dictionary;
    QMdiArea *my_parent;
    bool dictIsHiden;
    QList<unsigned int> eventsPositionInMiliseconds;


    void createConnections();
    void loadSpeceis();
    void loadSubjects();

private slots:
    void newEntry();
    void setSpeed(int val);
    void seekVideo(double pos);
    void review();
    void edit(int row, int col);
    void saveOrigText(int row, int col);
    void remove();
    void checkSaveCondition();
    void saveSession();

    void play();
    void pause();
    void stop();
    void highlight(int time);

    void showDict();

signals:
    void windowClosed();
};

#endif // VIDEOWINDOW_H
