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
                                       QTableWidget* delTable, double dc, int x, int y) {
    double L = 200 * 8;
    for(int i = 0; i < delTable->rowCount(); i++) {
        for(int j = 0; j < delTable->columnCount(); j++) {
            if(boTable->item(i, j)->text() != "") {
                double bm = boTable->item(i, j)->text().toDouble();
                double am = intensityDTTable->item(i, j)->text().toDouble();
                if((i == x) && (j == y)) {
                    bm += dc;
                }
                delTable->item(i, j)->setText(QString::number(L / (bm - am), 'g', 15));
            }
        }
    }
}

double OptimizationHandler::getWaySum(QTableWidget* nextTable, QTableWidget* delTable,
                                      int i, int j) {
    double sum = 0;
    if(i == j) {
        sum = delTable->item(i - 1, j - 1)->text().toDouble();
        return sum;
    }
    int k = i;
    int nextK = j;
    while(k != j) {
        nextK = nextTable->item(k - 1, j - 1)->text().toInt();
        sum += delTable->item(k - 1, nextK - 1)->text().toDouble();
        k = nextK;
    }
    return sum;
}

void OptimizationHandler::calcDlTable(QTableWidget* nextTable, QTableWidget* delTable,
                 QTableWidget* dlTable) {
    for(int i = 0; i < dlTable->rowCount(); i++) {
        for(int j = 0; j < dlTable->columnCount(); j++) {
            dlTable->item(i, j)->setText(QString::number(getWaySum(nextTable , delTable,
                                                                   (i + 1), (j + 1)), 'g', 15));
        }
    }
}

void OptimizationHandler::calcOTable(QTableWidget* dlTable, QTableWidget* oTable, int x, int y) {
    double Topt = 0.05;
    double sum = 0;
    for(int i = 0; i < dlTable->rowCount(); i++) {
        for(int j = 0; j < dlTable->columnCount(); j++) {
            double dlij = dlTable->item(i, j)->text().toDouble();
            sum += (dlij - Topt) * (dlij - Topt);
        }
    }
    oTable->item(x, y)->setText(QString::number(sum, 'g', 15));
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

    OptimizationProgressBar progressBar;
    progressBar.show();

    copyToBo(bandwidthTable, boTable);

    double dc = 10000;
    double Oprev = Q_INFINITY;
    double m0 = Q_INFINITY;

    int cycles = 0;

    do {
        progressBar.changeLabel("Please Wait... (cycles = " + QString::number(++cycles) + ")");
        progressBar.setValue(cycles);
        Oprev = m0;

        for(int i = 0; i < boTable->rowCount(); i++) {
            for(int j = 0; j < boTable->columnCount(); j++) {
                if(boTable->item(i, j)->text() != "") {
                    calcDelTable(intensityDTTable, boTable, delTable, dc, i, j);
                    calcDlTable(nextTable, delTable, dlTable);
                    calcOTable(dlTable, oTable, i, j);
                }
            }
        }

        int mi = 0;
        int mj = 0;
        m0 = oTable->item(mi, mj)->text().toDouble();

        for(int i = 0; i < oTable->rowCount(); i++) {
            for(int j = 0; j < oTable->columnCount(); j++) {
                if(oTable->item(i, j)->text() != "") {
                    double tmp = oTable->item(i, j)->text().toDouble();
                    if(tmp < m0) {
                        m0 = tmp;
                        mi = i;
                        mj = j;
                    }
                }
            }
        }

        double b = boTable->item(mi, mj)->text().toDouble();
        boTable->item(mi, mj)->setText(QString::number(b + dc, 'g', 15));
        QCoreApplication::processEvents();
    } while(m0 < Oprev);
    progressBar.setValue(650);
    progressBar.close();
}

OptimizationHandler::~OptimizationHandler() {

}
