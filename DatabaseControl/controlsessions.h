#ifndef CONTROLSESSIONS_H
#define CONTROLSESSIONS_H

#include <QWidget>
#include <QSettings>
#include <QMessageBox>
#include <QKeyEvent>

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

protected:
    void keyPressEvent(QKeyEvent *event);

public slots:
    void load();

private slots:
    void save(int r, int c);
    void saveOrigText(int r, int c);
    void remove();

signals:
    void sessions_updated();
};

#endif // CONTROLSESSIONS_H
