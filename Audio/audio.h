#ifndef AUDIO_H
#define AUDIO_H

#include <iostream>
#include "bass.h"
#include <QDebug>
#include <QThread>
#include <QtCore>

#ifndef AUDIO_VARIABLES
#define AUDIO_VARIABLES
#define WIDTH 600	// display width
#define HEIGHT 201	// height (odd number for centre line)
#endif

class Audio : public QThread
{
    Q_OBJECT
public:
    Audio(QString filename);
private:
    BOOL openAudio(QString filename);
    DWORD bpp;			// bytes per pixel
    DWORD chan;
    DWORD chan2;
    QWORD pos;
    QWORD *wavebuf;
    double getPos();
    QWORD getPosW();
    BOOL playing;
    BOOL killscan;
    void run();

private slots:
    void pauseAudio();
    void stopAudio();
    void updatePos();
    void toPos(QWORD pos);
};



#endif // AUDIO_H
