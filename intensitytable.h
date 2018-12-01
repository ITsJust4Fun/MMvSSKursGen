#ifndef INTENSITYTABLE_H
#define INTENSITYTABLE_H
#include "inputtable.h"


class IntensityTable : public InputTable {
    Q_OBJECT
public:
    IntensityTable() {}
    IntensityTable(QTableWidget*, QTableWidget*);
    virtual void initTable();
    virtual ~IntensityTable();
    double ySum(int i, int j);
    QTableWidget* inputTable = nullptr;
    QTableWidget* inputNumTable = nullptr;
private:
public slots:
    virtual void changeData(int, int);
};

#endif // INTENSITYTABLE_H
