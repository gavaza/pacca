#ifndef CONTROLSPECIES_H
#define CONTROLSPECIES_H

#include <QWidget>
#include <QList>
#include <QFileDialog>
#include <QKeyEvent>

#include "database.h"
#include "species.h"

namespace Ui {
class ControlSpecies;
}
/*!
 * \brief A class for control (view/insert/edit/remove) species.
 */
class ControlSpecies : public QWidget
{
    Q_OBJECT
    
public:
    explicit ControlSpecies(QWidget *parent = 0);
    ~ControlSpecies();
    
private:
    Ui::ControlSpecies *ui;
    QString origText;

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    /*!
     * \brief Checks if the species exist.
     */
    bool verify();
    /*!
     * \brief Insert a new specie.
     */
    void create();
    /*!
     * \brief Save a specie that was edited.
     */
    void save(int row, int col);
    /*!
     * \brief Save the name of a specie before edition.
     */
    void saveOrigText(int row, int col);
    /*!
     * \brief Remove a specie.
     */
    void remove();
    /*!
     * \brief Import from a text file
     */
    void importFromFile();
    /*!
     * \brief Refresh species list
     */
    void refreshList();
};

#endif // CONTROLSPECIES_H
