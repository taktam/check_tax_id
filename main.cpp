#include "checkwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CheckWindow w;
    w.show();
    return a.exec();
}
