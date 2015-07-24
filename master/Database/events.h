#ifndef EVENTS_H
#define EVENTS_H

#include <QString>

/*!
 * \brief Class to represent a Event displayed by the observed.
 */

class Events
{
public:
    Events();
    Events(QString description, unsigned int id=0);
    void setDescription(QString description);
    QString getDescription();
    void setId(unsigned int id);
    unsigned int getId();
private:
    unsigned int id;
    /*!
     * \brief Name or description of the event.
     */
    QString description;
};

#endif // EVENTS_H
