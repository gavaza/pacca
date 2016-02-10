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

QPair<int, float *> Audio::calcpeaks(){
    BASS_CHANNELINFO ci;
    BASS_ChannelGetInfo(this->chan, &ci);
    float *levels=(float*)malloc(ci.chans*sizeof(float)); // allocate an array for each channel's level
    BASS_ChannelGetLevelEx(this->chan, levels, 0.02, 0); // get the levels
    return QPair<int,float*>(ci.chans,levels);
}

void Audio::updateBpp(int width){
    this->bpp  = BASS_ChannelGetLength(this->chan,BASS_POS_BYTE)/width;
    DWORD bpp1 = BASS_ChannelSeconds2Bytes(this->chan,0.001); // minimum 1ms per pixel
    if (this->bpp<bpp1) this->bpp=bpp1;
}

void Audio::ScanPeaks(QWORD decoder, DWORD width, DWORD height){
    DWORD pos=0;
    float spp=BASS_ChannelBytes2Seconds(decoder,bpp); // seconds per pixel
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
        for (DWORD a=0;a<peak[0]*(height/2);a++)
            this->wavebuf[(height/2-1-a)*width+pos]=1+a; // draw left peak
        for (DWORD a=0;a<peak[1]*(height/2);a++)
            this->wavebuf[(height/2+1+a)*width+pos]=1+a; // draw right peak
        pos++;
        if (pos>=width) break; // reached end of display
        if (!BASS_ChannelIsActive(decoder)) break; // reached end of channel
    }
    if (!this->killscan){
        DWORD size;
        BASS_ChannelSetPosition(decoder,(QWORD)-1,BASS_POS_BYTE|BASS_POS_SCAN); // build seek table (scan to end)
        size=BASS_ChannelGetAttributeEx(decoder,BASS_ATTRIB_SCANINFO,0,0); // get seek table size
        if (size) { // got it
            void *info=malloc(size); // allocate a buffer
            BASS_ChannelGetAttributeEx(decoder,BASS_ATTRIB_SCANINFO,info,size); // get the seek table
            BASS_ChannelSetAttributeEx(this->chan,BASS_ATTRIB_SCANINFO,info,size); // apply it to the playback channel
            free(info);
        }
    }
    BASS_StreamFree(decoder); // free the decoder
}
