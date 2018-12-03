#include "optimizationhandler.h"

OptimizationHandler::OptimizationHandler(QList<QTableWidget*>* list, QObject *parent) : QObject(parent) {
    this->list = list;
}

void OptimizationHandler::copyToBo(QTableWidget* bandwidthTable,
                                   QTableWidget* boTable) {
    for(int i = 0; i < boTable->rowCount(); i++) {
        for(int j = 0; j < boTable->columnCount(); j++) {
            QString val = bandwidthTable->item(i, j)->text();
            boTable->item(i, j)->setText(val);
        }
    }
}

void OptimizationHandler::calcDelTable(QTableWidget* intensityDTTable, QTableWidget* boTable,
                                       QTableWidget* delTable, double dc) {
    double L = 200 / 1024.0;
    for(int i = 0; i < delTable->rowCount(); i++) {
        for(int j = 0; j < delTable->columnCount(); j++) {
            double bm = boTable->item(i, j)->text().toDouble();
            double am = intensityDTTable->item(i, j)->text().toDouble();
            delTable->item(i, j)->setText(QString::number(L / (bm + dc - am)));
        }
    }
}

double OptimizationHandler::getWaySum(QTableWidget* nextTable, QTableWidget* delTable,
                                      int i, int j) {
    double sum = 0;
    if(nextTable->item((i - 1), (j - 1))->text() == "") {
        return INFINITY;
    }
    int k = i;
    while(k != j) {
        sum += delTable->item((k - 1), (j - 1))->text().toDouble();
        k = nextTable->item((k - 1), (j - 1))->text().toInt();
    }
    sum += delTable->item((k - 1), (j - 1))->text().toDouble();
    return sum;
}

void OptimizationHandler::calcDlTable(QTableWidget* nextTable, QTableWidget* delTable,
                 QTableWidget* dlTable) {
    for(int i = 0; i < dlTable->rowCount(); i++) {
        for(int j = 0; j < dlTable->columnCount(); j++) {
            dlTable->item(i, j)->setText(QString::number(getWaySum(nextTable , delTable,
                                                                   (i + 1), (j + 1))));
        }
    }
}

void OptimizationHandler::calcOTable(QTableWidget* dlTable, QTableWidget* oTable) {
    double Topt = 0.05;
    for(int i = 0; i < dlTable->rowCount(); i++) {
        for(int j = 0; j < dlTable->columnCount(); j++) {
            double dlij = dlTable->item(i, j)->text().toDouble();
            oTable->item(i, j)->setText(QString::number(pow(dlij - Topt , 2.0)));
        }
    }
}

void OptimizationHandler::mkOptimization(int x, int y) {
    QTableWidget* dtTable = dynamic_cast<QTableWidget*>(QObject::sender());
    if(dtTable->item(dtTable->rowCount() - 1, dtTable->columnCount() - 1)->text() == "") {
        return;
    }
    if((x != dtTable->rowCount() - 1) && (y != dtTable->columnCount() - 1)){
        return;
    }

    QTableWidget* nextTable = (*list)[0];
    QTableWidget* intensityDTTable = (*list)[1];
    QTableWidget* bandwidthTable = (*list)[2];

    QTableWidget* boTable = (*list)[3];
    QTableWidget* delTable = (*list)[4];
    QTableWidget* dlTable = (*list)[5];
    QTableWidget* oTable = (*list)[6];

    copyToBo(bandwidthTable, boTable);

    double dc = (10000 / 1024.0) / 8.0;
    double Oprev = INFINITY;
    double m0 = INFINITY;

    do {
        Oprev = m0;

        calcDelTable(intensityDTTable, boTable, delTable, dc);

        calcDlTable(nextTable, delTable, dlTable);

        calcOTable(dlTable, oTable);

        m0 = oTable->item(0, 1)->text().toDouble();
        int mi = 0;
        int mj = 1;

        for(int i = 0; i < oTable->rowCount(); i++) {
            for(int j = 0; j < oTable->columnCount(); j++) {
                double tmp = oTable->item(i, j)->text().toDouble();
                if(tmp < m0) {
                    m0 = tmp;
                    mi = i;
                    mj = j;
                }
            }
        }

        double b = boTable->item(mi, mj)->text().toDouble();
        boTable->item(mi, mj)->setText(QString::number(b + dc));
        boTable->item(mj, mi)->setText(QString::number(b + dc));
    } while(m0 < Oprev);
}

OptimizationHandler::~OptimizationHandler() {

}
