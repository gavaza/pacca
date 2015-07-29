#include "database.h"

Database::Database()
{
}

void Database::showError(const QSqlError &err)
{
    QMessageBox::critical(0, QMessageBox::tr("Erro"),QMessageBox::tr("Erro no banco de dados: ") + err.text());
}

Sessions Database::fillSession()
{
    Sessions s;
    this->query.first();
    this->record = this->query.record();
    s.setId(this->query.value(this->record.indexOf("id")));
//    u.setName(this->query.value(this->record.indexOf("name")));
    return s;
}

Users Database::fillUser()
{
    Users u;
    this->query.first();
    this->record = this->query.record();
    u.setId(this->query.value(this->record.indexOf("id")));
    u.setName(this->query.value(this->record.indexOf("name")));
    return u;
}

Species Database::fillSpecie()
{
    Species s;
    this->query.first();
    this->record = this->query.record();
    s.setId(this->query.value(this->record.indexOf("id")));
    s.setName(this->query.value(this->record.indexOf("name")));
    return s;
}

Subjects Database::fillSubject()
{
    Subjects s;
    this->query.first();
    this->record = this->query.record();
    s.setId(this->query.value(this->record.indexOf("id")));
    s.setName(this->query.value(this->record.indexOf("name")));
    return s;
}

States Database::fillState()
{
    States s;
    this->query.first();
    this->record = this->query.record();
    s.setId(this->query.value(this->record.indexOf("id")).toUInt());
    s.setDescription(this->query.value(this->record.indexOf("name")).toString());
    return s;
}

Events Database::fillEvent()
{
    Events e;
    this->query.first();
    this->record = this->query.record();
    e.setId(this->query.value(this->record.indexOf("id")).toUInt());
    e.setDescription(this->query.value(this->record.indexOf("name")).toString());
    return e;
}

int Database::userExist(QVariant name)
{
    int id = this->cacheUserId.value(name.toString().toLower(),-1);
    if(id != -1) return id;

    this->query.prepare("Select id FROM Users WHERE Users.name=?");
    this->query.addBindValue(name.toString().toLower());
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return -1;
    }
    if(this->query.next()){
        id = this->query.value("id").toInt();
        this->cacheUserId.insert(name.toString().toLower(),id);
        return id;
    }
    return 0;
}

int Database::specieExist(QVariant name)
{
    this->query.prepare("Select id FROM Species WHERE Species.name=?");
    this->query.addBindValue(name.toString().toLower());
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return -1;
    }
    if(this->query.next()){
        int id = this->query.value("id").toInt();
        return id;
    }
    return 0;
}

int Database::subjectExist(QVariant name)
{
    this->query.prepare("Select id FROM Subjects WHERE Subjects.name=?");
    this->query.addBindValue(name.toString().toLower());
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return -1;
    }
    if(this->query.next()){
        int id = this->query.value("id").toInt();
        return id;
    }
    return 0;
}

int Database::stateExist(QVariant name)
{
    int id = this->cacheStateId.value(name.toString().toLower(),-1);
    if(id != -1) return id;

    this->query.prepare("Select id FROM States WHERE States.name=?");
    this->query.addBindValue(name.toString().toLower());
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return -1;
    }
    if(this->query.next()){
        id = this->query.value("id").toInt();
        this->cacheStateId.insert(name.toString().toLower(),id);
        return id;
    }
    return 0;
}

int Database::eventExist(QVariant name)
{
    int id = this->cacheEventId.value(name.toString().toLower(),-1);
    if(id != -1) return id;

    this->query.prepare("Select id FROM Events WHERE Events.name=?");
    this->query.addBindValue(name.toString().toLower());
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return -1;
    }
    if(this->query.next()){
        id = this->query.value("id").toInt();
        this->cacheEventId.insert(name.toString().toLower(),id);
        return id;
    }
    return 0;
}

int Database::dictExist(QVariant name)
{
    int id = -1;
    this->query.prepare("Select id FROM Dictionary WHERE Dictionary.name=?");
    this->query.addBindValue(name.toString().toLower());
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return -1;
    }
    if(this->query.next()){
        id = this->query.value("id").toInt();
        return id;
    }
    return 0;
}

int Database::dictEntryExist(QVariant name, QString code)
{
    int id = -1;
    int idDict = this->dictExist(name);
    this->query.prepare("Select id FROM EntryDict as E WHERE E.dictionary=? AND E.code=?");
    this->query.addBindValue(idDict);
    this->query.addBindValue(code);
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return -1;
    }
    if(this->query.next()){
        id = this->query.value("id").toInt();
        return id;
    }
    return 0;
}

int Database::insertUser(Users u)
{
    QVariant name = u.getName().toString().toLower();
    if(!this->userExist(name)){
        this->query.prepare("INSERT INTO Users (name) VALUES (:name);");
        this->query.bindValue(":name",name);
        if(!this->query.exec()){
            this->showError(this->query.lastError());
            return -1;
        }
        return this->query.lastInsertId().toInt();
    }
    this->showError(QMessageBox::tr("Esse usuário já existe!"));
    return 0;
}

int Database::insertSpecie(Species s)
{
    QVariant name = s.getName().toString().toLower();
    if(!this->specieExist(name)){
        this->query.prepare("INSERT INTO Species (name) VALUES (:name);");
        this->query.bindValue(":name",name);
        if(!this->query.exec()){
            this->showError(this->query.lastError());
            return -1;
        }
        return this->query.lastInsertId().toInt();
    }
    this->showError(QMessageBox::tr("Essa espécie já existe!"));
    return 0;
}

int Database::insertSubject(Subjects s)
{
    QVariant name = s.getName().toString().toLower();
    if(!this->subjectExist(name)){
        this->query.prepare("INSERT INTO Subjects (name) VALUES (:name);");
        this->query.bindValue(":name",name);
        if(!this->query.exec()){
            this->showError(this->query.lastError());
            return -1;
        }
        return this->query.lastInsertId().toInt();
    }
    this->showError(QMessageBox::tr("Essa espécie já existe!"));
    return 0;
}

int Database::insertState(States s)
{
    QVariant name = s.getDescription().toLower();
    if(!this->stateExist(name)){
        this->query.prepare("INSERT INTO States (name) VALUES (:name);");
        this->query.bindValue(":name",name);
        if(!this->query.exec()){
            this->showError(this->query.lastError());
            return -1;
        }
        return this->query.lastInsertId().toInt();
    }
    return 0;
}

int Database::insertEvent(Events e)
{
    QVariant name = e.getDescription().toLower();
    if(!this->eventExist(name)){
        this->query.prepare("INSERT INTO Events (name) VALUES (:name);");
        this->query.bindValue(":name",name);
        if(!this->query.exec()){
            this->showError(this->query.lastError());
            return -1;
        }
        return this->query.lastInsertId().toInt();
    }
    return 0;
}

int Database::insertSession(QVariant decoder, QVariant dateDecoding,
                                     QVariant observer, QVariant subject, QVariant specie,
                                     QVariant dateSession, QVariant description)
{

    this->query.prepare("INSERT INTO Sessions (datesession, datedecoding, decoder, observer, description, subject, specie) "
                        "VALUES (:datesession, :datedecoding, :decoder, :observer, :description, :subject, :specie);");
    this->query.bindValue(":datesession",dateSession.toDateTime().toString("yyyy-MM-dd HH:mm:ss"));
    this->query.bindValue(":datedecoding",dateDecoding.toDateTime().toString("yyyy-MM-dd HH:mm:ss"));
    this->query.bindValue(":decoder",decoder);
    this->query.bindValue(":observer",observer);
    this->query.bindValue(":description",description);
    this->query.bindValue(":subject",subject);
    this->query.bindValue(":specie",specie);
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return -1;
    }
    return this->query.lastInsertId().toInt();
}

int Database::insertAction(QVariant timer, QVariant session, QVariant state, QVariant event)
{

    this->query.prepare("INSERT INTO Actions (time, session, state, event) "
                        "VALUES (:time, :session, :state, :event);");
    this->query.bindValue(":time",timer);
    this->query.bindValue(":session",session);
    this->query.bindValue(":state",state);
    this->query.bindValue(":event",event);
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return -1;
    }
    return this->query.lastInsertId().toUInt();
}

int Database::editUsers(Users u)
{
    QVariant name = u.getName().toString().toLower();
    if(this->userExist(name) > 0){
        this->showError(QMessageBox::tr("Esse usuário já existe"));
        return 0;
    }
    if(this->userExist(name) >= 0){
        this->query.prepare("UPDATE Users SET name=? WHERE Users.id=?;");
        this->query.addBindValue(name);
        this->query.addBindValue(u.getId());
        if(!this->query.exec()){
            this->showError(this->query.lastError());
            return -1;
        }
        return 1;
    }
    QMessageBox::information(0, QMessageBox::tr("Erro"),QMessageBox::tr("Usuário não encontrado!"));
    return 0;
}

int Database::editSpecies(Species s)
{
    QVariant name = s.getName().toString().toLower();
    if(this->specieExist(name) > 0){
        this->showError(QMessageBox::tr("Esta espécie já existe"));
        return 0;
    }
    if(this->specieExist(name) <= 0){
        this->query.prepare("UPDATE Species SET name=? WHERE Species.id=?;");
        this->query.addBindValue(name);
        this->query.addBindValue(s.getId());
        if(!this->query.exec()){
            this->showError(this->query.lastError());
            return -1;
        }
        return 1;
    }
    QMessageBox::information(0, QMessageBox::tr("Erro"),QMessageBox::tr("Espécie não encontrada!"));
    return 0;
}

int Database::editSubjects(Subjects s)
{
    QVariant name = s.getName().toString().toLower();
    if(this->subjectExist(name) > 0){
        this->showError(QMessageBox::tr("Esta espécie já existe"));
        return 0;
    }
    if(this->subjectExist(name) <= 0){
        this->query.prepare("UPDATE Subjects SET name=? WHERE Subjects.id=?;");
        this->query.addBindValue(name);
        this->query.addBindValue(s.getId());
        if(!this->query.exec()){
            this->showError(this->query.lastError());
            return -1;
        }
        return 1;
    }
    QMessageBox::information(0, QMessageBox::tr("Erro"),QMessageBox::tr("Espécie não encontrada!"));
    return 0;
}

Users Database::getUsers(unsigned int id)
{
    Users u;
    u.setId(-1);
    this->query.prepare("Select * FROM Users WHERE Users.id=? LIMIT 1;");
    this->query.addBindValue(QVariant(id));
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return u;
    }
    u = this->fillUser();
    return u;
}

Users Database::getUsers(QString name)
{
    Users u;
    u.setId(-1);
    this->query.prepare("Select id, name FROM Users WHERE Users.name=? LIMIT 1;");
    this->query.addBindValue(QVariant(name));
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return u;
    }
    u = this->fillUser();
    return u;
}

QList<Users> Database::getAllUsers()
{
    QList<Users> users;
    this->query.prepare("Select * FROM Users ORDER BY Users.name;");
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return users;
    }
    while(this->query.next()){
        Users u;
        u.setId(this->query.value(0));
        u.setName(this->query.value(1));
        users.push_back(u);
    }
    return users;
}

bool Database::removeUser(unsigned int id)
{
    this->query.prepare("DELETE FROM Users WHERE Users.id=?");
    this->query.addBindValue(QVariant(id));
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return false;
    }
    return true;
}

Species Database::getSpecies(unsigned int id)
{
    Species s;
    s.setId(-1);
    this->query.prepare("Select * FROM Species WHERE Species.id=? LIMIT 1;");
    this->query.addBindValue(QVariant(id));
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return s;
    }
    s = this->fillSpecie();
    return s;
}

Species Database::getSpecies(QVariant name)
{
    Species s;
    s.setId(-1);
    this->query.prepare("Select id, name FROM Species WHERE Species.name=? LIMIT 1;");
    this->query.addBindValue(name);
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return s;
    }
    s = this->fillSpecie();
    return s;
}

QList<Species> Database::getAllSpecies()
{
    QList<Species> species;
    this->query.prepare("Select * FROM Species ORDER BY Species.name;");
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return species;
    }
    while(this->query.next()){
        Species s;
        s.setId(this->query.value(0));
        s.setName(this->query.value(1));
        species.push_back(s);
    }
    return species;
}

bool Database::removeSpecie(unsigned int id)
{
    this->query.prepare("DELETE FROM Species WHERE Species.id=?");
    this->query.addBindValue(QVariant(id));
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return false;
    }
    return true;
}

Subjects Database::getSubjects(unsigned int id)
{
    Subjects s;
    s.setId(-1);
    this->query.prepare("Select * FROM Subjects WHERE Subjects.id=? LIMIT 1;");
    this->query.addBindValue(QVariant(id));
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return s;
    }
    s = this->fillSubject();
    return s;
}

Subjects Database::getSubjects(QVariant name)
{
    Subjects s;
    s.setId(-1);
    this->query.prepare("Select id, name FROM Subjects WHERE Subjects.name=? LIMIT 1;");
    this->query.addBindValue(name);
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return s;
    }
    s = this->fillSubject();
    return s;
}

QList<Subjects> Database::getAllSubjects()
{
    QList<Subjects> subjects;
    this->query.prepare("Select * FROM Subjects ORDER BY Subjects.name;");
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return subjects;
    }
    while(this->query.next()){
        Subjects s;
        s.setId(this->query.value(0));
        s.setName(this->query.value(1));
        subjects.push_back(s);
    }
    return subjects;
}

bool Database::removeSubject(unsigned int id)
{
    this->query.prepare("DELETE FROM Subjects WHERE Subjects.id=?");
    this->query.addBindValue(QVariant(id));
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return false;
    }
    return true;
}

QList<Sessions> Database::getAllSessions()
{
    QList<Sessions> sessions;
    this->query.prepare("Select S.id, S.datesession, s.datedecoding, Spc.name as specie, Sub.name as subject, "
                        "O.name as obs, D.name as dec, S.description FROM Sessions as S "
                        "JOIN Subjects as Sub ON S.subject = Sub.id "
                        "JOIN Species as Spc ON S.specie = Spc.id "
                        "JOIN Users as O ON S.observer = O.id "
                        "JOIN Users as D ON S.decoder = D.id "
                        " ORDER BY S.datesession;");
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return sessions;
    }
    while(this->query.next()){
        Sessions s;
        s.setId(this->query.value(0));
        s.setDateSession(QDateTime::fromString(this->query.value(1).toString(),"yyyy-MM-dd HH:mm:ss"));
        s.setDateDecoding(QDateTime::fromString(this->query.value(2).toString(),"yyyy-MM-dd HH:mm:ss"));
        s.setSpecies(this->query.value(3));
        s.setSubject(this->query.value(4));
        s.setObserver(this->query.value(5));
        s.setDecoder(this->query.value(6));
        s.setDescription(this->query.value(7));
        sessions.push_back(s);
    }
    return sessions;
}

Sessions Database::getSession(unsigned int id)
{
    Sessions s;
    this->query.prepare("Select S.id, S.datesession, s.datedecoding, Spc.name as specie, Sub.name as subject, "
                        "O.name as obs, D.name as dec, S.description FROM Sessions as S "
                        "JOIN Subjects as Sub ON S.subject = Sub.id "
                        "JOIN Species as Spc ON S.specie = Spc.id "
                        "JOIN Users as O ON S.observer = O.id "
                        "JOIN Users as D ON S.decoder = D.id "
                        "WHERE S.id = :id ORDER BY S.datesession;");
    this->query.bindValue(":id",id);
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return s;
    }
    this->query.next();
    s.setId(this->query.value(0));
    s.setDateSession(QDateTime::fromString(this->query.value(1).toString(),"yyyy-MM-dd HH:mm:ss"));
    s.setDateDecoding(QDateTime::fromString(this->query.value(2).toString(),"yyyy-MM-dd HH:mm:ss"));
    s.setSpecies(this->query.value(3));
    s.setSubject(this->query.value(4));
    s.setObserver(this->query.value(5));
    s.setDecoder(this->query.value(6));
    s.setDescription(this->query.value(7));
    return s;
}

QList<Actions> Database::getSequence(unsigned int idSession)
{
    QList<Actions> sequence;
    this->query.prepare("SELECT A.time, E.name, S.name, A.id FROM Actions as A "
                        "JOIN States as S ON S.id = A.state JOIN Events as E ON E.id = A.event "
                        "WHERE A.session = :idSession ORDER BY A.time;");
    this->query.bindValue(":idSession",idSession);
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return sequence;
    }
    while(this->query.next()){
        Actions a(this->query.value(0).toDouble(),
                  this->query.value(1).toString(),
                  this->query.value(2).toString(),
                  this->query.value(3).toUInt());
        sequence.push_back(a);
    }
    return sequence;
}

int Database::insertDict(Dictionary dict)
{
    QVariant name = dict.getName().toLower();
    if(!this->dictExist(name)){
        this->query.prepare("INSERT INTO Dictionary (name) VALUES (:name);");
        this->query.bindValue(":name",name);
        if(!this->query.exec()){
            this->showError(this->query.lastError());
            return -1;
        }
        return this->query.lastInsertId().toInt();
    }
    return 0;
}

int Database::insertDictEntry(QString dict, QString code, QString word)
{
    int id = this->dictExist(dict.toLower());
    this->query.prepare("INSERT INTO EntryDict (dictionary, code, word) VALUES (:dict, :code, :word);");
    this->query.bindValue(":dict",id);
    this->query.bindValue(":code",code);
    this->query.bindValue(":word",word.toLower());
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return -1;
    }
    return this->query.lastInsertId().toInt();
}

int Database::editDictEntry(QString dict, QString lastCode, QString code, QString word)
{
    int id = this->dictEntryExist(dict,lastCode);
    this->query.prepare("UPDATE EntryDict SET code=?, word=? WHERE id=?;");
    this->query.addBindValue(code);
    this->query.addBindValue(word.toLower());
    this->query.addBindValue(id);
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return -1;
    }
    return 0;
}

int Database::editDict(QString oldName, QString newName)
{
    int id = this->dictExist(oldName.toLower());
    this->query.prepare("UPDATE Dictionary SET name=? WHERE id=?;");
    this->query.addBindValue(newName);
    this->query.addBindValue(id);
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return -1;
    }
    return 1;
}

QList<QString> Database::dictNames()
{
    QList<QString> names;
    this->query.prepare("Select Dictionary.name FROM Dictionary ORDER BY Dictionary.name;");
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return names;
    }
    while(this->query.next()){
        names.push_back(this->query.value(0).toString());
    }
    return names;
}

Dictionary Database::getDictionary(QString name)
{
    Dictionary dict;
    int id = this->dictExist(name.toLower());
    this->query.prepare("Select E.code, E.word FROM EntryDict as E WHERE E.dictionary=? ORDER BY E.word;");
    this->query.addBindValue(id);
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return dict;
    }
    while(this->query.next()){
        dict.insertEntry(this->query.value(0).toString(),this->query.value(1).toString());
    }
    return dict;
}

bool Database::removeDict(QString name)
{
    int id = this->dictExist(name.toLower());
    this->query.prepare("DELETE FROM Dictionary WHERE Dictionary.id=?");
    this->query.addBindValue(QVariant(id));
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return false;
    }
    return true;
}

bool Database::removeDictEntry(QString name, QString code)
{
    int id = this->dictExist(name.toLower());
    this->query.prepare("DELETE FROM EntryDict WHERE EntryDict.dictionary=? AND EntryDict.code=?");
    this->query.addBindValue(QVariant(id));
    this->query.addBindValue(QVariant(code));
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return false;
    }
    return true;
}

int Database::saveSession(Sessions session)
{
    int decoderId = this->userExist(session.getDecoder());
    if(decoderId == 0){
        decoderId = this->insertUser(Users(session.getDecoder()));
        if(decoderId <= 0) return -1;
        this->cacheUserId.insert(session.getDecoder().toString(),decoderId);
    }
    int observerId = this->userExist(session.getObserver());
    if(observerId == 0){
        observerId = this->insertUser(Users(session.getObserver()));
        if(observerId <= 0) return -2;
        this->cacheUserId.insert(session.getObserver().toString(),observerId);
    }
    int specieId = session.getSpecies().toInt();
    int subjectId = session.getSubject().toInt();

    int sessionId = this->insertSession(decoderId, session.getDateDecoding(),
                                        observerId, subjectId, specieId,
                                        session.getDateSession(), session.getDescription());
    if(sessionId <= 0) return -3;
    QList<Actions> sequence = session.getActions();
    for(int s=0; s < sequence.size(); s++){
        Actions action = sequence.at(s);
        int stateId = this->stateExist(action.getStateDescription());
        if(stateId == 0){
            stateId = this->insertState(States(action.getStateDescription()));
            if(stateId <= 0) return -4;
            this->cacheStateId.insert(action.getStateDescription(),stateId);
        }
        int eventId = this->eventExist(action.getEventDescription());
        if(eventId == 0){
            eventId = this->insertEvent(Events(action.getEventDescription()));
            if(eventId <= 0) return -5;
            this->cacheEventId.insert(action.getEventDescription(),eventId);
        }
        if(this->insertAction(action.getTimeAction(), sessionId, stateId, eventId) <= 0) return -6;
    }
//    qDebug() << this->query.lastQuery();
//    qDebug() << this->query.lastError();
//    qDebug() << sessionId;
    return sessionId;
}

int Database::editSession(Sessions session)
{
    int observerId = this->userExist(session.getObserver());
    if(observerId == 0){
        observerId = this->insertUser(Users(session.getObserver()));
        if(observerId <= 0) return -2;
        this->cacheUserId.insert(session.getObserver().toString(),observerId);
    }
    QVariant specieId = session.getSpecies();
    if(session.getSpecies().type() == QVariant::String)
        specieId = this->getSpecies(session.getSpecies()).getId();
    if(specieId <= 0) return -1;
    QVariant subjectId = session.getSubject();
    if(session.getSubject().type() == QVariant::String)
        subjectId = this->getSubjects(session.getSubject()).getId();
    if(subjectId <= 0) return -1;
    this->query.prepare("UPDATE Sessions SET observer = :observer, subject = :subject, specie = :specie, description = :description "
                        "WHERE id = :id;");
    this->query.bindValue(":observer",observerId);
    this->query.bindValue(":subject",subjectId);
    this->query.bindValue(":specie",specieId);
    this->query.bindValue(":description",session.getDescription());
    this->query.bindValue(":id",session.getId());
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        return -1;
    }
    return 0;
}

bool Database::removeSession(QVariant id)
{
    this->query.exec("BEGIN");
    this->query.prepare("DELETE FROM Actions WHERE session=?");
    this->query.addBindValue(id);
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        this->query.exec("ROLLBACK");
        return false;
    }
    this->query.prepare("DELETE FROM Sessions WHERE id=?");
    this->query.addBindValue(id);
    if(!this->query.exec()){
        this->showError(this->query.lastError());
        this->query.exec("ROLLBACK");
        return false;
    }
    this->query.exec("END");
    return true;
}
