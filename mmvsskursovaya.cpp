#include "mmvsskursovaya.h"

MMvSSKursovaya::MMvSSKursovaya(QWidget *parent)
    : QWidget(parent) {
    initWindow();
    initWidgets();
    initWindowElements();
}

void MMvSSKursovaya::initWindow() {
    screens = QGuiApplication::screens();
    screenHeight = screens[0]->size().height();
    screenWidth = screens[0]->size().width();
    widgetHeight = 400;
    widgetWidth = 800;
    if(screenWidth < widgetWidth) {
        widgetWidth = 600;
    }
    setWindowTitle(APP_NAME);
    setWindowIcon(QIcon(":/icons/Kurs_icon.png"));
    setMinimumSize(QSize(widgetWidth, widgetHeight));
    setGeometry((screenWidth / 2) - (widgetWidth / 2),
                (screenHeight / 2) - (widgetHeight / 2),
                widgetWidth, widgetHeight);
}

void MMvSSKursovaya::initWidgets() {
    inputTable = new InputTable;
    inputTable->initTable();
    inputNumTable = new InputNumTable;
    inputNumTable->initTable();
    intensityTable = new IntensityTable(inputTable->table, inputNumTable->table);
    intensityTable->initTable();
    nextTable = new IntensityTable;
    nextTable->initTable();
    shortestTable = new ShortestTable(nextTable->table);
    shortestTable->initTable();
    intensityTable2 = new IntensityTable(nextTable->table, intensityTable->table);
    intensityTable2->initTable();
    streamsTable = new StreamsTable();
    streamsTable->initTable();
    intensityDTTable = new IntensityDTTable;
    intensityDTTable->initTable();
    bandwidthTable = new BandwidthTable;
    bandwidthTable->initTable();
    boTable = new IntensityTable;
    boTable->initTable();
    delTable = new IntensityTable;
    delTable->initTable();
    dlTable = new IntensityTable;
    dlTable->initTable();
    oTable = new IntensityTable;
    oTable->initTable();

    list = new QList<QTableWidget*>;

    list->append(nextTable->table);
    list->append(intensityDTTable->table);
    list->append(bandwidthTable->table);

    list->append(boTable->table);
    list->append(delTable->table);
    list->append(dlTable->table);
    list->append(oTable->table);

    optimizationHandler = new OptimizationHandler(list);

    QObject::connect(inputTable->table, SIGNAL(cellChanged(int, int)),
                     intensityTable, SLOT(changeData(int, int)));
    QObject::connect(inputNumTable->table, SIGNAL(cellChanged(int, int)),
                     intensityTable, SLOT(changeData(int, int)));


    QObject::connect(inputTable->table, SIGNAL(cellChanged(int, int)),
                     shortestTable, SLOT(changeData(int, int)));


    QObject::connect(nextTable->table, SIGNAL(cellChanged(int, int)),
                     intensityTable2, SLOT(changeData(int, int)));
    QObject::connect(intensityTable->table, SIGNAL(cellChanged(int, int)),
                     intensityTable2, SLOT(changeData(int, int)));


    QObject::connect(intensityTable2->table, SIGNAL(cellChanged(int, int)),
                     streamsTable, SLOT(changeData(int, int)));


    QObject::connect(streamsTable->table, SIGNAL(cellChanged(int, int)),
                     intensityDTTable, SLOT(changeData(int, int)));


    QObject::connect(intensityDTTable->table, SIGNAL(cellChanged(int, int)),
                     bandwidthTable, SLOT(changeData(int, int)));


    QObject::connect(bandwidthTable->table, SIGNAL(cellChanged(int, int)),
                     optimizationHandler, SLOT(mkOptimization(int, int)));
}

void MMvSSKursovaya::initWindowElements() {
    tabWidget = new QTabWidget;
    tabWidget->addTab(inputTable, "Input");
    tabWidget->addTab(inputNumTable, "Input Num");
    tabWidget->addTab(intensityTable, "Intensity");
    tabWidget->addTab(shortestTable, "Shortest");
    tabWidget->addTab(nextTable, "Shortest Way");
    tabWidget->addTab(intensityTable2, "Intensity2");
    tabWidget->addTab(streamsTable, "Streams");
    tabWidget->addTab(intensityDTTable, "IntensityDT");
    tabWidget->addTab(bandwidthTable, "Bandwidth");
    tabWidget->addTab(boTable, "Bo");
    tabWidget->addTab(delTable, "DEL");
    tabWidget->addTab(dlTable, "DL");
    tabWidget->addTab(oTable, "O");
    gridLayout = new QGridLayout;
    gridLayout->addWidget(tabWidget);
    gridLayout->setMargin(5);
    gridLayout->setSpacing(10);
    gridLayout->setColumnStretch(0, 1);
    gridLayout->setRowStretch(0, 1);
    setLayout(gridLayout);
    tabWidget->widget(0)->setFocus();

    QObject::connect(tabWidget, SIGNAL(tabBarClicked(int)),
                     this, SLOT(setActive(int)));
}

void MMvSSKursovaya::setActive(int index) {
    if(index != -1) {
        tabWidget->widget(index)->setFocus();
    }
}

MMvSSKursovaya::~MMvSSKursovaya() {
    delete gridLayout;
    delete inputTable;
    delete inputNumTable;
    delete intensityTable;
    delete shortestTable;
    delete intensityTable2;
    delete streamsTable;
    delete intensityDTTable;
    delete bandwidthTable;
    delete nextTable;
    delete delTable;
    delete dlTable;
    delete oTable;
    delete tabWidget;
    delete list;
    delete optimizationHandler;
}
