#include "videowindow.h"
#include "ui_videowindow.h"

VideoWindow::VideoWindow(QString typeMedia,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoWindow),_media(0)
{
    ui->setupUi(this);
    this->ui->b_save->setEnabled(false);
    this->ui->b_save->setToolTip(tr("Preencha todos os campos antes de salvar."));
    this->my_parent = (QMdiArea*) parent;
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
    delete _player;
    delete _media;
    delete _instance;
    delete ui;
    emit windowClosed();
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
    connect(this->ui->in_event,SIGNAL(textChanged(QString)),this->_player,SLOT(pause()));
    connect(this->ui->in_event,SIGNAL(returnPressed()),this,SLOT(newEntry()));
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
    if(this->ui->sequence->selectedItems().size() > 0){
        disconnect(this->ui->sequence,SIGNAL(itemSelectionChanged()),this,SLOT(review()));
        int row = this->ui->sequence->selectedItems().first()->row();
        this->eventsPositionInMiliseconds.removeAt(row);
        this->ui->sequence->removeRow(row);
        connect(this->ui->sequence,SIGNAL(itemSelectionChanged()),this,SLOT(review()));
        this->checkSaveCondition();
    }
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
        QString st_temp = this->ui->sequence->item(i,1)->text();
        int size_st = st_temp.size()-st_temp.indexOf(")",0)-1;
        QString st = st_temp.right(size_st).simplified();
        a.setState(States(st));
        QString ev_temp = this->ui->sequence->item(i,2)->text();
        int size_ev = ev_temp.size()-ev_temp.indexOf(")",0)-1;
        QString ev = ev_temp.right(size_ev).simplified();
        a.setEvent(Events(ev));
        s.addAction(a);
    }
    int ret = db.saveSession(s);
    qDebug() << ret;
    if(ret > 0){
        QMessageBox::information(this,tr("Sucesso"),tr("Os dados foram salvos com sucesso!"));
        //        this->_player->stop();
        //        if(this->_player) delete this->_player;
        //        if(this->_media) delete this->_media;
        //        if(this->_instance) delete this->_instance;
        //        delete this->_player;
        //        delete this->_instance;
        this->close();
        //        this->my_parent->closeActiveSubWindow();
    } else {
        QMessageBox::critical(this,tr("Erro"),tr("Ocorreu um erro ao salvar! Tente novamente!"));
    }
}

void VideoWindow::play()
{
    this->_player->play();
    this->setSpeed(this->ui->speed->value());
    this->ui->in_event->setFocus();
}

void VideoWindow::pause()
{
    this->_player->pause();
    this->ui->in_event->setFocus();
}

void VideoWindow::stop()
{
    this->_player->stop();
    this->ui->in_event->setFocus();
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
        this->_player->pause();
    }
}

void VideoWindow::edit(int row, int col)
{
    disconnect(this->ui->sequence,SIGNAL(cellChanged(int,int)),this,SLOT(edit(int,int)));
    QString code = this->ui->sequence->item(row,col)->text();
    QString event = this->dictionary.value(code,"").simplified();
    this->ui->sequence->item(row,col)->setText("("+code+") "+event);
    if(event == "" && col==2){
        this->ui->sequence->item(row,col)->setText(this->origText);
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
    Database db;
    this->dictionary = db.getDictionary(dict).getEntries();
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
}
