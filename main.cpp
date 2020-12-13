#include "mainwindow.h"

#include <QApplication>

#define GRAPHDEBUG 0

#if GRAPHDEBUG == 0
#include <iostream>
#endif

int main(int argc, char *argv[])
{
#if GRAPHDEBUG
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
#else
    std::string fileName;

    if (argc > 1)
    {
        fileName = argv[1];
    }
    else
    {
        fileName = "pre.dat";
    }
    std::fstream fout;
    fout.open(fileName, std::ios::in);

    Graph graph;
    graph.init(fout);
    graph.show();
//    graph.



    return 0;
#endif
}
