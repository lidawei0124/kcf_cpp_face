#include "mainwindow.h"
#include <QApplication>
#include "run_tracker.h"

//#define USE_GUI

int main(int argc, char *argv[])
{
 #ifdef USE_GUI
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
#else
    run_tracker();
    return 0;
#endif
}
