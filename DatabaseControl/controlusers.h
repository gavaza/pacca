#ifndef CONTROLUSERS_H
#define CONTROLUSERS_H

#include <QWidget>
#include <QList>

#include "database.h"
#include "users.h"

namespace Ui {
class ControlUsers;
}
/*!
 * \brief A class for control (view/insert/edit/remove) users.
 */
class ControlUsers : public QWidget
{
    Q_OBJECT
    
public:
    explicit ControlUsers(QWidget *parent = 0);
    ~ControlUsers();
    
private:
    Ui::ControlUsers *ui;
    void refreshList();
    QString origText;

private slots:
    /*!
     * \brief Checks if the users exist.
     */
    bool verify();
    /*!
     * \brief Insert a new user.
     */
    void create();
    /*!
     * \brief Save a user that was edited.
     */
    void save(int row, int col);
    /*!
     * \brief Save the name of a user before edition.
     */
    void saveOrigText(int row, int col);
    /*!
     * \brief Remove a user.
     */
    void remove();
};

#endif // CONTROLUSERS_H
