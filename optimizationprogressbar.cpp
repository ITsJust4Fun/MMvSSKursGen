#include "optimizationprogressbar.h"

OptimizationProgressBar::OptimizationProgressBar(QWidget *parent) : QWidget(parent) {
    screens = QGuiApplication::screens();
    screenHeight = screens[0]->size().height();
    screenWidth = screens[0]->size().width();
    widgetHeight = 75;
    widgetWidth = 400;
    setWindowTitle("Optimization Process");
    setWindowIcon(QIcon(":/icons/Kurs_icon.png"));
    setMinimumSize(QSize(widgetWidth, widgetHeight));
    setGeometry((screenWidth / 2) - (widgetWidth / 2),
                (screenHeight / 2) - (widgetHeight / 2),
                widgetWidth, widgetHeight);
    setFixedSize(widgetWidth, widgetHeight);
    progressBar = new QProgressBar;
    gridLayout = new QGridLayout;
    progressBar->setMinimum(0);
    progressBar->setMaximum(650);
    progressBar->setValue(0);
    label = new QLabel;
    label->setText("     ");
    textLabel = new QLabel;
    gridLayout->addWidget(textLabel, 0, 1, 1, 1, Qt::AlignCenter);
    gridLayout->addWidget(label, 0, 0, 1, 1, Qt::AlignCenter);
    gridLayout->addWidget(progressBar, 1, 1, 1, 1);
    gridLayout->setMargin(5);
    gridLayout->setSpacing(10);
    gridLayout->setColumnStretch(1, 1);
    gridLayout->setRowStretch(1, 1);
    setLayout(gridLayout);
}

void OptimizationProgressBar::changeLabel(const QString& str) {
    textLabel->setText(str);
}

void OptimizationProgressBar::setValue(int val) {
    progressBar->setValue(val);
}

OptimizationProgressBar::~OptimizationProgressBar() {
    delete progressBar;
    delete gridLayout;
    delete label;
    delete textLabel;
}
