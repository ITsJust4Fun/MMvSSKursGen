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

void IntensityTable::addToWay(int i, int j) {
    if(inputTable->item(i - 1, j - 1)->text() == "") {
        return;
    }
    double y = inputNumTable->item(i - 1, j - 1)->text().toDouble();
    if(i == j) {
        table->item(i - 1, j - 1)->setText(QString::number(y));
        return;
    }
    int k = i;
    int nextK = j;
    while(k != j) {
        nextK = inputTable->item(k - 1, j - 1)->text().toInt();
        if(table->item(k - 1, nextK - 1)->text() == "") {
            table->item(k - 1, nextK - 1)->setText(QString::number(y));
        } else {
            double prev = table->item(k - 1, nextK - 1)->text().toDouble();
            table->item(k - 1, nextK - 1)->setText(QString::number(prev + y));
        }
        k = nextK;
    }
}

void IntensityTable::changeData(int x, int y) {
    if (dynamic_cast<QTableWidget*>(QObject::sender())->columnCount() == 8 && y != 2) {
        return;
    }
    if (inputNumTable->item(inputNumTable->rowCount() - 1, 0)->text() == "") {
        return;
    }

    if (inputNumTable->item(0, 0)->text().contains('.')) {
        if (inputNumTable->item(inputNumTable->rowCount() - 1,
                                inputNumTable->columnCount() - 1)->text() == "") {
            return;
        }
    }

    if (inputTable->item(inputTable->rowCount() - 1,
                         inputTable->columnCount() - 1)->text() == "") {
        return;
    }

    ytotal = 0;
    for(int i = 0; i < inputNumTable->rowCount(); i++) {
        ytotal += inputNumTable->item(i, 0)->text().toDouble() * 0.1;
    }
    if(inputTable->item(0, 0)->text() == "0") {
        for(int i = 0; i < inputTable->rowCount(); i++) {
            for(int j = 0; j < inputTable->columnCount(); j++) {
                double yj = inputNumTable->item(j, 0)->text().toDouble() * 0.1;
                double yi = inputNumTable->item(i, 0)->text().toDouble() * 0.1;
                double yij;
                yij = (yi * yj) / ytotal;
                table->item(i, j)->setText(QString::number(yij));
            }
        }
    } else {
        for(int i = 0; i < inputTable->rowCount(); i++) {
            for(int j = 0; j < inputTable->columnCount(); j++) {
                addToWay(i + 1, j + 1);
            }
        }
    }
    Q_UNUSED(x);
}

IntensityTable::~IntensityTable() {

}
