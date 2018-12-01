#include "mmvsskursovaya.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MMvSSKursovaya w;
    w.show();

    return a.exec();
}
