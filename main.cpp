#include "mhxxarmorinput.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MHXXArmorInput w;
    w.show();
    return a.exec();
}
