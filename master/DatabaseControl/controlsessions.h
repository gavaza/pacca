#ifndef CONTROLSESSIONS_H
#define CONTROLSESSIONS_H

#include <QWidget>
#include <QSettings>
#include <QMessageBox>

#include "database.h"
#include "sessions.h"
#include "dialogchoosespecie.h"

namespace Ui {
class ControlSessions;
}

class ControlSessions : public QWidget
{
    Q_OBJECT

public:
    explicit ControlSessions(QWidget *parent = 0);
    ~ControlSessions();

private:
    Ui::ControlSessions *ui;
    QString origText;

private slots:
    void save(int r, int c);
    void load();
    void saveOrigText(int r, int c);
    void remove();
};

#endif // CONTROLSESSIONS_H
