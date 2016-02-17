#ifndef CONTROLUSERS_H
#define CONTROLUSERS_H

#include <QWidget>
#include <QList>
#include <QKeyEvent>

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
    QString origText;

protected:
    void keyPressEvent(QKeyEvent *event);

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
    /*!
     * \brief Refresh users list
     */
    void refreshList();

signals:
    void users_updated();

};

#endif // CONTROLUSERS_H
