#ifndef MMVSSKURSOVAYA_H
#define MMVSSKURSOVAYA_H

#include <QApplication>
#include <QClipboard>
#include <QWidget>
#include <QGuiApplication>
#include <QIcon>
#include <QScreen>
#include <QTableWidget>
#include <QHeaderView>
#include <QGridLayout>
#include <QKeyEvent>
#include <QTabWidget>
#include "inputtable.h"
#include "inputnumtable.h"
#include "intensitytable.h"
#include "shortesttable.h"
#include "streamstable.h"
#include "intensitydttable.h"
#include "bandwidthtable.h"
#include "optimizationhandler.h"

class MMvSSKursovaya : public QWidget {
    Q_OBJECT

public:
    void initWindow();
    void initWindowElements();
    void initWidgets();
    MMvSSKursovaya(QWidget *parent = nullptr);
    virtual ~MMvSSKursovaya();
private:
    QList<QScreen*> screens;
    QTabWidget* tabWidget;
    QGridLayout* gridLayout;
    InputTable* inputTable;
    InputNumTable* inputNumTable;
    IntensityTable* intensityTable;
    ShortestTable* shortestTable;
    IntensityTable* intensityTable2;
    StreamsTable* streamsTable;
    IntensityDTTable* intensityDTTable;
    BandwidthTable* bandwidthTable;
    IntensityTable* delTable;
    IntensityTable* nextTable;
    IntensityTable* dlTable;
    IntensityTable* oTable;
    IntensityTable* boTable;
    QList<QTableWidget*>* list;
    OptimizationHandler* optimizationHandler;
    const QString APP_NAME = "MMvSS Kursovaya";
    int widgetHeight;
    int widgetWidth;
    int screenHeight;
    int screenWidth;
public slots:
    void setActive(int);
};

#endif // MMVSSKURSOVAYA_H
