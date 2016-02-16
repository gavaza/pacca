#include "videowindow.h"
#include "ui_videowindow.h"

VideoWindow::VideoWindow(QString typeMedia, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoWindow),_media(0)
{
    ui->setupUi(this);
    this->subwindow = subwindow;
    this->ui->b_save->setEnabled(false);
    this->ui->b_save->setToolTip(tr("Preencha todos os campos antes de salvar."));
    this->dictIsHiden = true;
    this->ui->dictView->setMaximumSize(0,0);
    QStringList args = VlcCommon::args();
    args.push_back("-vvv");
    if(typeMedia == "audio"){
        args.push_back("--audio-visual=visual");
        args.push_back("--effect-list=scope");
    }
    qDebug() << "ARGS VLC => " << args;
    this->_instance = new VlcInstance(args, this);
    this->_player = new VlcMediaPlayer(this->_instance);
    this->_player->setVideoWidget(this->ui->w_video);
    this->ui->w_video->setMediaPlayer(this->_player);
    this->ui->progress->setMediaPlayer(this->_player);

    this->loadSpeceis();
    this->loadSubjects();
    this->createConnections();
}

VideoWindow::~VideoWindow()
{
    this->deleteLater();
    delete _player;
    delete _media;
    delete _instance;
    delete ui;
}

void VideoWindow::closeEvent(QCloseEvent *ev)
{
    if(this->_player->state() == Vlc::Playing) this->_player->stop();
    emit windowClosed();
}

void VideoWindow::createConnections()
{
    connect(this->ui->b_play,SIGNAL(clicked()),this,SLOT(play()));
    connect(this->ui->b_pause,SIGNAL(clicked()),this,SLOT(pause()));
    connect(this->ui->b_stop,SIGNAL(clicked()),this,SLOT(stop()));
    connect(this->ui->speed,SIGNAL(valueChanged(int)),this,SLOT(setSpeed(int)));
    connect(this->ui->in_event,SIGNAL(returnPressed()),this,SLOT(newEntry()));
    connect(this->ui->in_event,SIGNAL(textChanged(QString)),this->_player,SLOT(pause()));
    connect(this->ui->sequence,SIGNAL(itemSelectionChanged()),this,SLOT(review()));
    connect(this->ui->sequence,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(saveOrigText(int,int)));
    connect(this->ui->sequence,SIGNAL(cellEntered(int,int)),this,SLOT(saveOrigText(int,int)));
    connect(this->ui->b_excluir,SIGNAL(clicked()),this,SLOT(remove()));
    connect(this->ui->subject,SIGNAL(textChanged(QString)),this,SLOT(checkSaveCondition()));
    connect(this->ui->description,SIGNAL(textChanged(QString)),this,SLOT(checkSaveCondition()));
    connect(this->ui->b_save,SIGNAL(clicked()),this,SLOT(saveSession()));
    connect(this->ui->b_dict,SIGNAL(clicked()),this,SLOT(showDict()));
    connect(this->_player,SIGNAL(timeChanged(int)),this,SLOT(highlight(int)));
}

void VideoWindow::loadSpeceis()
{
    Database db;
    QList<Species> species = db.getAllSpecies();
    this->ui->species->clear();
    for(int l = 0; l < species.size(); l++){
        Species sp = species.at(l);
        QString name = sp.getName().toString();
        QVariant id = sp.getId();
        this->ui->species->addItem(name,id);
    }
}

void VideoWindow::loadSubjects()
{
    Database db;
    QList<Subjects> subjects = db.getAllSubjects();
    this->ui->subject->clear();
    for(int l = 0; l < subjects.size(); l++){
        Subjects s = subjects.at(l);
        QString name = s.getName().toString();
        QVariant id = s.getId();
        this->ui->subject->addItem(name,id);
    }
}

void VideoWindow::saveOrigText(int row, int col)
{
    this->origText = this->ui->sequence->item(row,col)->text();
    connect(this->ui->sequence,SIGNAL(cellChanged(int,int)),this,SLOT(edit(int,int)));
}

void VideoWindow::remove()
{
    QList<int> rows;
    rows.push_back(this->ui->sequence->selectedItems().first()->row());
    this->remove(rows);
}

void VideoWindow::remove(QList<int> rows){
    disconnect(this->ui->sequence,SIGNAL(itemSelectionChanged()),this,SLOT(review()));
    while(rows.size()>0){
        this->eventsPositionInMiliseconds.removeAt(rows.last());
        this->ui->sequence->removeRow(rows.last());
        rows.pop_back();
    }
    connect(this->ui->sequence,SIGNAL(itemSelectionChanged()),this,SLOT(review()));
    this->checkSaveCondition();
}

void VideoWindow::checkSaveCondition()
{
    bool check = true;
    if(this->ui->sequence->rowCount() == 0) check = false;
    if(this->ui->description->text().isEmpty()) check = false;

    if(check){
        this->ui->b_save->setToolTip(tr("Salvar sessão!"));
    }else {
        this->ui->b_save->setToolTip(tr("Preencha todos os campos antes de salvar."));
    }
    this->ui->b_save->setEnabled(check);
}

void VideoWindow::saveSession()
{
    Database db;
    Sessions s;

    QSettings settings("NuEvo","Pacca");
    settings.beginGroup("global");
    QVariant user = settings.value("user");
    settings.endGroup();
    s.setDecoder(user);

    s.setDateDecoding(QDateTime::currentDateTime());
    s.setDateSession(QDateTime::currentDateTime());
    s.setObserver(this->ui->observer->text());
    if(this->ui->observer->text().isEmpty()) s.setObserver(user);
    s.setDescription(this->ui->description->text());
    s.setSubject(this->ui->subject->currentData());
    s.setSpecies(this->ui->species->currentData());
    for(int i = 0; i < this->ui->sequence->rowCount(); i++){
        Actions a;
        QTime time; time = QTime::fromString(this->ui->sequence->item(i,0)->text());
        a.setTimeAction(time.hour()*3600+time.minute()*60+time.second());
        QString st = this->simplefiedText(this->ui->sequence->item(i,1)->text()).second;
        a.setState(States(st));
        QString ev = this->simplefiedText(this->ui->sequence->item(i,2)->text()).second;
        a.setEvent(Events(ev));
        s.addAction(a);
    }
    int ret = db.saveSession(s);
    if(ret > 0){
        this->close();
    } else {
        QMessageBox::critical(this,tr("Erro"),tr("Ocorreu um erro ao salvar! Tente novamente!"));
    }
}

void VideoWindow::play()
{
    this->ui->sequence->clearSelection();
    this->_player->play();
    this->setSpeed(this->ui->speed->value());
    this->ui->in_event->setFocus();
    connect(this->ui->in_event,SIGNAL(returnPressed()),this,SLOT(newEntry()));
}

void VideoWindow::pause()
{
    this->_player->pause();
    this->ui->in_event->setFocus();
}

void VideoWindow::stop()
{
    this->_player->stop();
    this->ui->sequence->scrollToTop();
    this->ui->sequence->clearSelection();
    this->highlight(0);
    this->ui->in_event->setFocus();
    disconnect(this->ui->in_event,SIGNAL(returnPressed()),this,SLOT(newEntry()));
}

void VideoWindow::highlight(int ms)
{
    for(int r=0; r < this->eventsPositionInMiliseconds.size(); r++){
        QTableWidgetItem* item = this->ui->sequence->item(r,0);
        if(this->eventsPositionInMiliseconds.at(r) <= ms+125){
            if(this->eventsPositionInMiliseconds.at(r) >= ms-125)  item->setBackgroundColor(Qt::green);
            else item->setBackgroundColor(QColor(153,255,255));
        } else {
            QPalette p;
            if(r%2==0)
                item->setBackground(p.base());
            else
                item->setBackground(p.alternateBase());
        }
    }
}

void VideoWindow::showDict()
{
    if(this->dictIsHiden){
        this->ui->sequence->scrollToBottom();
        this->ui->dictView->setMaximumSize(999,999);
    } else {
        this->ui->dictView->setMaximumSize(0,0);
    }
    this->dictIsHiden = !this->dictIsHiden;
}

void VideoWindow::newEntry()
{
    QString code = this->ui->in_event->text().simplified();
    QString event = this->dictionary.value(code,"");
    if(event.size() == 0){
        QMessageBox::critical(this,tr("Erro"),tr("Código do evento não encontrado no dicionário."));
        return;
    }
    QString codeState = this->ui->in_state->text().simplified();
    QString state = "";
    if(codeState != ""){
        state = this->dictionary.value(codeState,"");
        if(state.size() == 0){
            QMessageBox::critical(this,tr("Erro"),tr("Código do estado não encontrado no dicionário."));
            return;
        }
    }
    QTableWidgetItem *item_time = new QTableWidgetItem;
    QTableWidgetItem *item_state = new QTableWidgetItem;
    QTableWidgetItem *item_event = new QTableWidgetItem;
    int ms = this->_player->time();
    int start = 0;
    int end = this->eventsPositionInMiliseconds.size()-1;
    int row = 0;
    while (start <= end){
        row = (start+end)/2;
        if (ms>this->eventsPositionInMiliseconds.at(row)){
            start = row+1;
        }
        else{
            end = row-1;
        }
    }
    row = start;

    this->eventsPositionInMiliseconds.insert(row,ms);
    QString time = QTime(0,0,0).addMSecs(ms).toString("hh:mm:ss");
    item_time->setText(time);
    item_time->setFlags(item_time->flags() & ~Qt::ItemIsEditable);
    item_state->setText("("+codeState+") "+state);
    item_event->setText("("+code+") "+event);
    this->ui->sequence->insertRow(row);
    this->ui->sequence->setItem(row,0,item_time);
    this->ui->sequence->setItem(row,1,item_state);
    this->ui->sequence->setItem(row,2,item_event);
    this->ui->sequence->scrollToBottom();
    this->ui->in_event->clear();
    this->_player->play();
    this->ui->in_event->setFocus();
    this->checkSaveCondition();
}

void VideoWindow::setSpeed(int val)
{
    qreal speed;
    if(val > 0){
        speed = 1+double(val);
    } else {
        speed = 1+double(val)/10;
    }
    if(speed==0) speed=0.05;
    QString l = QString::number(speed,'f',1)+"x";
    if(speed==1) l = "Normal";

    libvlc_media_player_set_rate(this->_player->core(),speed);
    VlcError::errmsg();

    this->ui->l_speed->setText(l);
}

void VideoWindow::seekVideo(double pos)
{
    this->_player->setTime(pos);
}

void VideoWindow::review()
{
    if(this->ui->sequence->rowCount() > 0){
        int row = this->ui->sequence->currentRow();
        double timeInMiliSeconds = this->eventsPositionInMiliseconds.at(row);
        this->seekVideo(timeInMiliSeconds);
        this->highlight(timeInMiliSeconds);
        this->_player->pause();
    }
}

void VideoWindow::edit(int row, int col)
{
    disconnect(this->ui->sequence,SIGNAL(cellChanged(int,int)),this,SLOT(edit(int,int)));
    QString code = this->ui->sequence->item(row,col)->text();
    QString event = this->dictionary.value(code,"").simplified();
    this->ui->sequence->item(row,col)->setText("("+code+") "+event);
    if(event == "" ){
        if (col==0){
            this->ui->sequence->item(row,col)->setText(code);
        }
        else if(col==1 || col==2){
            this->ui->sequence->item(row,col)->setText(this->origText);
        }
        this->origText="";
    }
}

void VideoWindow::setFilename(QString filename)
{
    this->filename = filename;
    this->_media = new VlcMedia(filename, true, _instance);
    this->_player->open(this->_media);
}

void VideoWindow::setDictionary(QString dict)
{
    this->dictionary_name = dict;
    this->updateDictionary();
}

void VideoWindow::updateDictionary(){
    Database db;
    this->dictionary = db.getDictionary(this->dictionary_name).getEntries();
    QMapIterator<QString, QString> i(this->dictionary);
    this->ui->dictView->setRowCount(0);
    int c = 0;
    int row = -1;
    while (i.hasNext()) {
        i.next();
        QTableWidgetItem *item  = new QTableWidgetItem;
        item->setText(i.key()+" : "+i.value());
        int col = c % this->ui->dictView->columnCount();
        if(col == 0){
            row = this->ui->dictView->rowCount();
            this->ui->dictView->insertRow(row);
        }
        this->ui->dictView->setItem(row,col,item);
        c++;
    }
    this->updateEntryDict();
    qDebug() << this->dictionary.keys();
    qDebug() << this->dictionary.values();
}

void VideoWindow::updateEntryDict(){
    QList<int> rows_remove;
    for (int i=0; i<this->ui->sequence->rowCount(); i++){
        QString state_code = this->simplefiedText(this->ui->sequence->item(i,1)->text()).first;
        QString event_code = this->simplefiedText(this->ui->sequence->item(i,2)->text()).first;
        QString state = this->dictionary.value(state_code);
        QString event = this->dictionary.value(event_code);
        this->ui->sequence->item(i,1)->setText("("+state_code+") " + state);
        if(event == "" ){
            rows_remove.push_back(i);
        }
        else{
            this->ui->sequence->item(i,2)->setText("("+event_code+") " + event);
        }
    }
    this->remove(rows_remove);
}

QPair<QString,QString> VideoWindow::simplefiedText(QString text){
    QString str_temp;

    // code
    str_temp = text;
    int code_start = str_temp.indexOf("(",0)+1;
    int code_end = str_temp.indexOf(")",code_start)-1;
    QString code = str_temp.remove(code_end+1,str_temp.size()).remove(0,code_start);

    // information
    str_temp = text;
    int size_str = str_temp.size()-str_temp.indexOf(")",0)-1;
    QString str = str_temp.right(size_str).simplified();

    return QPair<QString, QString> (code,str);
}

void VideoWindow::hideVideo(QMdiSubWindow* video){
    if (this->subwindow == video){
        this->ui->w_video->show();
    }
#ifdef MAC_OS_X_VERSION_MAX_ALLOWED
    else{
        this->ui->w_video->hide();
    }
#endif
}

void VideoWindow::setSubWindow(QMdiSubWindow *subwindow){
    this->subwindow = subwindow;
}

void VideoWindow::hideVideoCommands(bool hide){
    this->ui->b_play->setHidden(hide);
    this->ui->b_stop->setHidden(hide);
    this->ui->b_pause->setHidden(hide);
    this->ui->speed->setHidden(hide);
    this->ui->l_speed->setHidden(hide);
    this->ui->speedBox->setHidden(hide);
    this->ui->description->setHidden(hide);
    this->ui->observer->setHidden(hide);
    this->ui->label->setHidden(hide);
    this->ui->label_2->setHidden(hide);
    this->ui->l_observer->setHidden(hide);
    this->ui->l_description->setHidden(hide);
    this->ui->species->setHidden(hide);
    this->ui->subject->setHidden(hide);
}
