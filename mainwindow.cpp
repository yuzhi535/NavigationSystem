#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
		: QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	this->setWindowTitle(tr("Navigation System"));
	this->setStyleSheet("background-color: rgba(12, 23, 34, 0.5)");
	//设置最小尺寸
	this->setMinimumHeight(720);
	this->setMinimumWidth(960);

	//菜单栏待定，还没想好
	//-----------------------------------------------
	view = new QMenu(this);
	view->setTitle(tr("theme"));   //待定，还诶想好
	this->menuBar()->addMenu(view);
	action1 = new QAction("dark", this);
	view->addAction(action1);
	action2 = new QAction("light", this);
	view->addAction(action2);

	edit = new QMenu(this);
	edit->setTitle(tr("edit"));
	this->menuBar()->addMenu(edit);
	action3 = new QAction(tr("add vertex"), this);
	action4 = new QAction(tr("add path"), this);
	edit->addAction(action3);
	edit->addAction(action4);

	// 信号槽操作
	connect(action3, &QAction::triggered, [&]() { qDebug() << "add vertex"; });
	connect(action4, &QAction::triggered, [&]() { qDebug() << "add path"; });

	//更换主题   未完待续
	//+++++++++++++++++++++++++++++++++++++++++++++++
	connect(action1, &QAction::trigger, [&]() {});
	connect(action2, &QAction::trigger, [&]() {});
	//-----------------------------------------------

	// 针对整体进行设计
	widget = new QWidget(this);
	this->setCentralWidget(widget);
	outLayout = new QGridLayout(widget);
	outLayout->setVerticalSpacing(16);
	outLayout->setHorizontalSpacing(20);
	paintWidget = new GraphUi(this);
	paintWidget->setStatusTip(tr("graph"));
	outLayout->addWidget(paintWidget, 0, 0, 16, 14);
	list = new QListWidget(this);
//	list->setWindowTitle(tr("the shortest path output"));
	list->setStatusTip(tr("output"));
	outLayout->addWidget(list, 12, 14, 4, 6);
	groupBox = new QGroupBox(this);         //分组小组件
	groupBox->setTitle(tr("choice"));
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
	inLayout->addWidget(label1, 0, 2, 1, 2);
	comboBox1 = new QComboBox(groupBox);
	comboBox1->setStatusTip(tr("choose the beginning"));   //状态栏显示提示
	inLayout->addWidget(comboBox1, 0, 4, 1, 4);

	label2 = new QLabel(groupBox);
	label2->setText(tr("ending"));
	inLayout->addWidget(label2, 2, 2, 1, 2);
	comboBox2 = new QComboBox(groupBox);
	comboBox2->setStatusTip(tr("choose the ending"));   //状态栏显示提示
	inLayout->addWidget(comboBox2, 2, 4, 1, 4);

	connect(comboBox1, &QComboBox::currentIndexChanged, [&]() { qDebug() << comboBox1->currentIndex(); });

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
	inLayout->addWidget(checkBox1, 4, 2, 1, 2);

	checkBox2 = new QCheckBox(groupBox);
	checkBox2->setText(tr("weather"));
	checkBox2->setStatusTip(tr("choice"));
	inLayout->addWidget(checkBox2, 6, 2, 1, 2);

	//信号槽，未完待续
	//-----------------------------------------------------
	connect(checkBox1, &QCheckBox::stateChanged,
	        [&]() { qDebug() << "checkbox1 state changed" << checkBox1->isChecked(); });
	connect(checkBox2, &QCheckBox::stateChanged,
	        [&]() { qDebug() << "checkbox2 state changed" << checkBox2->isChecked(); });
	//-----------------------------------------------------

	// 按钮
	button = new QPushButton(groupBox);
	button->setText(tr("confirm"));
	button->setStatusTip(tr("confirm to find the shortest road"));  //设置状态栏提示
	button->setShortcut(QKeySequence::fromString("return"));   //设置快捷键
	inLayout->addWidget(button, 8, 4, 2, 3);   //加入group

	//信号槽，注意最短路径返回值
	connect(button, &QPushButton::clicked, [&]() { qDebug() << "button"; });

	//表格
	tableWidget = new QTableWidget(groupBox);
	tableWidget->setStatusTip(tr("vertex set"));
	QStringList header;
	header << "vertex" << "Description";
	tableWidget->setHorizontalHeaderLabels(header);
	tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  //禁止编辑
	inLayout->addWidget(tableWidget, 10, 2, -1, 6);
	tableWidget->setRowCount(vex_num * 2);
	tableWidget->setColumnCount(2);
	for (int i = 0; i < vex_num; ++i) {
		tableWidget->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(i)));
		tableWidget->setItem(i, 1, new QTableWidgetItem(paintWidget->getVExInfo(i)));
	}

	//test
	//________________________________
//	qDebug() << "row " << inLayout->rowCount() << "column" << inLayout->columnCount();
	//________________________________

}

MainWindow::~MainWindow() {
	delete ui;
}

