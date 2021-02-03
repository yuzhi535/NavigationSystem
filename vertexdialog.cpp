#include "vertexdialog.h"
#include <QTableWidgetSelectionRange>
#include <QHeaderView>

VertexDialog::VertexDialog(GraphUi *graphUi, QWidget *parent) : QDialog(parent) {
	ui = graphUi;
	isValid = true;

	this->setMinimumWidth(600);
	this->setMinimumHeight(450);
	this->setStyleSheet("background-color:black; color:white");
	layout = new QGridLayout(this);
	this->setLayout(layout);
	layout->setVerticalSpacing(12);
	layout->setHorizontalSpacing(20);
	tableWidget = new QTableWidget(20, 4, this);
	QStringList header;
	header << "vertex" << "description" << "x" << "y";

	tableWidget->setHorizontalHeaderLabels(header);
	tableWidget->setStyleSheet("background-color:white; color: black; ");  //设计样式
	tableWidget->horizontalHeader()->setStyleSheet("background-color:white; color: black; ");
	layout->addWidget(tableWidget, 0, 0, 10, -1);
	for (int i = 0; i < graphUi->getVexNum(); ++i) {

		//设置点的信息不可编辑
		QTableWidgetItem *item1 = new QTableWidgetItem(QString("%1").arg(i));
		item1->setBackground(QBrush(QColor(Qt::lightGray)));
		item1->setFlags(item1->flags() & (~Qt::ItemIsEditable));
		tableWidget->setItem(i, 0, item1);

		QTableWidgetItem *item2 = new QTableWidgetItem(QString("%1").arg(graphUi->getVExInfo(i)));
		item2->setBackground(QBrush(QColor(Qt::lightGray)));
		item2->setFlags(item2->flags() & (~Qt::ItemIsEditable));
		tableWidget->setItem(i, 1, item2);

		//添加坐标
		tableWidget->setItem(i, 2, new QTableWidgetItem(QString("%1").arg(graphUi->getPos(i).x())));
		tableWidget->setItem(i, 3, new QTableWidgetItem(QString("%1").arg(graphUi->getPos(i).y())));
	}

	button1 = new QPushButton(this);
	button1->setText(tr("confirm to change the pos"));
	layout->addWidget(button1, 11, 1, 1, 1);

	button2 = new QPushButton(this);
	button2->setText(tr("delete the vertex on the line"));
	layout->addWidget(button2, 11, 0, 1, 1);


	connect(tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(setPos(int, int)));
	connect(this, &VertexDialog::updateGraph,
	        [&]() { ui->update(); });
	connect(button2, SIGNAL(clicked(bool)), this, SLOT(on_button2_clicked()));
	connect(button1, SIGNAL(clicked(bool)), this, SLOT(close()));
}

void VertexDialog::setPos(int row, int col) {
	if (col == 2 || col == 3) {
		ui->setPos(tableWidget->item(row, 1)->text().toUtf8(), tableWidget->item(row, 2)->text().toInt(),
		           tableWidget->item(row, 3)->text().toInt());
		emit updateGraph();
	} else {
		QMessageBox::information(this, "info", "you can only change the pos");
		isValid = false;
	}
}

void VertexDialog::on_button2_clicked() {
	int index = this->tableWidget->currentRow();
	if (index < ui->getVexNum()) {
		if (this->tableWidget->item(index, 1)->text() != "" && isValid) {
			this->ui->delVex(this->tableWidget->item(index, 1)->text());
		}
	}
	emit updateGraph();
	close();
}
