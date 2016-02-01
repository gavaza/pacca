#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QApplication *app, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->app = app;
    this->dirConfig = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    if(!QDir(this->dirConfig).exists()) QDir().mkdir(this->dirConfig);
    this->adjustShortcuts();
    this->linkSignals();
    this->logoff();
    this->connectdb = NULL;
    this->users_ui = NULL;
    this->ctl_sessions = NULL;
    this->ctl_species = NULL;
    this->ctl_subjects = NULL;
    this->dict_ui = NULL;
    this->countAnalysis=1;
}

MainWindow::~MainWindow()
{
    if(this->connectdb){
        this->connectdb->closeConnection();
        delete this->connectdb;
    }
    delete ui;
}

void MainWindow::linkSignals(){
    connect(this->ui->actionText,SIGNAL(triggered()),this,SLOT(executeImportText()));
    connect(this->ui->actionVideo,SIGNAL(triggered()),this,SLOT(executeImportVideo()));
    connect(this->ui->actionAudio,SIGNAL(triggered()),this,SLOT(executeImportAudio()));
    connect(this->ui->actionUsuario,SIGNAL(triggered()),this,SLOT(newuser()));
    connect(this->ui->actionAnalise,SIGNAL(triggered()),this,SLOT(executeAnalysis()));
    connect(this->ui->actionLogin,SIGNAL(triggered()),this,SLOT(login()));
    connect(this->ui->actionDicion_rio,SIGNAL(triggered()),this,SLOT(managerDict()));
    connect(this->ui->actionSess_es,SIGNAL(triggered()),this,SLOT(managerSessions()));
    connect(this->ui->actionSpecies,SIGNAL(triggered()),this,SLOT(managerSpecies()));
    connect(this->ui->actionIndiv_duos,SIGNAL(triggered()),this,SLOT(managerSubjects()));
    connect(this->ui->aboutQt,SIGNAL(triggered()),this,SLOT(aboutQt()));
    connect(this->ui->aboutPacca,SIGNAL(triggered()),this,SLOT(aboutPacca()));
    connect(this->ui->actionIdioma,SIGNAL(triggered()),this,SLOT(changeLanguage()));
    connect(this->ui->actionCascata,SIGNAL(triggered()),this->ui->mdiArea,SLOT(cascadeSubWindows()));
    connect(this->ui->actionLado_a_Lado,SIGNAL(triggered()),this->ui->mdiArea,SLOT(tileSubWindows()));
    connect(this->ui->actionExportODF,SIGNAL(triggered()),this,SLOT(executeExportText()));
    connect(this->ui->actionExportMDF,SIGNAL(triggered()),this,SLOT(executeExportTextMDF()));
    connect(this->ui->actionResetDB,SIGNAL(triggered()),this,SLOT(resetDatabase()));
    connect(this->ui->actionExportDB,SIGNAL(triggered()),this,SLOT(executeExportDB()));
    connect(this->ui->actionImportDB,SIGNAL(triggered()),this,SLOT(executeImportDB()));
}

void MainWindow::adjustShortcuts()
{
    this->ui->actionText->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
    this->ui->actionVideo->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    this->ui->actionAudio->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    this->ui->actionAnalise->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_G));
    this->ui->actionLogin->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_L));
    this->ui->actionDicion_rio->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
    this->ui->actionSess_es->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    this->ui->actionSpecies->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
    this->ui->actionUsuario->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_U));
    this->ui->actionIndiv_duos->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));
}
void MainWindow::saveSession(Sessions session)
{
    Database db;
    db.saveSession(session);
}

void MainWindow::executeImportVideo()
{
    this->executeImportMedia("video");
}

void MainWindow::executeImportAudio()
{
    this->executeImportMedia("audio");
}

void MainWindow::executeImportMedia(QString type)
{
    QString filename = "";
    DialogChooseDict d;
    if(d.exec()){
        QString dict = d.getDictionary();
        filename = QFileDialog::getOpenFileName(this, tr("Escolha o arquivo:"), QDir::homePath());
        if(filename != ""){
            this->ui->menuBar->setEnabled(false);
            this->video_ui = new VideoWindow(type,this->ui->mdiArea);
            connect(this->video_ui,SIGNAL(destroyed(QObject*)),this,SLOT(videowClosed()));
            this->video_ui->setDictionary(dict);
            this->video_ui->setFilename(filename);
            this->ui->mdiArea->addSubWindow(this->video_ui);
            this->video_ui->showMaximized();
        }
    }
    emit this->database_updated();
}

void MainWindow::executeAnalysis()
{
    this->analysis_ui = new AnalysisWindow(this->ui->mdiArea,countAnalysis,this->ui->mdiArea);
    this->countAnalysis++;
    this->ui->mdiArea->addSubWindow(this->analysis_ui);
    this->analysis_ui->showMaximized();
}

void MainWindow::setDatabaseStatus(bool status)
{
    QSettings settings("NuEvo","Pacca");
    settings.beginGroup("database");
    settings.setValue("databaseUnconfigured",status);
    settings.endGroup();
}

void MainWindow::connectDatabase()
{
    QString databaseName = this->dirConfig+"/pacca_database.sqlite";
    this->connectdb = new Connections("QSQLITE",databaseName);
    if(!this->connectdb->openConnection()){
        qDebug("Connection error");
    }
}

void MainWindow::resetDatabase()
{
    if(QMessageBox::question(this,tr("Reiniciar Banco de Dados"),
                             tr("Você tem certeza que deseja reiniciar o banco de dado?"
                                " Essa ação irá apagar todas as informações do banco!"))
            == QMessageBox::Yes){
        this->ui->mdiArea->closeAllSubWindows();
        this->connectdb->makeDatabaseTables();
        this->logoff();
    }
}


void MainWindow::executeImportText(bool append){
    if (!append) this->sessions.clear();
    DialogChooseSpecie spc;
    if(spc.exec()){
        int specie = spc.getSpecie().toInt();
        int subject = spc.getSubject().toInt();
        /* import from text */
        QStringList filename = QFileDialog::getOpenFileNames(this, tr("Importar análise do arquivo"), QDir::homePath(), tr("Arquivo ODF (*.odf);;Arquivo MDF (*.mdf)"));
        if (filename.size()==0) return;
        Database db;
        Text t;
        QList<Sessions> s = t.executeImportText(filename);
        for (int i=0; i<s.size(); i++){
            QSettings settings("NuEvo","Pacca");
            settings.beginGroup("global");
            s[i].setDecoder(settings.value("user"));
            s[i].setObserver(settings.value("user"));
            settings.endGroup();
            s[i].setSpecies(specie);
            s[i].setSubject(subject);
            db.saveSession(s.at(i));
            emit this->database_updated();
        }
        this->sessions.append(s);
    }
}

void MainWindow::executeExportText(){
    /* Dialog to choose */
    DialogSelectSession d;
    if(d.exec()){
        QList<QTableWidgetItem*> itens = d.getSelectedItens();

        /* file */
        QString path_base = QFileDialog::getSaveFileName(this, tr("Exportar dados em arquivo"), QDir::homePath(), tr("Arquivo ODF (*.odf)"));
        path_base = path_base.remove(path_base.size()-4,4);

        if (path_base.size()==0) return;

        /* Database */
        Database db;
        for(int i=0; i<itens.size(); i=i+6){

            unsigned int idSession = itens.at(i)->text().toInt();
            QString filename = path_base + QString(itens.at(i)->text());
            filename = filename.append(".odf");

            QList<Actions> actions = db.getSequence(idSession);
            QList<QString> infos;
            for (int j=i; j<i+6; j++){
                infos.push_back(itens.at(j)->text());
            }

            Text t;
            t.executeExportText(filename, actions, infos);
        }
    }
}

void MainWindow::executeExportTextMDF(){
    /* Dialog to choose */
    DialogSelectSession d;
    if(d.exec()){
        QList<QTableWidgetItem*> itens = d.getSelectedItens();

        /* file */
        QString filename = QFileDialog::getSaveFileName(this, tr("Exportar dados em arquivo"), QDir::homePath(), tr("Arquivo MDF (*.mdf)"));
        if (filename.size()==0) return;

        /* Database */
        Database db;
        QList< QList<Actions> > list_actions;
        QList< QList<QString> > list_infos;

        for (int i=0; i<itens.size(); i+=6){

            unsigned int idSession = itens.at(i)->text().toInt();
            QList<Actions> actions = db.getSequence(idSession);
            list_actions.push_back(actions);
            QList<QString> infos;
            for (int j=i; j<i+6; j++){
                infos.push_back(itens.at(j)->text());
            }
            list_infos.push_back(infos);
        }

        Text t;
        t.executeExportTextMDF(filename, list_actions, list_infos);
    }
}



void MainWindow::login()
{
    QSettings settings("NuEvo","Pacca");
    settings.beginGroup("database");
    bool databaseUnconfigured = settings.value("databaseUnconfigured",true).toBool();
    settings.endGroup();

    if (databaseUnconfigured || !QDir(this->dirConfig).exists("pacca_database.sqlite")){
        if (!this->connectdb) this->connectDatabase();
        this->connectdb->makeDatabaseTables();
        this->newuser();
        this->setDatabaseStatus();
        return;
    }

    if (!this->connectdb) this->connectDatabase();

    Database db;
    QList<Users> users = db.getAllUsers();
    if (users.size()>0){
        DialogLogin login(users);
        if(login.exec()){
            QString username = login.getName();
            QSettings settings("NuEvo","Pacca");
            settings.beginGroup("global");
            settings.setValue("user",username);
            settings.endGroup();
            this->logoff(true);
        }
    }
    else{
        this->newuser();
    }
}

void MainWindow::logoff(bool status)
{
    this->ui->menuBar->setEnabled(true);
    this->ui->menuNova->setEnabled(status);
    this->ui->menuControle->setEnabled(true);
    this->ui->actionLogin->setEnabled(true);
    this->ui->menuAjuda->setEnabled(true);
    this->ui->actionDicion_rio->setEnabled(status);
    this->ui->actionSpecies->setEnabled(status);
    this->ui->actionIndiv_duos->setEnabled(status);
    this->ui->actionSess_es->setEnabled(status);
    this->ui->menuSess_o->setEnabled(status);
    this->ui->actionAnalise->setEnabled(status);
    this->ui->actionAudio->setEnabled(status);
    this->ui->actionVideo->setEnabled(status);
    this->ui->actionText->setEnabled(status);
    this->ui->actionUsuario->setEnabled(status);
    this->ui->menuExportar->setEnabled(status);
    this->ui->menuBanco->setEnabled(true);
    this->ui->actionResetDB->setEnabled(true);
    this->ui->actionExportDB->setEnabled(status);
    this->ui->actionImportDB->setEnabled(true);
    this->ui->menuJanelas->setEnabled(true);
}

void MainWindow::newuser()
{
    if(this->users_ui  == NULL){
        this->users_ui = new ControlUsers(this->ui->mdiArea);
        connect(this->users_ui,SIGNAL(destroyed(QObject*)),this,SLOT(usersClosed()));
        this->users_ui->setWindowModality(Qt::ApplicationModal);
        this->swUser = this->ui->mdiArea->addSubWindow(this->users_ui);
    }
    this->users_ui->show();
    this->ui->mdiArea->setActiveSubWindow(this->swUser);
}

void MainWindow::managerDict()
{
    if(this->dict_ui == NULL){
        this->dict_ui = new ControlDictionary(this->ui->mdiArea);
        connect(this->dict_ui,SIGNAL(destroyed(QObject*)),this,SLOT(dictClosed()));
        this->dict_ui->setWindowModality(Qt::ApplicationModal);
        this->swDict = this->ui->mdiArea->addSubWindow(this->dict_ui);
    }
    this->dict_ui->show();
    this->ui->mdiArea->setActiveSubWindow(this->swDict);
}

void MainWindow::managerSessions()
{
    if(this->ctl_sessions == NULL){
        this->ctl_sessions = new ControlSessions(this->ui->mdiArea);
        connect(this->ctl_sessions,SIGNAL(destroyed(QObject*)),this,SLOT(sessionsClosed()));
        this->ctl_sessions->setWindowModality(Qt::ApplicationModal);
        this->swSsn = this->ui->mdiArea->addSubWindow(this->ctl_sessions);
    }
    this->ctl_sessions->show();
    this->ui->mdiArea->setActiveSubWindow(this->swSsn);
}

void MainWindow::managerSpecies()
{
    if(this->ctl_species == NULL){
        this->ctl_species = new ControlSpecies(this->ui->mdiArea);
        connect(this->ctl_species,SIGNAL(destroyed(QObject*)),this,SLOT(speciesClosed()));
        this->ctl_species->setWindowModality(Qt::ApplicationModal);
        this->swSpc = this->ui->mdiArea->addSubWindow(this->ctl_species);
    }
    this->ctl_species->show();
    this->ui->mdiArea->setActiveSubWindow(this->swSpc);
}

void MainWindow::managerSubjects()
{
    if(this->ctl_subjects == NULL){
        this->ctl_subjects = new ControlSubjects(this->ui->mdiArea);
        connect(this->ctl_subjects,SIGNAL(destroyed(QObject*)),this,SLOT(subjectsClosed()));
        this->ctl_subjects->setWindowModality(Qt::ApplicationModal);
        this->swSpc = this->ui->mdiArea->addSubWindow(this->ctl_subjects);
    }
    this->ctl_subjects->show();
    this->ui->mdiArea->setActiveSubWindow(this->swSpc);
}

void MainWindow::dictClosed()
{
    this->dict_ui = NULL;
}

void MainWindow::sessionsClosed()
{
    this->ctl_sessions = NULL;
}

void MainWindow::speciesClosed()
{
    this->ctl_species = NULL;
}

void MainWindow::subjectsClosed()
{
    this->ctl_subjects = NULL;
}

void MainWindow::usersClosed()
{
    this->users_ui = NULL;
}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this,tr("Sobre o Qt"));
}

void MainWindow::aboutPacca()
{
    QMessageBox::about(this,tr("Sobre o Pacca"),
                       tr("O aplicativo PACCA visa o estudo do comportamento, entendido como uma rede de ações sequenciais de um indivíduo, "
                          "ou de interações entre indivíduos. Ele permite a detecção de significância estatística em rotinas comportamentais "
                          "específicas (ou conjuntos de rotinas com alguns aspectos em comum), típicas de um indivíduo, de uma população, "
                          "ou de uma espécie, a depender do esquema amostral do estudo.\n\n"
                          "O aplicativo é fruto do trabalho de uma equipe que envolve desenvolvedores (Alex Santana e Luiz Gavaza) e "
                          "estatísticos (Lucas Santana Souza), sob a coordenação de Hilton Ferreira Japyassú, como parte do projeto "
                          "INOMEP (Integrando Níveis de Organização em Modelos Ecológicos Preditivos), coordenado por Charbel Niño El-Hani, e "
                          "financiado pelo CNPq e pela FAPESB, no âmbito do Programa de Apoio a Núcleos de Excelência (PRONEX)."));
}

void MainWindow::changeLanguage()
{
    DialogChooseLanguage d;
    d.includeMenssage(tr("O novo idioma só está disponível após reiniciar a aplicação."));
    if(d.exec()){
        QString lang = d.getLanguage();
        QSettings settings("NuEvo","Pacca");
        settings.beginGroup("global");
        settings.setValue("language",lang);
        settings.endGroup();
    }
}

void MainWindow::videowClosed()
{
    this->ui->menuBar->setEnabled(true);
    this->ui->mdiArea->setFocus();
    disconnect(this->video_ui,SIGNAL(destroyed(QObject*)),this,SLOT(videowClosed()));
}

void MainWindow::executeExportDB(){
    QString filename = QFileDialog::getSaveFileName(this, tr("Exportar banco de dados"),
                                                    QDir::homePath(), tr("Arquivo SQLite (*.sqlite)"));
    if (filename.size()==0) return;

    QFile destination(filename);
    if (destination.exists()) destination.remove();
    QFile::copy(this->dirConfig+"/pacca_database.sqlite", filename);
}

void MainWindow::executeImportDB(){
    QString filename = QFileDialog::getOpenFileName(this, tr("Importar banco de dados"),
                                                    QDir::homePath(), tr("Arquivo SQLite (*.sqlite)"));
    if (filename.size()==0) return;

    this->logoff();
    QFile database(this->dirConfig+"/pacca_database.sqlite");
    if(!QDir(this->dirConfig).exists()) QDir().mkdir(this->dirConfig);
    if (database.exists()){
        this->connectdb->closeConnection();
        database.remove();
    }
    QFile::copy(filename, this->dirConfig+"/pacca_database.sqlite");
    this->connectdb->openConnection();
    this->ui->mdiArea->closeAllSubWindows();
    this->setDatabaseStatus();
}
