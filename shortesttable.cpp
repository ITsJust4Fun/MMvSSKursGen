#include "shortesttable.h"

ShortestTable::ShortestTable(QTableWidget* nextTable) {
    this->nextTable = nextTable;
}

void ShortestTable::changeData(int x, int y) {
    QTableWidget* inputTable = dynamic_cast<QTableWidget*>(QObject::sender());
    QString val = inputTable->item(table->rowCount() - 1,
                                   table->columnCount() - 1)->text();
    if(val != "0") {
        return;
    }
    for(int i = 0; i < nextTable->rowCount(); i++) {
        for(int j = 0; j < nextTable->columnCount(); j++) {
            nextTable->item(i, j)->setText(QString::number(j + 1));
            table->item(i, j)->setText(inputTable->item(i, j)->text());
        }
    }
    //table->item(table->rowCount() - 1, table->columnCount() - 1)->setText("-1");
    for(int k = 0; k < table->rowCount(); k++) {
        for(int i = 0; i < table->rowCount(); i++) {
            for(int j = 0; j < table->rowCount(); j++) {
                QString val1 = table->item(i, j)->text();
                QString val2 = table->item(i, k)->text();
                QString val3 = table->item(k, j)->text();
                double w1 = val1 != "" ? val1.toDouble() : INFINITY;
                double w2 = val2 != "" ? val2.toDouble() : INFINITY;
                double w3 = val3 != "" ? val3.toDouble() : INFINITY;
                double s = w1 < (w2 + w3) ? w1 : w2 + w3;
                if(s != INFINITY) {
                    table->item(i, j)->setText(QString::number(s));
                }
                if ((w2 + w3) < w1) {
                    nextTable->item(i, j)->setText(nextTable->item(i, k)->text());
                }
            }
        }
    }
    //table->item(table->rowCount() - 1, table->columnCount() - 1)->setText("0");
    for(int i = 0; i < table->rowCount(); i++) {
        for(int j = 0; j < table->columnCount(); j++) {
            QString value = table->item(i, j)->text();
            if(value == "") {
                nextTable->item(i, j)->setText("");
            }
        }
    }

    Q_UNUSED(x);
    Q_UNUSED(y);
}

ShortestTable::~ShortestTable() {

}
