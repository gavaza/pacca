#ifndef SPECIES_H
#define SPECIES_H

#include <QVariant>
#include <QVariant>

/*!
 * \brief Species class
 * A class to represent each specie, currently contains only name information.
 */
class Species
{
public:
    Species();
    Species(QVariant n, QVariant id=0);
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

#endif // SPECIES_H
