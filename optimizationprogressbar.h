#ifndef OPTIMIZATIONPROGRESSBAR_H
#define OPTIMIZATIONPROGRESSBAR_H

#include <QObject>
#include <QWidget>
#include <QProgressBar>
#include <QIcon>
#include <QScreen>
#include <QGuiApplication>
#include <QGridLayout>
#include <QLabel>

class OptimizationProgressBar : public QWidget
{
    Q_OBJECT
public:
    explicit OptimizationProgressBar(QWidget *parent = nullptr);
    virtual ~OptimizationProgressBar();
    void changeLabel(const QString&);
    void setValue(int);
private:
    QProgressBar* progressBar;
    int widgetHeight;
    int widgetWidth;
    int screenHeight;
    int screenWidth;
    QList<QScreen*> screens;
    QGridLayout* gridLayout;
    QLabel* label;
    QLabel* textLabel;

signals:

public slots:
};

#endif // OPTIMIZATIONPROGRESSBAR_H
