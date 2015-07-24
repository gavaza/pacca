#ifndef USERS_H
#define USERS_H

#include <QVariant>
#include <QVariant>

/*!
 * \brief Users class
 * A class to represent each user, currently contains only name information.
 */
class Users
{
public:
    Users();
    Users(QVariant n, QVariant id=0);
    void setId(QVariant id);
    QVariant getId();
    void setName(QVariant name);
    void setName(QString name);
    QVariant getName();
private:
    QVariant id;
    /*!
     * \brief Name of the user.
     */
    QVariant name;
};

#endif // USERS_H
