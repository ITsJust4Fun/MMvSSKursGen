#include "streamstable.h"

StreamsTable::StreamsTable() {

}

double StreamsTable::fErlang(double y, int v) {
    double p = 1;
    for (int i = 1; i < v; ++i) {
        p = 1 + p * i / y;
    }
    return 1 / p;
}

void StreamsTable::changeData(int x, int y) {
    QTableWidget* intensityTable = dynamic_cast<QTableWidget*>(QObject::sender());
    if(intensityTable->item(x, y)->text() == "") {
        return;
    }
    double s = intensityTable->item(x, y)->text().toDouble();
    if(s <= 0){
        table->item(x, y)->setText(QString::number(INFINITY));
        return;
    }
    double p0 = 1 - (98.0/100);
    int v = 0;
    double p = 1;
    while(p0 < p) {
        v++;
        p = fErlang(s, v);
    }
    table->item(x, y)->setText(QString::number(v));
}

StreamsTable::~StreamsTable() {

}
