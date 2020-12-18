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
	VertexDialog dialog;
	dialog.show();

#endif
	return a.exec();
}
