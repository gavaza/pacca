#include "analysis.h"
#include "ui_analysis.h"
#include "ui_dialogconfigstats.h"

AnalysisWindow::AnalysisWindow(QMdiArea* mdi, unsigned int nwin, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Analysis)
{
    ui->setupUi(this);
    this->statsModule = new Statistics(this->ui->dynamic->isChecked(),
                                       this->ui->absolut->isChecked(),
                                       this->ui->stepsSize->value(),
                                       this->ui->startStep->value());
    this->phyloModule = new Phylogenetic();
    this->createConnection();
    this->ui->sessions->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    this->ui->configBox->setDisabled(true);
    this->ui->statsSession->setDisabled(true);
    this->ui->tabListSession->setDisabled(true);
    this->ui->tabPhylo->setDisabled(true);
    this->table_op.push_back(this->ui->firstTable);
    this->ui->seqBox->setMinimumHeight(250);
    this->nwin=nwin;
    this->mdi=mdi;
    this->setWindowTitle("Análise "+QString::number(this->nwin));
    this->ui->sizeSeq->setValue(2);
    this->ui->cancelProcess->setDisabled(true);
    this->hasData = false;
    this->hasPhyloData = false;
    this->ui->stopMtx->setEnabled(false);

    this->config = new DialogConfigStats(this);
    this->refreshConfig();
}

AnalysisWindow::~AnalysisWindow()
{
    delete ui;
}

void AnalysisWindow::createConnection()
{
    connect(this->ui->addSession,SIGNAL(clicked()),this,SLOT(addSession()));
    connect(this->ui->removeSession,SIGNAL(clicked()),this,SLOT(removeSession()));
    connect(this->ui->sessions,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(loadSequence()));
    connect(this->ui->sizeSeq,SIGNAL(valueChanged(int)),this,SLOT(createPagesSeq(int)));
    connect(this->ui->addSeq,SIGNAL(clicked()),this,SLOT(addSelectedSeq()));
    connect(this->ui->genSeq,SIGNAL(clicked()),this,SLOT(genSelectedSeq()));
    connect(this->ui->tabSeq,SIGNAL(tabCloseRequested(int)),this,SLOT(delSelectedSeq(int)));
    connect(this->ui->statsSession,SIGNAL(clicked()),this,SLOT(showSessionStats()));
    connect(this->ui->statsSeq,SIGNAL(clicked()),this,SLOT(showSequenceStats()));
    connect(this->ui->config,SIGNAL(clicked()),this,SLOT(setConfig()));
    connect(this->ui->showGraph,SIGNAL(clicked()),this,SLOT(drawSessionGraph()));
    connect(this->ui->makeRandom,SIGNAL(clicked()),this,SLOT(genRandomSequence()));
    connect(this->ui->hypNull,SIGNAL(clicked()),this,SLOT(statisticsTests()));
    connect(this->statsModule,SIGNAL(dataProcessed()),this,SLOT(showProcessedDataPermutation()));
    connect(this->statsModule,SIGNAL(statusProcess(double)),this,SLOT(updateProgressPemutation(double)));
    connect(this->ui->sessions,SIGNAL(itemSelectionChanged()),this,SLOT(refreshTableEvents()));
    connect(this->ui->cancelProcess,SIGNAL(clicked()),this,SLOT(cancelProcessPermutation()));
    connect(this->ui->spcUP,SIGNAL(clicked()),this,SLOT(upSpecie()));
    connect(this->ui->spcDOWN,SIGNAL(clicked()),this,SLOT(downSpecie()));
    connect(this->ui->showMtx,SIGNAL(clicked()),this,SLOT(showPhyloMtx()));
    connect(this->ui->stopMtx,SIGNAL(clicked()),this,SLOT(cancelProcessPhylo()));
    connect(this->phyloModule,SIGNAL(dataProcessed()),this,SLOT(showProcessedDataPhylo()));
    connect(this->phyloModule,SIGNAL(statusProcess(double)),this,SLOT(updateProgressPhylo(double)));
    connect(this->phyloModule,SIGNAL(statusProcessLabel(QString)),this->ui->label_phylo,SLOT(setText(QString)));
    connect(this->ui->absolut,SIGNAL(clicked(bool)),this->statsModule,SLOT(updateAbsolute(bool)));
    connect(this->ui->dynamic,SIGNAL(clicked(bool)),this->statsModule,SLOT(updateDynamic(bool)));
    connect(this->ui->startStep,SIGNAL(valueChanged(int)),this->statsModule,SLOT(updateStepStart(int)));
    connect(this->ui->stepsSize,SIGNAL(valueChanged(int)),this->statsModule,SLOT(updateStepSize(int)));

}

void AnalysisWindow::addSession()
{
    DialogSelectSession d;
    bool duplicated = false;
    if(d.exec()){
        int row = 0;
        QList<QTableWidgetItem*> itens = d.getSelectedItens();
        for(int i=0; i<itens.size(); i++){
            int column = i%6;
            duplicated = this->checkDuplicated(itens.at(i)->text().toInt());
            if(!duplicated){
                if(column == 0){
                    row = this->ui->sessions->rowCount();
                    this->ui->sessions->insertRow(row);
                }
                QTableWidgetItem* item = new QTableWidgetItem;
                item->setText(itens.at(i)->text());
                this->ui->sessions->setItem(row,column,item);
            }
        }
        //        this->ui->sessions->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        this->fillSetEvents();
        this->fillPagesSeq();
        this->checkConditions();
        this->refreshSpeciesList();
    }
}

void AnalysisWindow::removeSession()
{
    int nSelected = this->ui->sessions->selectedItems().size();
    disconnect(this->ui->sessions,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(loadSequence()));
    disconnect(this->ui->sessions,SIGNAL(itemSelectionChanged()),this,SLOT(refreshTableEvents()));
    if(nSelected > 0){
        QList<QTableWidgetSelectionRange> ranges = this->ui->sessions->selectedRanges();
        if ( ranges.isEmpty() )
            return;
        int begin = ranges.at(0).topRow(),
                count = ranges.at(0).rowCount();
        do
        {
            this->ui->sessions->removeRow(begin);
        }while ( --count );
        this->fillSetEvents();
        this->fillPagesSeq();
        this->checkConditions();
        this->refreshSpeciesList();
    }
    connect(this->ui->sessions,SIGNAL(itemSelectionChanged()),this,SLOT(refreshTableEvents()));
    connect(this->ui->sessions,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(loadSequence()));
}

void AnalysisWindow::loadSequence()
{
    if(this->ui->sessions->selectedItems().size() > 0){
        Database db;
        unsigned int idSession = this->ui->sessions->selectedItems().first()->text().toUInt();
        QList<Actions> actions = db.getSequence(idSession);
        for(int i = 0; i<actions.size(); i++){
            if(i==0) this->ui->sequence->clear();
            Actions a = actions.at(i);
            QString line = QTime(0,0,0).addSecs(int(a.getTimeAction())).toString();
            line += ","+a.getStateDescription();
            line += ","+a.getEventDescription();
            this->ui->sequence->addItem(line);
        }
        this->ui->groupSession->setCurrentIndex(1);
    }
}

void AnalysisWindow::checkConditions()
{
    bool enable = (this->ui->sessions->rowCount() == 0);
    this->ui->configBox->setDisabled(enable);
    this->ui->statsSession->setDisabled(enable);
    this->ui->tabListSession->setDisabled(enable);
    this->ui->tabPhylo->setDisabled(enable);
}

void AnalysisWindow::createPagesSeq(int size)
{
    int currentSize = this->ui->seqBox->count();
    if(currentSize < size){
        for(int i=currentSize; i < size; i++){
            QString pageName = QString::number(i+1);
            QWidget* w = new QWidget(this->ui->seqBox);
            this->ui->seqBox->addTab(w,pageName);
            w->setLayout(new QGridLayout);
            QTableWidget* t = new QTableWidget(w);
            t->horizontalHeader()->setVisible(false);
            t->verticalHeader()->setVisible(false);
            t->setEditTriggers(QAbstractItemView::NoEditTriggers);
            w->layout()->addWidget(t);
            this->table_op.push_back(t);
            this->fillPagesSeq(i);
        }
    } else {
        for(int i=currentSize; i > size; i--){
            if(this->table_op.size() > 1){
                QTableWidget* t = this->table_op.last();
                t->clear();
                delete t;
                this->table_op.removeLast();
            }
            this->ui->seqBox->removeTab(i-1);
        }
    }
}

void AnalysisWindow::addSelectedSeq()
{
    QListWidget *list = new QListWidget(this->ui->tabSeq);
    this->sequences.push_back(list);
    for(int p = 0; p < this->table_op.size(); p++){
        QString line = QString::number(p+1)+": {";
        QList<QTableWidgetItem*> itens = this->table_op.at(p)->selectedItems();
        if((itens.size() == 0) || (itens.size() == this->events.size())) line+=" *";
        else{
            for(int i = 0; i <  itens.size(); i++){
                line+=" "+itens.at(i)->text()+",";
            }
        }
        line+=" }";
        list->insertItem(p,line);
    }

    int tabNumber = this->ui->tabSeq->count();
    int idx = this->ui->tabSeq->insertTab(tabNumber,list,"Seq "+QString::number(tabNumber+1));
    this->ui->tabSeq->setCurrentIndex(idx);

    QGridLayout *layout = new QGridLayout();
    this->ui->tabSeq->widget(tabNumber)->setLayout(layout);
}

void AnalysisWindow::permutation(QStringList ev, QList<int> list, int i, int n)
{
    if(list.size()==n){
        QVariantList comb;
        for(int e=0; e < n; e++){
            comb.push_back(ev.at(list.at(e)));
        }
        this->permutation_list.push_back(comb);
    } else {
        for(int j=0; j < ev.size(); j++){
            if(!list.contains(j)){
                list.push_back(j);
                permutation(ev,list,j,n);
                list.pop_back();
            }
        }
    }
}

void AnalysisWindow::preparePhylogenetic(Phylogenetic* module)
{
    QMessageBox::StandardButton r = QMessageBox::No;
    if(this->hasPhyloData){
        r = QMessageBox::question(this, tr("Novo cálculo"), tr("Você deseja atualizar os dados?"),
                                  QMessageBox::Yes|QMessageBox::No);
    }
    if (r == QMessageBox::Yes || !this->hasPhyloData) {
        Database db;
        QMap< QString, StatisticMap > mapSequences;

        if(this->ui->sessions->selectedItems().size() == 0){ //calculating for all sessions
            for(int s=0; s < this->ui->sessions->rowCount(); s++){
                unsigned int idSession = this->ui->sessions->item(s,0)->text().toUInt(); //getting the session id
                QString sbjSession = this->ui->sessions->item(s,1)->text(); //getting the name of the specie
                int idSubject = db.getSubjects(sbjSession).getId().toInt();
                QString spcSession = this->ui->sessions->item(s,2)->text(); //getting the name of the specie
                if(!mapSequences.contains(spcSession)){ //checking if already exist sessions with this specie
                    mapSequences.insert(spcSession,StatisticMap());
                }
                QList<Actions> actions = db.getSequence(idSession); //getting the sequence of events
                QList<QVariant> tmp_ev;
                for(int a = 0; a < actions.size(); a++){ //for each event, getting the description and position index
                    Actions act = actions.at(a);
                    QString ev = act.getEventDescription();
                    tmp_ev.push_back(ev);
                }
                if(!mapSequences.value(spcSession).contains(idSubject)){
                    mapSequences[spcSession].insert(idSubject,tmp_ev);
                } else {
                    mapSequences[spcSession].insertMulti(idSubject,tmp_ev);
                }
            }
        } else {
            int sizeCollumns = this->ui->sessions->columnCount();
            for(int s=0; s < this->ui->sessions->selectedItems().size(); s=s+sizeCollumns){
                unsigned int idSession = this->ui->sessions->selectedItems().at(s)->text().toUInt();
                QString sbjSession = this->ui->sessions->selectedItems().at(s+1)->text();
                int idSubject = db.getSubjects(sbjSession).getId().toInt();
                QString spcSession = this->ui->sessions->selectedItems().at(s+2)->text();
                if(!mapSequences.contains(spcSession)){
                    mapSequences.insert(spcSession,StatisticMap());
                }
                QList<Actions> actions = db.getSequence(idSession);
                QList<QVariant> tmp_ev;
                for(int a = 0; a < actions.size(); a++){
                    Actions act = actions.at(a);
                    QString ev = act.getEventDescription();
                    tmp_ev.push_back(ev);
                }
                if(!mapSequences[spcSession].contains(idSubject)){
                    mapSequences[spcSession].insert(idSubject,tmp_ev);
                } else {
                    mapSequences[spcSession].insertMulti(idSubject,tmp_ev);
                }
            }
        }
        QList<QVariant> sortedSpecies;
        if(this->ui->speciesTable->selectedItems().size() == 0){
            for(int idx = 0; idx < this->ui->speciesTable->rowCount(); idx++)
                sortedSpecies.push_back(this->ui->speciesTable->item(idx,0)->text());
        } else {
            int sizeCollumns = this->ui->speciesTable->columnCount();
            qDebug() << sizeCollumns;
            for(int idx = 0; idx < this->ui->speciesTable->selectedItems().size(); idx+=sizeCollumns){
                sortedSpecies.push_back(this->ui->speciesTable->selectedItems().at(idx)->text());
            }
        }
        this->permutation_list.clear();
        QList<int> idx;
        this->permutation(this->events.toList(),idx,0,this->ui->sizeSeq->value()); //need to check this->events
        module->loadData(mapSequences,sortedSpecies,
                         this->permutation_list,this->ui->sizeSeq->value(),
                         this->ui->mtxIntervals->value(),this->ui->stepsSize->value(),this->ui->absValMtx->isChecked());
    }
}

void AnalysisWindow::hideSubWindow(QMdiSubWindow *w)
{
    w->hide();
}

void AnalysisWindow::genSelectedSeq()
{
    this->permutation_list.clear();
    QList<int> idx;
    this->permutation(this->events.toList(),idx,0,this->ui->sizeSeq->value());
    this->showPermutationStats();
}

void AnalysisWindow::delSelectedSeq(int index)
{
    QListWidget *l = this->sequences.at(index);
    if(l) delete l;
    this->sequences.removeAt(index);
}

void AnalysisWindow::genRandomSequence()
{
    int nlines = this->ui->sequence->count();
    if(nlines > 1){
        QVariantList ev;
        for(int l=0; l < nlines; l++){
            QString current = this->ui->sequence->item(l)->text().split(',').last();
            ev.push_back(current);
        }
        this->bootstrap_list = this->statsModule->bootstrap(ev,this->nPermutations);
        this->ui->tableRandom->setRowCount(0);
        this->ui->tableRandom->setColumnCount(this->nPermutations);
        for(int i=0; i < nlines; i++){
            int row = this->ui->tableRandom->rowCount();
            this->ui->tableRandom->insertRow(row);
            for(int j=0; j < this->nPermutations; j++){
                QString event = this->bootstrap_list.at(j).at(i).toString();
                QTableWidgetItem* item = new QTableWidgetItem(event);
                this->ui->tableRandom->setItem(i,j,item);
            }
        }
        this->ui->tabSequence->setCurrentIndex(1);
    }
}

void AnalysisWindow::showSessionStats()
{
    Database db;
    QVariantList listEvents;
    if(this->ui->sessions->selectedItems().size() == 0){
        for(int s=0; s < this->ui->sessions->rowCount(); s++){
            unsigned int idSession = this->ui->sessions->item(s,0)->text().toUInt();
            QList<Actions> actions = db.getSequence(idSession);
            for(int a = 0; a < actions.size(); a++){
                Actions act = actions.at(a);
                QString ev = act.getEventDescription();
                listEvents.push_back(ev.toLower().simplified());
            }
        }
    } else {
        int sizeCollumns = this->ui->sessions->columnCount();
        for(int s=0; s < this->ui->sessions->selectedItems().size(); s=s+sizeCollumns){
            unsigned int idSession = this->ui->sessions->selectedItems().at(s)->text().toUInt();
            QList<Actions> actions = db.getSequence(idSession);
            for(int a = 0; a < actions.size(); a++){
                Actions act = actions.at(a);
                QString ev = act.getEventDescription();
                listEvents.push_back(ev.toLower().simplified());
            }
        }
    }
    PlotWindow* plot = this->showFrequenceStats(listEvents,tr("Sessões"),tr("Frequência Absoluta"),tr("Frequência das Sessões"), true);
    this->mdi->addSubWindow(plot);
    plot->showMaximized();
}

void AnalysisWindow::showSequenceStats()
{
    Database db;
    StatisticMap behaivors;


    QVector<double> sessionsTicks;
    QList<int> idSession;
    QList<QString> set_line;
    QList<QList<double> > set_E;
    QList<QList<double> > set_O;
    QList<QList<double> > set_R;
    QList<QMap<int, QPair<double,double> > > set_VE;
    QList<QMap<int, QPair<double,double> > > set_VO;
    QList<QMap<int, QPair<double,double> > > set_VR;
    QList<QVector<QString> > set_sessionsLabels;
    QList<QVector<QString> > set_infos;

    if (this->ui->sessions->selectedItems().size() == 0){
       for(int s=0; s < this->ui->sessions->rowCount(); s++){
           idSession.push_back(this->ui->sessions->item(s,0)->text().toUInt());
       }
    }
    else{
        int sizeCollumns = this->ui->sessions->columnCount();
        for(int s=0; s < this->ui->sessions->selectedItems().size(); s=s+sizeCollumns){
            idSession.push_back(this->ui->sessions->selectedItems().at(s)->text().toUInt());
        }
    }

    QVector<QString> sessionsLabels;
    QVector<QString> infos;

    for (int i=0; i<idSession.size(); i++){
        QList<Actions> actions = db.getSequence(idSession[i]);
        QVariantList behavior_session;
        for(int a = 0; a < actions.size(); a++){
            Actions act = actions.at(a);
            QVariant ev = act.getEventDescription();
            behavior_session.push_back(ev);
        }
        behaivors.insertMulti(db.subjectExist(db.getSession(idSession[i]).getSubject()),behavior_session);
        sessionsLabels.push_back("S:"+QString::number(idSession[i]));
//        sessionsTicks.push_back(s+2); //FIXME
        infos.push_back(db.getSession(idSession[i]).getDescription().toString());
    }

    for(int s=0; s < this->sequences.size(); s++){
        list_behavior list_us;
        QString line_us;
        for(int l=0; l < this->sequences.at(s)->count(); l++){
            list_us.push_back(QVariantList());
            QString line = this->sequences.at(s)->item(l)->text();
            line_us.append(line);
            line_us.append("; ");
            line.remove(0,line.indexOf("{")+1);
            line.remove("}");
            line.remove(" ");
            QStringList us = line.split(",",QString::SkipEmptyParts);
            QString u;
            foreach (u, us) {
                list_us.last().push_back(u);
            }
        }
        line_us.remove(line_us.size()-1,1);
        set_line.push_back(line_us);
        QList<QList<double> > result = this->calc_statistics(list_us,behaivors.values());
        QList<double> E = result.at(0);
        QList<double> O = result.at(1);
        QList<double> R = result.at(2);

        QMap<int, QPair<double,double> > VE = this->statsModule->V_Map(list_us, behaivors, Expected);
        QMap<int, QPair<double,double> > VO;
        if (this->ui->absolut->isChecked()){
            VO = this->statsModule->V_Map(list_us, behaivors, Observed);
        }
        else{
            VO = this->statsModule->V_Map(list_us, behaivors, Probability);
        }
        QMap<int, QPair<double,double> > VR = this->statsModule->V_Map(list_us, behaivors, Residue);


        QPair<double, double> E_all = this->statsModule->V(VE);
        QPair<double, double> O_all = this->statsModule->V(VO);
        QPair<double, double> R_all = this->statsModule->V(VR);
        sessionsTicks.push_front(1);
        VE.insertMulti(-1,E_all);
        VO.insertMulti(-1,O_all);
        VR.insertMulti(-1,R_all);

        set_VE.push_back(VE);
        set_VO.push_back(VO);
        set_VR.push_back(VR);
        set_E.push_back(E);
        set_O.push_back(O);
        set_R.push_back(R);
        set_sessionsLabels.push_back(sessionsLabels);
        set_infos.push_back(infos);


    }

    switch (this->showtype) {
    case 0:
//        this->showGraphicStats(E,O,R,sessionsLabels,infos,sessionsTicks);
        break;
    case 1:
        this->showTableStats(set_line,set_E,set_O,set_R,set_VE,set_VO,set_VR,set_sessionsLabels,set_infos);
        break;
    case 2:
//        this->showNetStats(E,O,R,sessionsLabels,infos);
        break;
    case 3:
//        this->saveCsvStats(E,O,R,sessionsLabels,infos);
        break;
    default:
        break;
    }
}

QList<QList<double> > AnalysisWindow::calc_statistics(list_behavior set_us, list_behavior behaivors){
    QList<double> E;
    QList<double> O;
    QList<double> R;
    QList<QList<double> > result;

    E = this->statsModule->E(set_us,behaivors);
    if (this->ui->absolut->isChecked()){
        O = this->statsModule->O(set_us,behaivors);
    }
    else{
        O = this->statsModule->P(set_us,behaivors);
    }
    R = this->statsModule->R(set_us,behaivors);

    result.push_back(E);
    result.push_back(O);
    result.push_back(R);

    return result;
}

void AnalysisWindow::showPermutationStats()
{
    QMessageBox::StandardButton r = QMessageBox::No;
    if(this->hasData){
        r = QMessageBox::question(this, tr("Novo cálculo"), tr("Você deseja refazer o cálculo?"),
                                  QMessageBox::Yes|QMessageBox::No);
    }
    if (r == QMessageBox::Yes || !this->hasData) {
        Database db;
        list_behavior behaivors;
        QList< QVariantList > events;
        QList< QList<int> > indexes;
        QList<int> subjects;
        QList<int> idSession;

        if (this->ui->sessions->selectedItems().size() == 0){
           for(int s=0; s < this->ui->sessions->rowCount(); s++){
               idSession.push_back(this->ui->sessions->item(s,0)->text().toUInt());
           }
        }
        else{
            int sizeCollumns = this->ui->sessions->columnCount();
            for(int s=0; s < this->ui->sessions->selectedItems().size(); s=s+sizeCollumns){
                idSession.push_back(this->ui->sessions->selectedItems().at(s)->text().toUInt());
            }
        }

        for (int i=0; i<idSession.size(); i++){
            int subject = db.subjectExist(db.getSession(idSession[i]).getSubject());
            QList<Actions> actions = db.getSequence(idSession[i]);
            QList<QVariant> behavior_session;
            QVariantList tmp_ev;
            QList<int> tmp_idx;
            for(int a = 0; a < actions.size(); a++){
                Actions act = actions.at(a);
                QString ev = act.getEventDescription();
                behavior_session.push_back(ev);
                tmp_ev.push_back(ev);
                tmp_idx.push_back(a);
            }
            events.push_back(tmp_ev);
            indexes.push_back(tmp_idx);
            behaivors.push_back(behavior_session);
            subjects.push_back(subject);
        }

        this->statsModule->setEvents(events);
        this->statsModule->setIndexes(indexes);
        this->statsModule->setSessions(behaivors,subjects);
        this->statsModule->setPermutationList(this->permutation_list);
        this->statsModule->setPermutationSize(this->nPermutations);
        this->statsModule->setTypeRun('P');
        this->statsModule->setTailedAlpha(this->tailed,this->alfa);
        this->statsModule->setFilterPvalue(this->filterPvalue);
        this->ui->genSeq->setEnabled(false);
        this->statsModule->start();
        this->ui->cancelProcess->setEnabled(true);
        this->hasData = false;
    } else if(this->hasData) {
        this->showProcessedDataPermutation();
    }
}

void AnalysisWindow::showData(QList<double> tmp_E, QList<double> tmp_O,
                              QList<double> tmp_Rs, QMap<int, QPair<double, double> > VE,
                              QMap<int, QPair<double, double> > VO,
                              QMap<int, QPair<double, double> > VR, QVector<QString> tmp_sessionsLabels,
                              QVector<QString> tmp_infos, int s, QList<QPair<double, double> > Ps)
{
    QList<double> Rs;
    QList<double> E;
    QList<double> O;
    QList<double> pvalues;
    QVector<QString> sessionsLabels;
    QVector<QString> infos;
    QVector<double> sessionsTicks;
    int tick = 0;
    for(int i = 0; i < Ps.size(); i++) {
        QPair<double,double> pv = Ps.at(i);
        bool valid = false;
        if(this->filterPvalue){
            double reference = this->alfa;
            if(this->tailed == 0){
                reference = this->alfa/2.0;
                double p;
                if(pv.first < pv.second) p=pv.first;
                else p=pv.second;
                if(p<=reference){
                    pvalues.push_back(p);
                    valid=true;
                }
            } else if((pv.first < pv.second) && tailed == -1 && (pv.first <= reference)){
                pvalues.push_back(pv.first);
                valid=true;
            } else if((pv.first >= pv.second) && tailed == 1 && (pv.second <= reference)){
                pvalues.push_back(pv.second);
                valid=true;
            }
        }else {
            valid=true;
            if(pv.first < pv.second) pvalues.push_back(pv.first);
            else pvalues.push_back(pv.second);
        }
        if(valid){
            E.push_back(tmp_E.at(i));
            O.push_back(tmp_O.at(i));
            Rs.push_back(tmp_Rs.at(i));
            sessionsLabels.push_back(tmp_sessionsLabels.at(i));
            tick++;
            sessionsTicks.push_back(tick);
            infos.push_back(tmp_infos.at(i));
        }
    }
    switch (this->showtype) {
    case 0:
        this->showGraphicStats(E,O,Rs,sessionsLabels,infos,sessionsTicks,pvalues);
        break;
    case 1:
//        this->showTableStats(E,O,Rs,VE,VO,VR,sessionsLabels,infos,s,pvalues);
        break;
    case 2:
        this->showNetStats(E,O,Rs,sessionsLabels,infos,pvalues);
        break;
    case 3:
        this->saveCsvStats(E,O,Rs,sessionsLabels,infos,pvalues);
        break;
    default:
        break;
    }
}

PlotWindow* AnalysisWindow::showFrequenceStats(QVariantList data, QString xlabel, QString title, QString legend, bool sorted)
{
    QMap<QVariant,int> freq;
    if(sorted){
        freq = this->statsModule->frequence(data);
    } else {
        freq = this->statsModule->frequence(data,this->tailed);
    }

    PlotWindow* plt = new PlotWindow(this->mdi);
    title += " - "+QString::number(nwin);
    plt->setWindowTitle(title);
    plt->showFrequenceStats(freq,xlabel,legend,sorted);
    return plt;
}

void AnalysisWindow::showGraphicStats(QList<double> E, QList<double> O, QList<double> R,
                                      QVector<QString> sessionsLabels, QVector<QString> infos,
                                      QVector<double> sessionsTicks, QList<double> pvalues)
{
    QTabWidget* statsWidget = new QTabWidget(this->mdi);
    statsWidget->setMinimumSize(600,400);

    QPair<double,double> VE = this->statsModule->V(E);
    QPair<double,double> VO = this->statsModule->V(O);
    QPair<double,double> VR = this->statsModule->V(R);

    QString labX = tr("Sessões");
    QString labY = tr("Valor Esperado");
    QString title = tr("Valor Esperado - Sequência - Análise ")+QString::number(this->nwin);
    PlotWindow* panelE = this->showHistogram(E.toVector(),sessionsTicks,VE,
                                             sessionsLabels,labX,labY,title,this->colorExpected);
    statsWidget->addTab(panelE,labY);

    labY = tr("Valor Observado");
    title = tr("Valor Observado - Sequência - Análise ")+QString::number(this->nwin);
    PlotWindow* panelO = this->showHistogram(O.toVector(),sessionsTicks,VO,
                                             sessionsLabels,labX,labY,title,this->colorObserved);
    statsWidget->addTab(panelO,labY);

    labY = tr("Resíduo");
    title = tr("Resíduo - Sequência - Análise ")+QString::number(this->nwin);
    PlotWindow* panelR = this->showHistogram(R.toVector(),sessionsTicks,VR,
                                             sessionsLabels,labX,labY,title,this->colorResidue);
    statsWidget->addTab(panelR,labY);

    if(!pvalues.isEmpty()){
        QPair<double,double> VP = this->statsModule->V(pvalues);
        labY = tr("P-Valor");
        title = tr("P-Valor - Sequência - Análise ")+QString::number(this->nwin);
        PlotWindow* panelP = this->showHistogram(pvalues.toVector(),sessionsTicks,VP,sessionsLabels,
                                                      labX,labY,title,this->colorUpper);
        statsWidget->addTab(panelP,labY);
    }

    QListWidget *informations = new QListWidget(statsWidget);
    for(int f=0; f < infos.size(); f++){
        QString info = sessionsLabels.at(f);
        info.append(" = {");
        info.append(infos.at(f));
        info.append("}");
        informations->addItem(info);
    }
    statsWidget->addTab(informations,tr("Informações"));

    this->mdi->addSubWindow(statsWidget);
    title = tr("Estatísticas ")+QString::number(nwin)+tr(" - Todas combinações");
    statsWidget->setWindowTitle(title);
    statsWidget->show();
}

void AnalysisWindow::saveCsvStats(QList<double> E, QList<double> O, QList<double> R,
                                  QVector<QString> sessionsLabels, QVector<QString> infos, QList<double> pvalues)
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Salvar Arquivo CSV"), QDir::homePath(),".csv");
    if(filename != ""){
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
            return;
        }
        QTextStream csv(&file);
        for(int s=0; s < this->sequences.size(); s++){
            csv << tr("Sequência") << endl;
            for(int l=0; l < this->sequences.at(s)->count(); l++){
                csv << this->sequences.at(s)->item(l)->text() << endl;
            }
        }
        csv << tr("Identificador") << ";";
        csv << tr("Valor Estimado")  << ";" << tr("Média") << ";" << tr("Variância") << ";";
        csv << tr("Valor Observado") << ";" << tr("Média") << ";" << ";" << tr("Variância") << ";";
        csv << tr("Resíduo")         << ";" << tr("Média") << ";" << tr("Variância") << ";";
        if(!pvalues.isEmpty()){
            csv << tr("PValue") << ";";
        }
        csv << tr("Informações") << endl;
        QPair<double,double> MeanVarE = this->statsModule->V(E);
        QPair<double,double> MeanVarO = this->statsModule->V(O);
        QPair<double,double> MeanVarR = this->statsModule->V(R);
        QVariant VE = MeanVarE.second;
        if(VE.toInt() == -1) VE = "-";
        QVariant VO = MeanVarO.second;
        if(VO.toInt() == -1) VO = "-";
        QVariant VR = MeanVarR.second;
        if(VR.toInt() == -1) VR = "-";
        for(int v=0; v < E.size(); v++){
            csv << sessionsLabels.at(v) << ";";
            csv << E.at(v) << ";" << VR.toString() << ";" << MeanVarE.first << ";";
            csv << O.at(v) << ";" << VO.toString() << ";" << MeanVarO.first << ";";
            csv << R.at(v) << ";" << VR.toString() << ";" << MeanVarR.first << ";";
            if(!pvalues.isEmpty()){
                csv << pvalues.at(v) << ";";
            }
            csv << infos.at(v) << endl;
        }
        file.close();
    }
}

void AnalysisWindow::showTableStats(QList<QString> set_line, QList<QList<double> > E, QList<QList<double> > O, QList<QList<double> > R,
                                    QList<QMap<int, QPair<double, double> > > VE,
                                    QList<QMap<int, QPair<double, double> > > VO,
                                    QList<QMap<int, QPair<double, double> > > VR,
                                    QList<QVector<QString> > sessionsLabels,
                                    QList<QVector<QString> > infos,
                                    QList<QList<double> > pvalues)
{   
    ViewTableStats* view = new ViewTableStats(this->mdi);
    view->setData(set_line,sessionsLabels,infos,O,E,R,pvalues,VE,VO,VR);
//    view->setWindowTitle(title);
    this->mdi->addSubWindow(view);
    view->show();
}

void AnalysisWindow::showNetStats(QList<double> E, QList<double> O, QList<double> R, QVector<QString> sessionsLabels, QVector<QString> infos, QList<double> pvalues)
{
    QTabWidget* statsWidget = new QTabWidget(this->mdi);
    statsWidget->setMinimumSize(600,400);

    Graph ge;
    double scaleFactor =  1000;
    for(int i = 0; i < E.size(); i++){
        QString name = sessionsLabels.at(i);
        double size = E.at(i);
        QString info = QString::number(size);
        ge.addNode(name,info,1+std::abs(size)*scaleFactor);
    }
    QString lab = tr("Valor Esperado");
    ge.getGraphWindow()->showMaximized();
    ge.getGraphWindow()->updateEdgesNormalization();
    ge.getGraphWindow()->updateNodesNormalization();
    ge.getGraphWindow()->drawGraph("dot");
    statsWidget->addTab(ge.getGraphWindow(),lab);

    Graph go;
    scaleFactor =  1;
    for(int i = 0; i < O.size(); i++){
        QString name = sessionsLabels.at(i);
        double size = O.at(i);
        QString info = QString::number(size);
        go.addNode(name,info,1+std::abs(size)*scaleFactor);
    }
    lab = tr("Valor Observado");
    go.getGraphWindow()->showMaximized();
    go.getGraphWindow()->updateEdgesNormalization();
    go.getGraphWindow()->updateNodesNormalization();
    go.getGraphWindow()->drawGraph("dot");
    statsWidget->addTab(go.getGraphWindow(),lab);

    Graph gr;
    scaleFactor =  10000;
    for(int i = 0; i < R.size(); i++){
        QString name = sessionsLabels.at(i);
        double size = R.at(i);
        QString info = QString::number(size);
        gr.addNode(name,info,1+std::abs(size)*scaleFactor);
    }
    lab = tr("Valor Observado");
    gr.getGraphWindow()->showMaximized();
    gr.getGraphWindow()->updateEdgesNormalization();
    gr.getGraphWindow()->updateNodesNormalization();
    gr.getGraphWindow()->drawGraph("dot");
    statsWidget->addTab(gr.getGraphWindow(),lab);

    this->mdi->addSubWindow(statsWidget);
    QString title = tr("Estatísticas ")+QString::number(nwin);
    statsWidget->setWindowTitle(title);
    statsWidget->show();
}

void AnalysisWindow::setConfig()
{
    if(this->config->exec()){
        this->refreshConfig();
    }
}

void AnalysisWindow::refreshConfig()
{
    this->showMean = this->config->ui->mean->isChecked();
    this->showVariance = this->config->ui->variance->isChecked();
    this->showLegend = this->config->ui->legend->isChecked();
    this->filterPvalue = this->config->ui->filterPvalue->isChecked();
    if(this->config->ui->viewGraph->isChecked()) this->showtype = 0;
    if(this->config->ui->viewTable->isChecked()) this->showtype = 1;
    if(this->config->ui->viewNet->isChecked()) this->showtype = 2;
    if(this->config->ui->viewFile->isChecked()) this->showtype = 3;
    this->colorExpected=this->config->colorExpected;
    this->colorObserved=this->config->colorObserved;
    this->colorResidue=this->config->colorResidue;
    this->colorFrequence=this->config->colorFrequence;
    this->colorLower=this->config->colorLower;
    this->colorUpper=this->config->colorUpper;
    if(this->config->ui->tResidue->isChecked()) this->testType = 0;
    if(this->config->ui->tVariance->isChecked()) this->testType = 1;
    this->nPermutations=this->config->ui->nPermutations->value();
    this->alfa=this->config->ui->alfa->value();
    if(this->config->ui->lower->isChecked()) this->tailed = -1;
    if(this->config->ui->bitailed->isChecked()) this->tailed = 0;
    if(this->config->ui->upper->isChecked()) this->tailed = 1;
    this->filterPvalue = this->config->ui->filterPvalue->isChecked();

    this->withZeros=true;
    this->colorMean=QColor(Qt::black);
    this->colorVar=QColor(255,50,30,60);
}

void AnalysisWindow::drawSessionGraph()
{
    int nlines = this->ui->sequence->count();
    if(nlines > 1){
        Graph g;
        QString last = this->ui->sequence->item(0)->text().split(',').last();
        g.addNode(last,"");
        for(int l=1; l < nlines; l++){
            QString current = this->ui->sequence->item(l)->text().split(',').last();
            g.addNode(current,"");
            QString edgeName=last+"->"+current;
            g.addEdge(edgeName,last,current);
            last=current;
        }
        this->mdi->addSubWindow(g.getGraphWindow());
        g.getGraphWindow()->showMaximized();
        g.getGraphWindow()->updateEdgesNormalization();
        g.getGraphWindow()->updateNodesNormalization();
        g.getGraphWindow()->drawGraph("dot");
    }

}

void AnalysisWindow::statisticsTests()
{
    Database db;
    StatisticMap behaivors;
    list_behavior random_behavior;
    QVector<QString> tmp_sessionsLabels;
    QVector<QString> tmp_infos;
    if(this->ui->sessions->selectedItems().size() == 0){
        for(int s=0; s < this->ui->sessions->rowCount(); s++){
            QVariantList events;
            unsigned int idSession = this->ui->sessions->item(s,0)->text().toUInt();
            QList<Actions> actions = db.getSequence(idSession);
            QVariantList behavior_session;
            for(int a = 0; a < actions.size(); a++){
                Actions act = actions.at(a);
                QVariant ev=act.getEventDescription();
                behavior_session.push_back(ev);
                events.push_back(ev);
            }
            this->bootstrap_list = this->statsModule->bootstrap(events,this->nPermutations);
            random_behavior.append(this->bootstrap_list);
            behaivors.insertMulti(db.subjectExist(db.getSession(idSession).getSubject()),behavior_session);
            tmp_sessionsLabels.push_back("S:"+QString::number(idSession));
            tmp_infos.push_back(db.getSession(idSession).getDescription().toString());
        }
    } else {
        int sizeCollumns = this->ui->sessions->columnCount();
        for(int s=0; s < this->ui->sessions->selectedItems().size(); s=s+sizeCollumns){
            QVariantList events;
            unsigned int idSession = this->ui->sessions->selectedItems().at(s)->text().toUInt();
            QList<Actions> actions = db.getSequence(idSession);
            QVariantList behavior_session;
            for(int a = 0; a < actions.size(); a++){
                Actions act = actions.at(a);
                QVariant ev = act.getEventDescription();
                behavior_session.push_back(ev);
                events.push_back(ev);
            }

            this->bootstrap_list = this->statsModule->bootstrap(events,this->nPermutations);
            random_behavior.append(this->bootstrap_list);
            behaivors.insert(db.subjectExist(db.getSession(idSession).getSubject()), behavior_session);
            tmp_sessionsLabels.push_back("S:"+QString::number(idSession));
            tmp_infos.push_back(db.getSession(idSession).getDescription().toString());
        }
    }
    for(int s=0; s < this->sequences.size(); s++){
        list_behavior set_us;
        for(int l=0; l < this->sequences.at(s)->count(); l++){
            set_us.push_back(QVariantList());
            QString line = this->sequences.at(s)->item(l)->text();
            line.remove(0,line.indexOf("{")+1);
            line.remove("}");
            line.remove(" ");
            QStringList us = line.split(",",QString::SkipEmptyParts);
            QString u;
            foreach (u, us) {
                set_us.last().push_back(u);
            }
        }
        QList<QList<double> > tmp_stats = this->calc_statistics(set_us,behaivors.values());
        QList<double> tmp_E = tmp_stats.at(0);
        QList<double> tmp_O = tmp_stats.at(1);
        QList<double> tmp_Rs = tmp_stats.at(2);
        QList<double> dist = this->statsModule->R(set_us,random_behavior);
        QList< QPair<double,double> > Ps = this->statsModule->pvalue(tmp_Rs,dist);


        QMap<int, QPair<double,double> > VE = this->statsModule->V_Map(set_us, behaivors, Expected);
        QMap<int, QPair<double,double> > VO;
        if (this->ui->absolut->isChecked()){
            VO = this->statsModule->V_Map(set_us, behaivors, Observed);
        }
        else{
            VO = this->statsModule->V_Map(set_us, behaivors, Probability);
        }
        QMap<int, QPair<double,double> > VR = this->statsModule->V_Map(set_us, behaivors, Residue);

        this->showData(tmp_E,tmp_O,tmp_Rs,VE,VO,VR,tmp_sessionsLabels,tmp_infos,s,Ps);

    }
}

void AnalysisWindow::showProcessedDataPermutation()
{
    this->ui->genSeq->setEnabled(true);
    this->ui->cancelProcess->setDisabled(true);
    this->hasData = true;
    this->ui->progressBar->setValue(0);
    int np = this->statsModule->getPermutationSize();
    for (int i=0; i<np; i++){
        this->showData(this->statsModule->getE(i),this->statsModule->getO(i),this->statsModule->getR(i),
                       this->statsModule->getVE(i), this->statsModule->getVO(i), this->statsModule->getVR(i),
                       this->statsModule->getLabels(),this->statsModule->getInfos(),-1,this->statsModule->getP());
    }
}

void AnalysisWindow::cancelProcessPermutation()
{
    QMessageBox::StandardButton r = QMessageBox::No;
    r = QMessageBox::question(this, tr("Cancelar cálculo"), tr("Você deseja realmente cancelar o cálculo?"),
                              QMessageBox::Yes|QMessageBox::No);
    if (r == QMessageBox::Yes) {
        this->statsModule->setStopThreadStatus(true);
        this->hasData = false;
        this->ui->genSeq->setEnabled(true);
    }
}

void AnalysisWindow::updateProgressPemutation(double p)
{
    this->ui->progressBar->setValue(p*100);
}

void AnalysisWindow::refreshTableEvents()
{
    this->fillSetEvents();
    this->fillPagesSeq();
}

void AnalysisWindow::showProcessedDataPhylo()
{
    this->hasPhyloData = true;
    this->ui->showMtx->setEnabled(true);
    this->ui->stopMtx->setEnabled(false);
    ViewPhylogenetics *view = new ViewPhylogenetics(this->mdi);
    view->showPhylogenetis(this->phyloModule->getMO(),this->phyloModule->getME(),
                          this->phyloModule->getMR(),this->phyloModule->getMP(),
                          this->phyloModule->getSpecies(),this->phyloModule->getBehaviors(),
                          this->ui->mtxIntervals->value());
    this->mdi->addSubWindow(view);
    view->show();
}

void AnalysisWindow::cancelProcessPhylo()
{
    QMessageBox::StandardButton r = QMessageBox::No;
    r = QMessageBox::question(this, tr("Cancelar cálculo"), tr("Você deseja realmente cancelar o cálculo da filogenia?"),
                              QMessageBox::Yes|QMessageBox::No);
    if (r == QMessageBox::Yes) {
        this->phyloModule->setStopThreadStatus(true);
        this->hasPhyloData = false;
        this->ui->showMtx->setEnabled(true);
    }
}

void AnalysisWindow::updateProgressPhylo(double p)
{
    this->ui->progressPhylo->setValue(p*100);
}

void AnalysisWindow::refreshSpeciesList()
{
    int nrows = this->ui->sessions->rowCount();
    this->ui->speciesTable->setRowCount(0);
    QStringList speciesList;
    for(int s=0; s < nrows; s++){
        QString specieName = this->ui->sessions->item(s,2)->text();
        speciesList.push_back(specieName);
    }
    speciesList.removeDuplicates();
    for(int s=0; s < speciesList.size(); s++){
        QTableWidgetItem* item = new QTableWidgetItem(speciesList.at(s));
        int r = this->ui->speciesTable->rowCount();
        this->ui->speciesTable->insertRow(r);
        this->ui->speciesTable->setItem(r,0,item);
    }
}

void AnalysisWindow::upSpecie()
{
    if(this->ui->speciesTable->selectedItems().size() == 1){
        QTableWidgetItem* it = this->ui->speciesTable->selectedItems().at(0);
        int r = it->row();
        if(r > 0){
            QString swp = this->ui->speciesTable->item(r-1,0)->text();
            this->ui->speciesTable->item(r-1,0)->setText(it->text());
            it->setText(swp);
            this->ui->speciesTable->clearSelection();
            this->ui->speciesTable->item(r-1,0)->setSelected(true);
        }
    }
}

void AnalysisWindow::downSpecie()
{
    if(this->ui->speciesTable->selectedItems().size() == 1){
        QTableWidgetItem* it = this->ui->speciesTable->selectedItems().at(0);
        int r = it->row();
        if(r < this->ui->speciesTable->rowCount()-1){
            QString swp = this->ui->speciesTable->item(r+1,0)->text();
            this->ui->speciesTable->item(r+1,0)->setText(it->text());
            it->setText(swp);
            this->ui->speciesTable->clearSelection();
            this->ui->speciesTable->item(r+1,0)->setSelected(true);
        }
    }
}

void AnalysisWindow::showPhyloMtx()
{
    QMessageBox::StandardButton r = QMessageBox::No;
    if(this->hasPhyloData){
        r = QMessageBox::question(this, tr("Novo cálculo"), tr("Você deseja recalcular as matrizes filogenéticas?"),
                                  QMessageBox::Yes|QMessageBox::No);
    }
    if (r == QMessageBox::Yes || !this->hasPhyloData){
        this->ui->progressBar->setValue(0);
        this->preparePhylogenetic(this->phyloModule);
        this->phyloModule->start();
        this->ui->showMtx->setEnabled(false);
        this->ui->stopMtx->setEnabled(true);
    } else {
        this->showProcessedDataPhylo();
    }
}

bool AnalysisWindow::checkDuplicated(int id)
{
    bool duplicate = false;
    for(int i=0; i<this->ui->sessions->rowCount(); i++){
        if(id == this->ui->sessions->item(i,0)->text().toInt()){
            duplicate = true;
            break;
        }
    }
    return duplicate;
}

void AnalysisWindow::fillPagesSeq(int page)
{
    QList<QString> events_name = this->events.toList();
    qSort(events_name);
    QTableWidget *t = this->table_op.at(page);
    t->clear();
    t->setRowCount(0);
    t->setColumnCount(4);
    int row = 0;
    for(int e = 0; e < events_name.size(); e++){
        int column = e%4;
        if(column == 0){
            row = t->rowCount();
            t->insertRow(row);
        }
        QTableWidgetItem* item = new QTableWidgetItem;
        item->setText(events_name.at(e));
        t->setItem(row,column,item);
    }
}

void AnalysisWindow::fillPagesSeq()
{
    QList<QString> events_name = this->events.toList();
    qSort(events_name);
    for(int p = 0; p < this->table_op.size(); p++){
        QTableWidget *t = this->table_op.at(p);
        t->clear();
        t->setRowCount(0);
        t->setColumnCount(4);
        int row = 0;
        for(int e = 0; e < events_name.size(); e++){
            int column = e%4;
            if(column == 0){
                row = t->rowCount();
                t->insertRow(row);
            }
            QTableWidgetItem* item = new QTableWidgetItem;
            item->setText(events_name.at(e));
            t->setItem(row,column,item);
        }
    }
}

void AnalysisWindow::fillSetEvents()
{
    Database db;
    this->events.clear();
    if(this->ui->sessions->selectedItems().size() == 0){
        for(int s=0; s < this->ui->sessions->rowCount(); s++){
            unsigned int idSession = this->ui->sessions->item(s,0)->text().toUInt();
            QList<Actions> actions = db.getSequence(idSession);
            for(int a = 0; a < actions.size(); a++){
                Actions act = actions.at(a);
                QString ev = act.getEventDescription();
                this->events.insert(ev);
            }
        }
    } else {
        int sizeCollumns = this->ui->sessions->columnCount();
        for(int s=0; s < this->ui->sessions->selectedItems().size(); s+=sizeCollumns){
            unsigned int idSession = this->ui->sessions->selectedItems().at(s)->text().toUInt();
            QList<Actions> actions = db.getSequence(idSession);
            for(int a = 0; a < actions.size(); a++){
                Actions act = actions.at(a);
                QString ev = act.getEventDescription();
                this->events.insert(ev);
            }
        }
    }
}

PlotWindow* AnalysisWindow::showHistogram(QVector<double> data, QVector<double> ticks, QPair<double,double> variances,
                                          QVector<QString> labels, QString labX, QString labY, QString title, QColor color)
{
    PlotWindow *panel = new PlotWindow(this);
    panel->setWindowTitle(title);
    panel->showHistogram(data,ticks,variances,labels,labX,labY,title,color);
    return panel;
}

PlotWindow *AnalysisWindow::showStackHistogram(QVector<double> lower, QVector<double> upper,
                                               QVector<double> ticks, QVector<QString> labels,
                                               QString labX, QString labY, QString title,
                                               QColor lColor, QColor uColor)
{
    PlotWindow *panel = new PlotWindow(this);
    panel->setWindowTitle(title);
    panel->showStackHistogram(lower,upper,ticks,labels,labX,labY,title,lColor,uColor);
    return panel;
}
