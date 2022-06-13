#include "MainWindow.h"
#include "api.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
//    auto test = SimulationCoreAPI::getInstance();
//    test->run();
    return a.exec();
}
