#ifndef AUDIO_H
#define AUDIO_H

#include "bass.h"
#include <QDebug>
#include <QtCore>
#include <QList>

#ifndef AUDIO_VARIABLES
#define AUDIO_VARIABLES
#endif

#define time_update 50

class Audio
{
public:
    Audio(QString filename);
private:
    BOOL openAudio(QString filename);
    DWORD bpp;			// bytes per pixel
    DWORD chan;
    DWORD chan2;
    QWORD pos;
    double getPos();
    QWORD getPosW();
    BOOL playing;
    QPair<QList<float>, QList<float> > ScanPeaks(QWORD decoder);
    void updateBpp();
    BOOL killscan; // thread scan
    DWORD width;

private slots:
    void pauseAudio();
    void stopAudio();
    void updatePos();
    void toPos(QWORD pos);
};



#endif // AUDIO_H
