#include "edgedialog.h"
#include <QDebug>
#include <QMessageBox>

const int maxEdgeNum = 20;

EdgeDialog::EdgeDialog(GraphUi *graphUi, QWidget *parent) {
	this->setMinimumWidth(400);
	this->setMinimumHeight(300);
	ui = graphUi;
	this->setStyleSheet("background-color:black");
	layout = new QGridLayout(this);
	// 设置布局
	this->setLayout(layout);
	layout->setVerticalSpacing(12);
	layout->setHorizontalSpacing(20);

	tableWidget = new QTableWidget(maxEdgeNum, 3, this);
	tableWidget->setStyleSheet("color: black; background-color:white");  //设计样式
	QStringList header;
	header << "from" << "to" << "weight";
	tableWidget->setHorizontalHeaderLabels(header);
	//添加到布局
	layout->addWidget(tableWidget, 0, 0, 10, -1);

	button1 = new QPushButton(this);
	button2 = new QPushButton(this);
	button1->setText(tr("confirm"));
	button2->setText(tr("exit"));

	// 设置样式表
	button1->setStyleSheet(
			"background-color: black ; color: yellow; selection-color: white; selection-background-color: blue");
	button2->setStyleSheet(
			"background-color: black ; color: yellow; selection-color: white; selection-background-color: blue");

	//添加到布局
	layout->addWidget(button1, 10, 0, 2, 10);
	layout->addWidget(button2, 10, 10, 2, 10);


	connect(button1, SIGNAL(clicked(bool)), this, SLOT(on_button_1_clicked()));
	connect(button2, SIGNAL(clicked(bool)), this, SLOT(on_button_2_clicked()));

	auto edge = graphUi->getEdge();
	for (int i = 0; i < edge.size(); ++i) {
		tableWidget->setItem(i, 0,
		                     new QTableWidgetItem(
				                     QString("%1").arg(graphUi->getVExInfo(edge[i].m_pair.from))));
		tableWidget->setItem(i, 1,
		                     new QTableWidgetItem(
				                     QString("%1").arg(graphUi->getVExInfo(edge[i].m_pair.to))));
		tableWidget->setItem(i, 2,
		                     new QTableWidgetItem(
				                     QString("%1").arg(edge[i].weight)));
	}

	col1.clear();
	col2.clear();
	col3.clear();

	col1.resize(maxEdgeNum);
	col2.resize(maxEdgeNum);
	col3.resize(maxEdgeNum);

	for (int i = 0; i < ui->getEdge().size(); ++i) {
		col1[i].first = col1[i].second = tableWidget->item(i, 0)->text().toUtf8();
		qDebug() << "row=" << i << " " << col1[i].second;
	}

	for (int i = 0; i < ui->getEdge().size(); ++i) {
		col2[i].first = col2[i].second = tableWidget->item(i, 1)->text().toUtf8();
		qDebug() << "row=" << i << " " << col2[i].second;
	}
	for (int i = 0; i < ui->getEdge().size(); ++i) {
		col3[i].first = col3[i].second = tableWidget->item(i, 2)->text().toInt();
		qDebug() << "row=" << i << " " << col2[i].second;
	}

	connect(tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(onTableItemChanged(int, int)));
}

void EdgeDialog::on_button_1_clicked() {
	bool flag1[maxEdgeNum] = {0}, flag2[maxEdgeNum] = {0};
	for (int i = 0; i < maxEdgeNum; ++i) {
		// 对顶点的更改
		//如果顶点名称第一个和第二个不一样，则更改顶点
		if (col1[i].first != col1[i].second) {
			if (col1[i].first != "") {
				ui->setVexInfo(i, col1[i].second);
			} else {
				qDebug() << "edit a new vertex";
				if (ui->getVexIndex(col1[i].second) == -1)
					ui->addVex(col1[i].second);
			}
			flag1[i] = true;
		}
//		 改变顶点
		if (col2[i].first != col2[i].second) {
			if (col2[i].first != "") {
				ui->setVexInfo(i, col1[i].second);
			} else {
				qDebug() << "edi a new vertex";
				if (ui->getVexIndex(col1[i].second) == -1)
					ui->addVex(col2[i].second);
			}
			flag2[i] = true;
		}
		//改变权重
		if (col3[i].first != col3[i].second) {
			if (col3[i].second == 0) {
				if (flag1[i] && flag2[i]) {
					QMessageBox::information(this, "info",
					                         QString("row%1 col%2 no weight").arg(i).arg(i));
				} else {
					QMessageBox::information(this, "info", "edit not complete");
					return;
				}
			}
			int index1, index2;
			qDebug() << QString("col1=%1 col2=%2").arg(col1[i].second).arg(col2[i].second);
			index1 = ui->getVexIndex(col1[i].second);
			index2 = ui->getVexIndex(col2[i].second);
			qDebug() << QString("index1=%1,index2=%2,weight=%3").arg(index1).arg(index2).arg(col3[i].second);
			if (index1 != -1 && index2 != -1) {
				Road road(index1, index2, col3[i].second);
				ui->addArc(road);
			}
		}
	}
	emit updateGraph();
	this->close();
}

// 退出
void EdgeDialog::on_button_2_clicked() {
	this->close();
}

void EdgeDialog::onTableItemChanged(int row, int column) {
	qDebug() << "changed";
	switch (column) {
		case 0:
			col1[row].second = tableWidget->item(row, column)->text().toUtf8();
			qDebug() << "row " << row << " column= " << column << col1[row];
			break;
		case 1:
			col2[row].second = tableWidget->item(row, column)->text().toUtf8();
			qDebug() << "row " << row << " column= " << column << col2[row];
			break;
		case 2:
			col3[row].second = tableWidget->item(row, column)->text().toInt();
			qDebug() << "row " << row << " column= " << column << col3[row].second;
			break;
		default:
			qDebug() << "test";
	}
}
