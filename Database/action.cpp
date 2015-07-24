#include "action.h"

Actions::Actions()
{

}

Actions::Actions(double t, Events event, States state, unsigned int id)
{
    this->id = id;
    this->timeAction = t;
    this->state = state;
    this->event = event;
}

Actions::Actions(double t, QString event, QString state, unsigned int id)
{
    this->id = id;
    this->timeAction = t;
    this->state.setDescription(state);
    this->event.setDescription(event);
}

void Actions::setId(unsigned int id)
{
    this->id = id;
}

unsigned int Actions::getId()
{
    return this->id;
}

void Actions::setTimeAction(double time)
{
    this->timeAction = time;
}

double Actions::getTimeAction(){
    return this->timeAction;
}

void Actions::setState(States state)
{
    this->state = state;
}

States Actions::getState()
{
    return this->state;
}

QString Actions::getStateDescription()
{
    return this->state.getDescription();
}

void Actions::setEvent(Events event)
{
    this->event = event;
}

Events Actions::getEvent()
{
    return this->event;
}

QString Actions::getEventDescription()
{
    return this->event.getDescription();
}
