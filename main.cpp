#include "rpitc.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RPiTC w;
    w.show();

    return a.exec();
}
