#ifndef INPUTTABLE_H
#define INPUTTABLE_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QGridLayout>
#include <QHeaderView>
#include <QApplication>
#include <QKeyEvent>
#include <QClipboard>

class InputTable : public QWidget {
    Q_OBJECT
public:
    explicit InputTable(QWidget *parent = nullptr);
    virtual void initTable();
    QTableWidget* table;
    virtual ~InputTable();
private:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void copy();
    virtual void paste();
    QGridLayout* gridLayout;

signals:

public slots:
};

#endif // INPUTTABLE_H
