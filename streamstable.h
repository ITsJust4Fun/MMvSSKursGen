#ifndef STREAMSTABLE_H
#define STREAMSTABLE_H
#include "intensitytable.h"


class StreamsTable : public IntensityTable {
    Q_OBJECT
public:
    StreamsTable();
    static double fErlang(double, int);
    virtual ~StreamsTable();

signals:

public slots:
    virtual void changeData(int, int);
};

#endif // STREAMSTABLE_H
