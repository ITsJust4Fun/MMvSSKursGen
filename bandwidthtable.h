#ifndef BANDWIDTHTABLE_H
#define BANDWIDTHTABLE_H
#include "intensitytable.h"

class BandwidthTable : public IntensityTable {
    Q_OBJECT
public:
    BandwidthTable();
    virtual ~BandwidthTable();

signals:

public slots:
    virtual void changeData(int, int);

};

#endif // BANDWIDTHTABLE_H
