#include "audio.h"

Audio::Audio(QString filename)
{
    // check the correct BASS was loaded
    if (HIWORD(BASS_GetVersion())!=BASSVERSION) {
        qDebug() << "An incorrect version of bass library was loaded";
    }

    if(!BASS_Init(-1,44100,0,this,NULL)){
        qDebug("Can't initialize device");
    }

    if (!(this->playing=this->openAudio(filename))) { // start a file playing
        BASS_Free();
    }
    qDebug() << "Inicializado";
    this->killscan = false;
    this->run();
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
    this->bpp=BASS_ChannelGetLength(this->chan,BASS_POS_BYTE)/WIDTH; // bytes per pixel
    DWORD bpp1=BASS_ChannelSeconds2Bytes(this->chan,0.001); // minimum 1ms per pixel
    if (this->bpp<bpp1) this->bpp=bpp1;

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

void Audio::run()
{
    QTimer timer_update_pos;
    connect(&timer_update_pos, SIGNAL(timeout()), this, SLOT(updatePos()));
    timer_update_pos.start(50);

    this->exec();
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
