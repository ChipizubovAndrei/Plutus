#include "Plutus.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Plutus kernel;
    kernel.show();
    return a.exec();
}
