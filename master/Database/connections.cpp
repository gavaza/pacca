#include "connections.h"

Connections::Connections(QString driver, QString database){
    this->db = QSqlDatabase::addDatabase(driver);
    if(!this->db.isValid()){
        qDebug("Database Error");
    }
    this->db.setDatabaseName(database);
}

bool Connections::openConnection(){
    if (!(this->db.open())) {
        QMessageBox::critical(0, QMessageBox::tr("Erro no banco de dados"), this->db.lastError().text());
        return false;
    }
    else return true;
}

void Connections::closeConnection(){
    if (this->db.isOpen()){
        this->db.close();
    }
}

bool Connections::makeDatabaseTables(){
    QSqlQuery query;

    query.exec("DROP TABLE IF EXISTS Actions;");
    query.exec("DROP TABLE IF EXISTS Events;");
    query.exec("DROP TABLE IF EXISTS Sessions;");
    query.exec("DROP TABLE IF EXISTS Users;");
    query.exec("DROP TABLE IF EXISTS Dictionary;");
    query.exec("DROP TABLE IF EXISTS EntryDict;");
    query.exec("DROP TABLE IF EXISTS Species;");

    query.exec("CREATE TABLE Users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT);");

    query.exec("CREATE TABLE Species (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT);");

    query.exec("CREATE TABLE Sessions (id INTEGER PRIMARY KEY AUTOINCREMENT, "
           " datesession DATETIME, datedecoding DATETIME, "
           " specie INTEGER, "
           " decoder INTEGER, "
           " observer INTEGER, "
           " description TEXT, "
           " subject TEXT, "
           " FOREIGN KEY(specie) REFERENCES Species(id), "
           " FOREIGN KEY(observer) REFERENCES Users(id), "
           " FOREIGN KEY(decoder) REFERENCES Users(id));");

    query.exec("CREATE TABLE States (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT);");

    query.exec("CREATE TABLE Events (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT);");

    query.exec("CREATE TABLE Actions (id INTEGER PRIMARY KEY AUTOINCREMENT,"
           " time REAL NOT NULL,"
           " session INTEGER, "
           " state INTEGER, "
           " event INTEGER, "
           " FOREIGN KEY(event)   REFERENCES Events(id), "
           " FOREIGN KEY(session) REFERENCES Sessions(id), "
           " FOREIGN KEY(state)  REFERENCES States(id));");

    query.exec("CREATE TABLE Dictionary (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT);");

    query.exec("CREATE TABLE EntryDict (id INTEGER PRIMARY KEY AUTOINCREMENT,"
           " code TEXT, "
           " word TEXT, "
           " dictionary INTEGER, "
           " FOREIGN KEY(dictionary)   REFERENCES Dictionary(id));");

    return true;
}
