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
    void addToWay(int i, int j);
    double ytotal;
    QTableWidget* inputTable = nullptr;
    QTableWidget* inputNumTable = nullptr;
private:
public slots:
    virtual void changeData(int, int);
};

#endif // INTENSITYTABLE_H
