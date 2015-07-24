#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include <QStandardPaths>
#include <QtSql/QSqlDatabase>
#include <QMessageBox>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

#include <QDebug>


//!  \class Class responsible by to create and connect the database.
/*!
 *   \brief In this version, this software uses a sqlite3 database.
*/
class Connections
{
private:
    /*!
     * \brief db Attribute responsible by to manage the database.
     */
    QSqlDatabase db;
public:
    /*!
     * \brief Connections
     * \param driver
     * \param database
     */
    Connections(QString driver, QString database);
    /*!
     * \brief openConnection
     * \return
     */
    bool openConnection();
    /*!
     * \brief closeConnection
     */
    void closeConnection();
    /*!
     * \brief makeDatabaseTables
     */
    bool makeDatabaseTables();
};

#endif // CONNECTIONS_H
