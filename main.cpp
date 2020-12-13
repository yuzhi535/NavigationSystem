#include "mainwindow.h"

#include <QApplication>

#define GRAPHDEBUG 0


int main(int argc, char *argv[])
{
#if GRAPHDEBUG
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
#else
    QString fileName;

    if (argc > 1)
    {
        fileName = argv[1];
    }
    else
    {
        fileName = "pre.txt";
    }

    Graph graph;
//    graph.



    return 0;
#endif
}
