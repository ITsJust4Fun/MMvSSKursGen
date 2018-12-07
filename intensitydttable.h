#ifndef INTENSITYDTTABLE_H
#define INTENSITYDTTABLE_H
#include "intensitytable.h"


class IntensityDTTable : public IntensityTable {
    Q_OBJECT
public:
    IntensityDTTable();
    virtual ~IntensityDTTable();

signals:

public slots:
    virtual void changeData(int, int);
};

#endif // INTENSITYDTTABLE_H
