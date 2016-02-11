#include "audio.h"

Audio::Audio(QString filename)
{
    // check the correct BASS was loaded
    if (HIWORD(BASS_GetVersion())!=BASSVERSION) {
        qDebug() << "An incorrect version of bass library was loaded";
    }

#ifdef WINVER
    HWND hwnd;
    if(!BASS_Init(-1,44100,0,hwnd,NULL)){
#endif
#ifdef MAC_OS_X_VERSION_MAX_ALLOWED
    if(!BASS_Init(-1,44100,0,this,NULL)){
#endif
#ifdef linux
    if(!BASS_Init(-1,44100,0,this,NULL)){
#endif
        qDebug("Can't initialize device");
    }

    if (!(this->playing=this->openAudio(filename))) { // start a file playing
        BASS_Free();
    }

    /* debug options to peaks */
    this->killscan = false;
    qDebug() << "peaks";
    this->width = 1000;
    QPair<QList<float>,QList<float> > peaks = this->ScanPeaks(this->chan2);
    QList<float> esq = peaks.first;
    QList<float> dir = peaks.second;
    qDebug() << "(size) = " << esq.size();
    qDebug() << esq;
    qDebug() << dir;

    /* only debug */

}

BOOL Audio::openAudio(QString filename){
    char* file;

    file = (char*)malloc(sizeof(char)*filename.size());
    strcpy(file, filename.toStdString().data());

    if (!(this->chan=BASS_StreamCreateFile(FALSE,file,0,0,0))
            && !(this->chan=BASS_MusicLoad(FALSE,file,0,0,BASS_MUSIC_RAMPS|BASS_MUSIC_POSRESET|BASS_MUSIC_PRESCAN,1))) {
        qDebug("Can't play file");
        return FALSE; // Can't load the file
    }

    BASS_ChannelPlay(this->chan,FALSE); // start playing

    this->chan2=BASS_StreamCreateFile(FALSE,file,0,0,BASS_STREAM_DECODE);
    if (!this->chan2) this->chan2=BASS_MusicLoad(FALSE,file,0,0,BASS_MUSIC_DECODE,1);

    return TRUE;
}

void Audio::updatePos(){
    this->pos = BASS_ChannelGetPosition(this->chan,BASS_POS_BYTE);
}

QWORD Audio::getPosW(){
    return this->pos;
}

double Audio::getPos(){
    return BASS_ChannelBytes2Seconds(this->chan,this->pos);
}

void Audio::pauseAudio(){
    if (this->playing)
        this->playing = BASS_ChannelPause(this->chan);
    else
        this->playing = BASS_ChannelPlay(this->chan,FALSE);
}

void Audio::stopAudio(){
    if (this->playing)
        this->playing = !BASS_ChannelStop(this->chan);
    else
        this->playing = BASS_ChannelPlay(this->chan,TRUE);
}

void Audio::toPos(QWORD pos){
    BASS_ChannelSetPosition(this->chan,pos,BASS_POS_BYTE);
}

void Audio::updateBpp(){
    this->bpp  = BASS_ChannelGetLength(this->chan,BASS_POS_BYTE)/this->width;
    DWORD bpp1 = BASS_ChannelSeconds2Bytes(this->chan,0.001); // minimum 1ms per pixel
    if (this->bpp<bpp1) this->bpp=bpp1;
}

QPair<QList<float>,QList<float> > Audio::ScanPeaks(QWORD decoder){
    DWORD pos=0;
    QPair<QList<float>,QList<float> > peaks;
    this->updateBpp();
    float spp=BASS_ChannelBytes2Seconds(decoder,this->bpp); // seconds per pixel
    while (!this->killscan) {
        float peak[2];
        if (spp>1) { // more than 1 second per pixel, break it down...
            float todo=spp;
            peak[1]=peak[0]=0;
            do {
                float level[2],step=(todo<1?todo:1);
                BASS_ChannelGetLevelEx(decoder,level,step,BASS_LEVEL_STEREO); // scan peaks
                if (peak[0]<level[0]) peak[0]=level[0];
                if (peak[1]<level[1]) peak[1]=level[1];
                todo-=step;
            } while (todo>0);
        }
        else{
            BASS_ChannelGetLevelEx(decoder,peak,spp,BASS_LEVEL_STEREO); // scan peaks
        }
        peaks.first.push_back(peak[0]);
        peaks.second.push_back(peak[1]);
        pos++;
        if (pos>=this->width) break; // reached end of display
        if (!BASS_ChannelIsActive(decoder)) break; // reached end of channel
    }
    BASS_StreamFree(decoder); // free the decoder
    return peaks;
}
