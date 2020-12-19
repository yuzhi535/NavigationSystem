#include "mainwindow.h"

#include <QApplication>

#include "graph.h"

int main(int argc, char *argv[]) {
	QString fileName("pre.txt");
	QApplication a(argc, argv);
#if DEV == 1
	MainWindow w;
	w.show();
#else
	Graph graph;
	graph.init_from_file();

#endif
	return a.exec();
}
