#ifndef DATABASE_H
#define DATABASE_H

#include <QVariant>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QSqlError>
#include <QCryptographicHash>
#include <QList>
#include <QHash>

#include <QDebug>

#include "users.h"
#include "species.h"
#include "sessions.h"
#include "action.h"
#include "states.h"
#include "events.h"
#include "dictionary.h"
#include "subject.h"

/*!
 * \brief Interface wiht the sqlite database
 */
class Database
{
public:
    Database();
    int insertUser(Users u);
    int editUsers(Users u);
    Users getUsers(unsigned int id);
    Users getUsers(QString name);
    QList<Users> getAllUsers();
    bool removeUser(unsigned int id);
    int insertSpecie(Species s);
    int editSpecies(Species s);
    Species getSpecies(unsigned int id);
    Species getSpecies(QVariant name);
    QList<Species> getAllSpecies();
    int insertSubject(Subjects s);
    int editSubjects(Subjects s);
    Subjects getSubjects(unsigned int id);
    Subjects getSubjects(QVariant name);
    QList<Subjects> getAllSubjects();
    bool removeSubject(unsigned int id);
    bool removeSpecie(unsigned int id);
    int insertEvent(Events e);
    int insertState(States s);
    int saveSession(Sessions session);
    int editSession(Sessions session);
    bool removeSession(QVariant id);
    int eventExist(QVariant name);
    QList<Sessions> getAllSessions();
    Sessions getSession(unsigned int id);
    QList<Actions> getSequence(unsigned int idSession, bool reserved=false);
    int insertDict(Dictionary dict);
    int insertDictEntry(QString dict, QString code, QString word);
    int editDictEntry(QString dict, QString lastCode, QString code, QString word);
    QList<QString> dictNames();
    bool removeDict(QString name);
    bool removeDictEntry(QString name, QString code);
    Dictionary getDictionary(QString name);
    int editDict(QString oldName, QString newName);
    int subjectExist(QVariant name);

private:
    QSqlQuery query;
    QSqlRecord record;
    QHash<QString,unsigned int> cacheUserId;
    QHash<QString,unsigned int> cacheStateId;
    QHash<QString,unsigned int> cacheEventId;
    void showError(const QSqlError &err);

    Sessions fillSession();
    Users fillUser();
    Species fillSpecie();
    Subjects fillSubject();
    Events fillEvent();
    States fillState();

    int userExist(QVariant name);
    int specieExist(QVariant name);
    int stateExist(QVariant name);
    int dictExist(QVariant name);
    int dictEntryExist(QVariant name, QString code);

    int insertSession(QVariant decoder, QVariant dateDecoding, QVariant observer, QVariant subject, QVariant specie, QVariant dateSession, QVariant description);
    int insertAction(QVariant timer, QVariant session, QVariant state, QVariant event);
    int insertSubject(QVariant name);
};

#endif // DATABASE_H
