#ifndef SHORTESTTABLE_H
#define SHORTESTTABLE_H
#include "intensitytable.h"
#include <QList>


class ShortestTable : public IntensityTable {
    Q_OBJECT
public:
    ShortestTable(QTableWidget*);
    QTableWidget* nextTable;
    virtual ~ShortestTable();

signals:

public slots:
    virtual void changeData(int, int);
};

#endif // SHORTESTTABLE_H
