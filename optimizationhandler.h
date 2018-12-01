#ifndef OPTIMIZATIONHANDLER_H
#define OPTIMIZATIONHANDLER_H

#include <QObject>
#include "inputtable.h"

class OptimizationHandler : public QObject
{
    Q_OBJECT
public:
    explicit OptimizationHandler(QList<QTableWidget*>* list, QObject *parent = nullptr);
    QList<QTableWidget*>* list;
    ~OptimizationHandler();
private:
    void calcDelTable(QTableWidget*, QTableWidget*,
                      QTableWidget*, double);
    void copyToBo(QTableWidget*, QTableWidget*);
    double getWaySum(QTableWidget*, QTableWidget*, int, int);
    void calcDlTable(QTableWidget*, QTableWidget*,
                     QTableWidget*);
    void calcOTable(QTableWidget*, QTableWidget*);
signals:

public slots:
    void mkOptimization(int, int);
};

#endif // OPTIMIZATIONHANDLER_H
