#include "Plutus.h"

#include <Logger.h>

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    Logger::init();

    QApplication a(argc, argv);
    Plutus kernel;
    kernel.show();
    bool state = a.exec();
    Logger::clean();
    return state;
}
