#ifndef ACTIONSEQ_H
#define ACTIONSEQ_H

#include <QTime>
#include <QString>

#include "states.h"
#include "events.h"

/*!
 * \brief Class to represent an action of a specific sequence/session.
 * Each element of a behavioral sequence is classified as an event.
 * This Event can be associated with a State, if not, a common state is automatically assigned to it.
 * Each event have a time associated with the vídeo file.
 * An event can have an associated state.
 */
class Actions
{
public:
    Actions();
    Actions(double t, Events event, States state, unsigned int id=0);
    Actions(double t, QString event, QString state, unsigned int id=0);
    void setId(unsigned int id);
    unsigned int getId();
    void setTimeAction(double time);
    double getTimeAction();
    void setState(States state);
    States getState();
    QString getStateDescription();
    void setEvent(Events event);
    Events getEvent();
    QString getEventDescription();

private:
    unsigned int id;
    /*!
     * \brief The video's time which an action occurred.
     */
    double timeAction;
    /*!
     * \brief The state's name of the respective action.
     */
    States state;
    /*!
     * \brief The event's name of the respective action.
     */
    Events event;

};

#endif // ACTIONSEQ_H
