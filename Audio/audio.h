#ifndef AUDIO_H
#define AUDIO_H

#include <iostream>
#include "bass.h"
#include <QDebug>
#include <QtCore>

#ifndef AUDIO_VARIABLES
#define AUDIO_VARIABLES
#define WIDTH 600	// display width
#define HEIGHT 201	// height (odd number for centre line)
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
    QPair<int, float*> calcpeaks();
    void ScanPeaks(QWORD decoder, DWORD width, DWORD height);
    void updateBpp(int width);
    BYTE* wavebuf;
    BOOL killscan; // thread scan

private slots:
    void pauseAudio();
    void stopAudio();
    void updatePos();
    void toPos(QWORD pos);
};



#endif // AUDIO_H
