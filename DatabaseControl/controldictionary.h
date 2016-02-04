#ifndef CONTROLDICTIONARY_H
#define CONTROLDICTIONARY_H

#include <QWidget>
#include <QMap>
#include <QMapIterator>
#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>

#include "database.h"
#include "dictionary.h"

namespace Ui {
class ControlDictionary;
}

class ControlDictionary : public QWidget
{
    Q_OBJECT

public:
    explicit ControlDictionary(QWidget *parent = 0);
    ~ControlDictionary();

private:
    Ui::ControlDictionary *ui;
    void createConnexions();
    QString origText;

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void loadDict();
    void saveDict();
    void saveOrigTextDict(int r, int c);
    void editDict(int r, int c);
    void removeDict();
    void loadEntries();
    void saveEntry();
    void saveOrigTextEntry(int r, int c);
    void editEntry(int r, int c);
    void removeEntry();

    bool existEntry(QString code, QString word);
    bool existEntry(QString text, unsigned int col);
    bool existDict(QString name);
};

#endif // CONTROLDICTIONARY_H
