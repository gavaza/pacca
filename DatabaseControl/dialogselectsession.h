#ifndef DIALOGSELECTSESSION_H
#define DIALOGSELECTSESSION_H

#include <QDialog>
#include <QList>
#include <QTableWidgetItem>
#include <QPushButton>

#include "database.h"
#include "sessions.h"

namespace Ui {
class DialogSelectSession;
}

class DialogSelectSession : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogSelectSession(QWidget *parent = 0);
    ~DialogSelectSession();
    QList<QTableWidgetItem *> getSelectedItens();
    
private:
    Ui::DialogSelectSession *ui;
    void load();
};

#endif // DIALOGSELECTSESSION_H
