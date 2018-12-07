#include "bandwidthtable.h"

BandwidthTable::BandwidthTable() {

}

void BandwidthTable::changeData(int x, int y) {
    QTableWidget* intensityDTTable = dynamic_cast<QTableWidget*>(QObject::sender());
    if(intensityDTTable->item(x, y)->text() == "") {
        return;
    }
    double aij = intensityDTTable->item(x, y)->text().toDouble();
    double L = 200 * 8;
    double T0 = 0.1;
    table->item(x, y)->setText(QString::number(aij + L/T0, 'g', 15));
}

BandwidthTable::~BandwidthTable() {

}
