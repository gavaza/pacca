#ifndef STATE_H
#define STATE_H
#include <QString>
#include <QList>
#include "events.h"

/*!
 * \brief Class to represent a State displayed by the observed.
 */

class States
{
public:
    States();
    States(QString description, unsigned int id=0);
    void setDescription(QString description);
    QString getDescription();
    void setId(unsigned int id);
    unsigned int getId();
private:
    unsigned int id;
    /*!
     * \brief Name or description of the state.
     */
    QString description;
};

#endif // STATE_H
