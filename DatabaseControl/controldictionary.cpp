#include "controldictionary.h"
#include "ui_controldictionary.h"

ControlDictionary::ControlDictionary(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlDictionary)
{
    ui->setupUi(this);
    this->loadDict();
    this->ui->words->setEnabled(false);
    this->createConnexions();
}

ControlDictionary::~ControlDictionary()
{
    delete ui;
}

void ControlDictionary::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete){
    }
}

void ControlDictionary::createConnexions()
{
    connect(this->ui->addDict,SIGNAL(clicked()),this,SLOT(saveDict()));
    connect(this->ui->nameDict,SIGNAL(returnPressed()),this,SLOT(saveDict()));
    connect(this->ui->rmDict,SIGNAL(clicked()),this,SLOT(removeDict()));
    connect(this->ui->listDict,SIGNAL(itemSelectionChanged()),this,SLOT(loadEntries()));
    connect(this->ui->addEntry,SIGNAL(clicked()),this,SLOT(saveEntry()));
    connect(this->ui->word,SIGNAL(returnPressed()),this,SLOT(saveEntry()));
    connect(this->ui->rmEntry,SIGNAL(clicked()),this,SLOT(removeEntry()));
    connect(this->ui->listDict,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(saveOrigTextDict(int,int)));
    connect(this->ui->listDict,SIGNAL(cellEntered(int,int)),this,SLOT(saveOrigTextDict(int,int)));
    connect(this->ui->entries,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(saveOrigTextEntry(int,int)));
    connect(this->ui->entries,SIGNAL(cellEntered(int,int)),this,SLOT(saveOrigTextEntry(int,int)));
}

void ControlDictionary::loadDict()
{
    Database db;
    QList<QString> dicts = db.dictNames();
    this->ui->listDict->setRowCount(0);
    for(int d = 0; d < dicts.size(); d++){
        QTableWidgetItem *item  = new QTableWidgetItem;
        item->setText(dicts.at(d));
        int row = this->ui->listDict->rowCount();
        this->ui->listDict->insertRow(row);
        this->ui->listDict->setItem(row,0,item);
    }
}

void ControlDictionary::saveDict()
{
    QString name = this->ui->nameDict->text().simplified();
    if(name.size() > 0){
        Database db;
        Dictionary dict;
        dict.setName(name);
        db.insertDict(dict);
        this->loadDict();
        this->ui->nameDict->clear();
    }
}

void ControlDictionary::editDict(int r, int c)
{
    disconnect(this->ui->listDict,SIGNAL(cellChanged(int,int)),this,SLOT(editDict(int,int)));
    QString newContent = this->ui->listDict->item(r,c)->text().simplified();
    this->ui->listDict->item(r,c)->setText(this->origText);
    if(!this->existDict(newContent) && newContent.size() != 0){
        this->ui->listDict->item(r,c)->setText(newContent);
        Database db;
        db.editDict(this->origText,newContent);
        this->loadDict();
    } else {
        this->ui->listDict->item(r,c)->setText(this->origText);
    }
}

void ControlDictionary::saveOrigTextDict(int r, int c)
{
    this->origText = this->ui->listDict->item(r,c)->text();
    connect(this->ui->listDict,SIGNAL(cellChanged(int,int)),this,SLOT(editDict(int,int)));
}

void ControlDictionary::editEntry(int r, int c)
{
    disconnect(this->ui->entries,SIGNAL(cellChanged(int,int)),this,SLOT(editEntry(int,int)));
    QString newContent = this->ui->entries->item(r,c)->text().simplified();
    this->ui->entries->item(r,c)->setText(this->origText);
    bool exist = this->existEntry(newContent,c);
    if(!exist && newContent.size() != 0){
        this->ui->entries->item(r,c)->setText(newContent);
        QString dictName = this->ui->listDict->selectedItems().first()->text();
        QString code = this->ui->entries->item(r,0)->text().simplified();
        QString word = this->ui->entries->item(r,1)->text().simplified();
        Database db;
        if(c==0)
            db.editDictEntry(dictName,this->origText,code,word);
        else
            db.editDictEntry(dictName,code,code,word);
        this->loadEntries();
    } else {
        this->ui->entries->item(r,c)->setText(this->origText);
    }
}

void ControlDictionary::saveOrigTextEntry(int r, int c)
{
    this->origText = this->ui->entries->item(r,c)->text();
    connect(this->ui->entries,SIGNAL(cellChanged(int,int)),this,SLOT(editEntry(int,int)));
}

void ControlDictionary::removeDict()
{
    if(this->ui->listDict->selectedItems().size() > 0){
        QString name = this->ui->listDict->selectedItems().first()->text();
        if(QMessageBox::question(this,tr("Apagar dicionário"),
                                 tr("Você tem certeza que deseja apagar o dicionário selecionado?"))
                == QMessageBox::Yes){
            Database db;
            db.removeDict(name);
            this->loadDict();
            this->ui->entries->clear();
            this->ui->entries->setRowCount(0);
        }
    }
}

void ControlDictionary::saveEntry()
{
    QString code = this->ui->code->text().simplified();
    QString word = this->ui->word->text().simplified();
    QString nameDict = this->ui->listDict->selectedItems().first()->text();
    if(!this->existEntry(code,word) && word.size() > 0 && code.size() > 0){
        Database db;
        db.insertDictEntry(nameDict,code,word);
        this->loadEntries();
        this->ui->code->clear();
        this->ui->word->clear();
        this->ui->code->setFocus();
    } else {
        QMessageBox::information(this,tr("Nova entrada"),
                                 tr("Todos os campos são obrigatórios!\nNão pode repetir entrada já existente no dicionário."));
    }
}

void ControlDictionary::removeEntry()
{
    if(this->ui->entries->selectedItems().size() > 0){
        if(QMessageBox::question(this,tr("Apagar entradas de dicionário"),
                                 tr("Você tem certeza que deseja apagar as entradas de dicionário selecionadas?"))
                == QMessageBox::Yes){

            QString dictName = this->ui->listDict->selectedItems().first()->text();

            Database db;
            QList<int> rows;

            for (int i=0; i<this->ui->entries->selectedItems().size(); i+=2){
                QString code = this->ui->entries->selectedItems().at(i)->text();
                db.removeDictEntry(dictName,code);
                rows.push_back(this->ui->entries->selectedItems().at(i)->row());
            }
            while(rows.size()>0){
                this->ui->entries->removeRow(rows.last());
                rows.pop_back();
            }
        }
    }
}

bool ControlDictionary::existEntry(QString code, QString word)
{
    bool exist = false;
    for(int e = 0; e < this->ui->entries->rowCount(); e++){
        if(code == this->ui->entries->item(e,0)->text() || word == this->ui->entries->item(e,1)->text()){
            exist = true;
            break;
        }
    }
    return exist;
}

bool ControlDictionary::existEntry(QString text, unsigned int col)
{
    bool exist = false;
    for(int e = 0; e < this->ui->entries->rowCount(); e++){
        if(text == this->ui->entries->item(e,col)->text()){
            exist = true;
            break;
        }
    }
    return exist;
}

bool ControlDictionary::existDict(QString name)
{
    bool exist = false;
    for(int e = 0; e < this->ui->listDict->rowCount(); e++){
        if(name == this->ui->listDict->item(e,0)->text()){
            exist = true;
            break;
        }
    }
    return exist;
}

// TODO : Necessário reescrever para considerar que os itens deletados.
//        Da forma como está implementado, ocorrem travamentos.
void ControlDictionary::loadEntries()
{
    if(this->ui->listDict->selectedItems().size() > 0){
        this->ui->words->setEnabled(true);
        Database db;
        QString dictName = this->ui->listDict->selectedItems().first()->text();
        Dictionary dict = db.getDictionary(dictName);
        QMap<QString,QString> entries = dict.getEntries();
        QMapIterator<QString, QString> i(entries);
        this->ui->entries->setRowCount(0);
        while (i.hasNext()) {
            i.next();
            QTableWidgetItem *item_code  = new QTableWidgetItem;
            QTableWidgetItem *item_word  = new QTableWidgetItem;
            item_code->setText(i.key());
            item_word->setText(i.value());
            int row = this->ui->entries->rowCount();
            this->ui->entries->insertRow(row);
            this->ui->entries->setItem(row,0,item_code);
            this->ui->entries->setItem(row,1,item_word);
        }
    }
}
