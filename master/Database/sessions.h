#ifndef SESSIONS_H
#define SESSIONS_H

#include <QVariant>
#include <QList>
#include "action.h"

/*!
 * \brief A class to represent a observation session.
 * This class is resposible for store all information about a observation session and a decoding session.
 */
class Sessions
{
public:
    Sessions();
    Sessions(QVariant d, QVariant o, QVariant s, QVariant dateD, QVariant dateS, QVariant id=0);
    void setId(QVariant id);
    QVariant getId();
    void setDecoder(QVariant decoder);
    QVariant getDecoder();
    void setObserver(QVariant observer);
    QVariant getObserver();
    void setSubject(QVariant subject);
    QVariant getSubject();
    void setDateDecoding(QVariant date);
    QVariant getDateDecoding();
    void setDescription(QVariant desc);
    QVariant getDescription();
    void setDateSession(QVariant date);
    QVariant getDateSession();
    void setActions(QList<Actions> action);
    QList<Actions> getActions();
    void addAction(Actions action);
    void setSpecies(QVariant specie);
    QVariant getSpecies();

private:
    QVariant id;
    /*!
     * \brief Identifier of the user that made the decoding.
     */
    QVariant decoder;
    /*!
     * \brief Identifier of the user that made the observation.
     */
    QVariant observer;
    /*!
     * \brief Some information about the session to help your identification.
     */
    QVariant description;
    /*!
     * \brief Some information about the session to help your identification.
     */
    QVariant subject;
    /*!
     * \brief Date an time that the decoding was made.
     */
    QVariant dateDecoding;
    /*!
     * \brief Date and time that the observation session occurred.
     */
    QVariant dateSession;
    /*!
     * \brief List of actions in session.
     */
    QList<Actions> actions;
    QVariant specie;
};

#endif // SESSIONS_H
