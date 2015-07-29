#ifndef CONTROLSUBJECTS_H
#define CONTROLSUBJECTS_H

#include <QWidget>
#include <QList>
#include <QFileDialog>

#include "database.h"
#include "subject.h"

namespace Ui {
class ControlSubjects;
}
/*!
 * \brief A class for control (view/insert/edit/remove) subjects.
 */
class ControlSubjects : public QWidget
{
    Q_OBJECT
    
public:
    explicit ControlSubjects(QWidget *parent = 0);
    ~ControlSubjects();
    
private:
    Ui::ControlSubjects *ui;
    void refreshList();
    QString origText;

private slots:
    /*!
     * \brief Checks if the subjects exist.
     */
    bool verify();
    /*!
     * \brief Insert a new subject.
     */
    void create();
    /*!
     * \brief Save a subject that was edited.
     */
    void save(int row, int col);
    /*!
     * \brief Save the name of a subject before edition.
     */
    void saveOrigText(int row, int col);
    /*!
     * \brief Remove a subject.
     */
    void remove();
    /*!
     * \brief Import from a text file
     */
    void importFromFile();
};

#endif // CONTROLSUBJECTS_H
