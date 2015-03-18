#include "ComPortTestWgt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ComPortTestWgt w;
    w.show();

    return a.exec();
}
