#include "inputnumtable.h"

InputNumTable::InputNumTable() {

}

void InputNumTable::initTable() {
    table->setColumnCount(1);
    table->setRowCount(20);
    table->setShowGrid(true);
    table->setSelectionMode(QAbstractItemView::ContiguousSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectItems);
    table->horizontalHeader()->setMinimumSectionSize(70);
    table->verticalHeader()->setMinimumSectionSize(20);
    table->horizontalHeader()->sortIndicatorOrder();
    table->resizeColumnsToContents();
    table->resizeRowsToContents();
    table->setHorizontalHeaderLabels(QStringList() << "Subscribers"
                                     );
    for(int i = 0; i < 20; i++) {
        table->setItem(i, 0, new QTableWidgetItem);
    }
    QObject::connect(table, SIGNAL(cellChanged(int, int)),
                     this, SLOT(changeData(int, int)));
}

void InputNumTable::changeData(int x, int y) {
    if(y != 0){
        return;
    }
    int total = 0;
    for(int i = 0; i < table->rowCount(); i++){
        QString str = table->item(i, 0)->text();
        if(str == QString("")){
            return;
        }
        total += str.toDouble();
    }
    if(table->columnCount() == 1) {
        for(int i = 0; i < 7; i++){
            table->insertColumn(table->columnCount());
        }
        table->setHorizontalHeaderLabels(QStringList() << "Subscribers"
                                                       << "Total"
                                                       << "Ki"
                                                       << "Total K"
                                        );
        for(int i = 0; i < table->rowCount(); i++) {
            for(int j = 1; j < table->columnCount(); j++){
                table->setItem(i, j, new QTableWidgetItem);
            }
        }
        table->item(0, 4)->setText("n (шт)");
        table->item(1, 4)->setText("y0 (Эрл)");
        table->item(2, 4)->setText("Codec");

        table->item(0, 5)->setText("20");
        table->item(1, 5)->setText("0.1");
        table->item(2, 5)->setText("G.771");

        table->item(0, 6)->setText("L (байты)");
        table->item(1, 6)->setText("a0 (бит/с)");
        table->item(2, 6)->setText("T0 (с)");
        table->item(3, 6)->setText("q (%)");

        table->item(0, 7)->setText("200");
        table->item(1, 7)->setText("85600");
        table->item(2, 7)->setText("0.10");
        table->item(3, 7)->setText("98");

        for(int i = 0; i < 4; i++){
            if(i != 3){
                table->item(i, 4)->setBackgroundColor(QColor("Green"));
            }
            table->item(i, 6)->setBackgroundColor(QColor("Green"));
        }
        for(int i = 0; i < 4; i++){
            if(i != 3){
                table->item(i, 5)->setBackgroundColor(QColor("Gray"));
            }
            table->item(i, 7)->setBackgroundColor(QColor("Gray"));
        }
    }
    double totalk = 0;
    for(int i = 0; i < table->rowCount(); i++) {
        double n = table->item(i, 0)->text().toDouble();
        double k = n / total;
        table->item(i, 2)->setText(QString::number(k));
        totalk += k;

    }
    table->item(0, 1)->setText(QString::number(total));
    table->item(0, 3)->setText(QString::number(totalk));
    Q_UNUSED(x);
}

InputNumTable::~InputNumTable() {

}
