#include "vertexdialog.h"

VertexDialog::VertexDialog(GraphUi *graphUi, QWidget *parent) : QDialog(parent)
{
	this->setMinimumWidth(400);
	this->setMinimumHeight(300);
	layout = new QGridLayout(this);
	this->setLayout(layout);
	layout->setVerticalSpacing(12);
	layout->setHorizontalSpacing(20);
	tableWidget = new QTableWidget(20, 2, this);
	QStringList header;
	header << "vertex" << "description";
	tableWidget->setHorizontalHeaderLabels(header);
	layout->addWidget(tableWidget, 0, 0, 10, -1);
	for (int i = 0; i < graphUi->getVexNum(); ++i) {
		tableWidget->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(i)));
		tableWidget->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(graphUi->getVExInfo(i))));
	}
}
