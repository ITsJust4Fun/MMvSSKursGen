#include "intensitytable.h"

IntensityTable::IntensityTable(QTableWidget* inputTable,
                               QTableWidget* inputNumTable) {
    this->inputTable = inputTable;
    this->inputNumTable = inputNumTable;
}

void IntensityTable::initTable() {
    InputTable::initTable();
    for(int i = 0; i < table->rowCount(); i++){
        for(int j = 0; j < table->columnCount(); j++){
            QTableWidgetItem *item = table->item(i, j);
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        }
    }
}

double IntensityTable::ySum(int i, int j) {
    double ysum = 0;
    if(inputTable->item(0, 0)->text() == "0") {
        return ytotal;
    }
    if(inputTable->item((i - 1), (j - 1))->text() == "") {
        return INFINITY;
    }
    int k = i;
    while(k != j) {
        ysum += inputNumTable->item((k - 1), 0)->text().toDouble() * 0.1;
        k = inputTable->item((k - 1), (j - 1))->text().toInt();
    }
    ysum += inputNumTable->item((k - 1), 0)->text().toDouble() * 0.1;
    return ysum;
}

void IntensityTable::changeData(int x, int y) {
    if (dynamic_cast<QTableWidget*>(QObject::sender())->columnCount() == 8 && y != 2) {
        return;
    }
    if (inputNumTable->item(inputNumTable->rowCount() - 1, 0)->text() == "") {
        return;
    }
    if (inputTable->item(inputTable->rowCount() - 1,
                         inputTable->columnCount() - 1)->text() == "") {
        return;
    }

    ytotal = 0;
    for(int i = 0; i < inputNumTable->rowCount(); i++) {
        ytotal += inputNumTable->item(i, 0)->text().toDouble() * 0.1;
    }
    for(int i = 0; i < inputTable->rowCount(); i++) {
        for(int j = 0; j < inputTable->columnCount(); j++) {
            //QString val = inputTable->item(i, j)->text();
            double yj = inputNumTable->item(j, 0)->text().toDouble() * 0.1;
            double yi = inputNumTable->item(i, 0)->text().toDouble() * 0.1;
            double yij;
            if (i != j) {
                double kj = yj / ySum(i + 1, j + 1);
                yij = kj * yi;
            } else {
                yij = (yi * yj) / ytotal;
            }
            table->item(i, j)->setText(QString::number(yij));
        }
    }
    Q_UNUSED(x);
}

IntensityTable::~IntensityTable() {

}
