#include "inputtable.h"

InputTable::InputTable(QWidget *parent) : QWidget(parent) {
    table = new QTableWidget;
    gridLayout = new QGridLayout;
    gridLayout->addWidget(table);
    gridLayout->setMargin(5);
    gridLayout->setSpacing(10);
    gridLayout->setColumnStretch(0, 1);
    gridLayout->setRowStretch(0, 1);
    setLayout(gridLayout);
}

void InputTable::initTable() {
    table->setColumnCount(20);
    table->setRowCount(20);
    table->setShowGrid(true);
    table->setSelectionMode(QAbstractItemView::ContiguousSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectItems);
    table->horizontalHeader()->setMinimumSectionSize(35);
    table->verticalHeader()->setMinimumSectionSize(20);
    table->horizontalHeader()->sortIndicatorOrder();
    table->resizeColumnsToContents();
    table->resizeRowsToContents();
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 20; j++) {
            table->setItem(i, j, new QTableWidgetItem);
        }
    }
}

void InputTable::paste() {
    if(!table->item(0, 0)->flags().testFlag(Qt::ItemIsEditable)) {
        return;
    }
    table->item(table->rowCount() - 1,
                table->columnCount() - 1)->setText("");
    QString str = QApplication::clipboard()->text();
    QStringList rows = str.split('\n');
    if(rows.count() - 1 > table->rowCount() ||
       rows[0].split('\t').count() > table->columnCount()) {
        return;
    }
    for(int i = 0; i < rows.count() - 1; i++) {
        QStringList columns = rows[i].split('\t');
        for(int j = 0; j < columns.count(); j++) {
            table->item(i, j)->setText(columns[j].replace(",", "."));
        }
    }
}

void InputTable::copy() {
    QString toClipboard = "";
    for(int i = 0; i < table->rowCount(); i++) {
        for(int j = 0; j < table->columnCount(); j++) {
            QString val = table->item(i, j)->text().replace(".", ",");
            toClipboard += val;
            if(j != table->columnCount() - 1) {
                toClipboard += "\t";
            }
        }
        toClipboard += "\n";
    }
    QApplication::clipboard()->setText(toClipboard);
}

void InputTable::keyPressEvent(QKeyEvent* e) {
    if (e->matches(QKeySequence::Paste)) {
        paste();
    } else if (e->matches(QKeySequence::Copy)) {
        copy();
    }
}

InputTable::~InputTable() {
    delete gridLayout;
    delete table;
}
