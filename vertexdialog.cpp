#include "vertexdialog.h"

VertexDialog::VertexDialog(GraphUi *graphUi, QWidget *parent) : QDialog(parent) {
	ui = graphUi;
	this->setMinimumWidth(500);
	this->setMinimumHeight(300);
	layout = new QGridLayout(this);
	this->setLayout(layout);
	layout->setVerticalSpacing(12);
	layout->setHorizontalSpacing(20);
	tableWidget = new QTableWidget(20, 4, this);
	QStringList header;
	header << "vertex" << "description" << "x" << "y";
	tableWidget->setHorizontalHeaderLabels(header);
	layout->addWidget(tableWidget, 0, 0, 10, -1);
	for (int i = 0; i < graphUi->getVexNum(); ++i) {
		tableWidget->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(i)));
		tableWidget->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(graphUi->getVExInfo(i))));
		tableWidget->setItem(i, 2, new QTableWidgetItem(QString("%1").arg(graphUi->getPos(i).x())));
		tableWidget->setItem(i, 3, new QTableWidgetItem(QString("%1").arg(graphUi->getPos(i).y())));
	}

	connect(tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(setPos(int, int)));
	connect(this, SIGNAL(updateGraph()), ui, SIGNAL(update()));
}

void VertexDialog::setPos(int row, int col) {
	if (col == 2 || col == 3) {
		ui->setPos(tableWidget->item(row, 1)->text().toUtf8(), tableWidget->item(row, 2)->text().toInt(), tableWidget->item(row, 3)->text().toInt());
		emit updateGraph();
	} else {
		QMessageBox::information(this, "info", "you can only change the pos");
	}
}
