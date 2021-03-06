#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
		: QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	index1 = index2 = 0;

	this->setWindowTitle(tr("Navigation System"));
	this->setStyleSheet("background-color: white; color:black"); //设置样式
	//设置最小尺寸
	this->setMinimumHeight(1000);
	this->setMinimumWidth(1200);

	//菜单栏待
	edit = new QMenu(this);
	edit->setTitle(tr("edit"));
	this->menuBar()->addMenu(edit);
	action1 = new QAction(tr("change vertexes' position"), this);
	action2 = new QAction(tr("change paths and vertexes"), this);
	edit->addAction(action1);
	edit->addAction(action2);


	// 信号槽操作
	connect(action1, &QAction::triggered, this, &MainWindow::action1_triggered);
	connect(action2, &QAction::triggered, this, &MainWindow::action2_triggered);

	// 针对整体进行设计
	widget = new QWidget(this);
	this->setCentralWidget(widget);
	outLayout = new QGridLayout(widget);
	outLayout->setVerticalSpacing(16);
	outLayout->setHorizontalSpacing(20);
	paintWidget = new GraphUi(this);
	paintWidget->setStatusTip(tr("graph"));
	outLayout->addWidget(paintWidget, 0, 0, 16, 14);
	list = new QTableWidget(this);
	list->setRowCount(12);
	list->setColumnCount(2);
	QStringList listHeader;
	listHeader << "from" << "to";
	list->setHorizontalHeaderLabels(listHeader);
	list->setStatusTip(tr("output"));
	list->setEditTriggers(QAbstractItemView::NoEditTriggers);  //禁止编辑
	list->setStyleSheet("color:black; background-color: white"); //设置样式
	outLayout->addWidget(list, 12, 14, 4, 6);

	groupBox = new QGroupBox(this);         //分组小组件
	groupBox->setTitle(tr("choice"));
	groupBox->setStyleSheet("color:black; background-color: white"); //设置样式
	outLayout->addWidget(groupBox, 0, 14, 12, 6);

	// 针对右边groupBox进行设计
	inLayout = new QGridLayout(groupBox);
	inLayout->setHorizontalSpacing(20);
	inLayout->setVerticalSpacing(8);
	inLayout->setColumnMinimumWidth(16, 1);
	inLayout->setRowMinimumHeight(8, 1);
//	inLayout->setColumnStretch(16, 2);
//	inLayout->setRowStretch(8, 2);

	// groupBox里面的组件
	label1 = new QLabel(groupBox);
	label1->setText(tr("beginning"));
	label1->setStyleSheet("color:black");  //设置样式
	inLayout->addWidget(label1, 0, 2, 1, 2);
	comboBox1 = new QComboBox(groupBox);
	comboBox1->setStatusTip(tr("choose the beginning"));   //状态栏显示提示
	inLayout->addWidget(comboBox1, 0, 4, 1, 4);

	label2 = new QLabel(groupBox);
	label2->setText(tr("ending"));
	label2->setStyleSheet("color:black");   //设置样式
	inLayout->addWidget(label2, 2, 2, 1, 2);
	comboBox2 = new QComboBox(groupBox);
	comboBox2->setStatusTip(tr("choose the ending"));   //状态栏显示提示
	inLayout->addWidget(comboBox2, 2, 4, 1, 4);

	connect(comboBox1, SIGNAL(activated(int)), this, SLOT(comboBox1_triggered(int)));
	connect(comboBox2, SIGNAL(activated(int)), this, SLOT(comboBox2_triggered(int)));

	//提取各个顶点的信息
	int vex_num = paintWidget->getVexNum();
	for (int i = 0; i < vex_num; ++i) {
		QString info = paintWidget->getVExInfo(i);
		comboBox1->addItem(info);
	}
	for (int i = 0; i < vex_num; ++i) {
		QString info = paintWidget->getVExInfo(i);
		comboBox2->addItem(info);
	}

	checkBox1 = new QCheckBox(groupBox);
	checkBox1->setText(tr("people"));
	checkBox1->setStatusTip(tr("choice"));               //状态栏显示提示
	checkBox1->setStyleSheet("background-color: white; color: black");
	inLayout->addWidget(checkBox1, 4, 2, 1, 2);

	checkBox2 = new QCheckBox(groupBox);
	checkBox2->setText(tr("car"));
	checkBox2->setStatusTip(tr("choice"));
	checkBox2->setStyleSheet("background-color: white; color: black");
	inLayout->addWidget(checkBox2, 6, 2, 1, 2);

	//信号槽
	connect(checkBox1, &QCheckBox::stateChanged,
	        this, &MainWindow::onCheckBox1_stateChanged);
	connect(checkBox2, &QCheckBox::stateChanged,
	        this, &MainWindow::onCheckBox2_stateChanged);

	// 按钮
	button = new QPushButton(groupBox);
	button->setText(tr("confirm"));
	button->setStatusTip(tr("confirm to find the shortest road"));  //设置状态栏提示
	button->setShortcut(QKeySequence::fromString("return"));   //设置快捷键
	button->setStyleSheet(
			"background-color:white; color: black; selection-color: white; selection-background-color: blue;");
	inLayout->addWidget(button, 8, 4, 2, 3);   //加入group

	//信号槽，注意最短路径返回值
	connect(button, &QPushButton::clicked, this, &MainWindow::on_button_clicked);

	//表格
	tableWidget = new QTableWidget(groupBox);
	tableWidget->setStatusTip(tr("vertex set"));
	tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //禁止编辑
	tableWidget->setStyleSheet("background-color: white; color: black");
	inLayout->addWidget(tableWidget, 10, 2, -1, 6);
	tableWidget->setRowCount(vex_num * 2);
	tableWidget->setColumnCount(2);
	QStringList header;
	header << "Vertex" << "Description";      //设置标题
	tableWidget->setHorizontalHeaderLabels(header);
	for (int i = 0; i < vex_num; ++i) {
		tableWidget->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(i)));
		tableWidget->setItem(i, 1, new QTableWidgetItem(paintWidget->getVExInfo(i)));
	}

	dialog1 = nullptr;
	dialog2 = nullptr;

	//更新列表的信号槽
	connect(paintWidget, SIGNAL(updateList(QVector<QString>)), this,
	        SLOT(updateListWidget(QVector<QString>)));
	connect(this, &MainWindow::updateGraph, [&]() { paintWidget->update(); });
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::comboBox1_triggered(int index) {
	startPos = paintWidget->getPos(index);
	index1 = index;
}

// 编辑道路
void MainWindow::action2_triggered() {
	dialog1 = new EdgeDialog(paintWidget, this);
	connect(dialog1, SIGNAL(updateGraph()), this, SLOT(updateWidget()));
	dialog1->show();
}

// 编辑顶点
void MainWindow::action1_triggered() {
	dialog2 = new VertexDialog(paintWidget, this);
	connect(dialog2, SIGNAL(updateGraph()), this, SLOT(updateWidget()));
	dialog2->show();
}

void MainWindow::onCheckBox1_stateChanged() {
	auto result = checkBox1->isChecked();
	if (result)  //因为人群密度
		paintWidget->setGroup1(2);
	else
		paintWidget->setGroup1(1);
}

void MainWindow::onCheckBox2_stateChanged() {
	auto result = checkBox2->isChecked();
	if (result)  //因为车辆密度
		paintWidget->setGroup2(2);
	else
		paintWidget->setGroup2(1);
}

void MainWindow::on_button_clicked() {
	if (lastPos != startPos) {
		paintWidget->getShortestRoad(index1, index2);

	} else {
		QMessageBox::information(this, tr("info"), QString("<h2>起点和终点相同！</h2>"));
	}
}

void MainWindow::comboBox2_triggered(int index) {
	lastPos = paintWidget->getPos(index);
	index2 = index;
}

void MainWindow::updateListWidget(QVector<QString> path) {
	list->clearContents();
	for (int i = 0; i < path.size() - 1; ++i) {
		list->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(path[i])));
		list->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(path[i + 1])));
	}
}

void MainWindow::updateWidget() {
	this->tableWidget->clearContents();
	int vex_num = this->paintWidget->getVexNum();
	comboBox1->clear();
	comboBox2->clear();
	for (int i = 0; i < vex_num; ++i) {
		tableWidget->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(i)));
		tableWidget->setItem(i, 1, new QTableWidgetItem(paintWidget->getVExInfo(i)));
		comboBox1->addItem(paintWidget->getVExInfo(i));
		comboBox2->addItem(paintWidget->getVExInfo(i));
	}
}

