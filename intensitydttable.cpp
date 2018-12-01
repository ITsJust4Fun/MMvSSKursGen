#include "intensitydttable.h"

IntensityDTTable::IntensityDTTable() {

}

void IntensityDTTable::changeData(int x, int y) {
    QTableWidget* streamsTable = dynamic_cast<QTableWidget*>(QObject::sender());
    if(streamsTable->item(x, y)->text() == "") {
        return;
    }
    double a0 = 85.6 / 8;
    double a = streamsTable->item(x, y)->text().toDouble() * a0;
    table->item(x, y)->setText(QString::number(a));
}

IntensityDTTable::~IntensityDTTable() {

}
