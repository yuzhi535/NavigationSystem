#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
		: QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	this->setWindowTitle(tr("Navigation System"));
	this->setStyleSheet("background-color: rgba(12, 23, 34, 0.5)");

	//菜单栏待定，还没想好
	//-----------------------------------------------
	menu = new QMenu(this);
	menu->setTitle(tr("theme"));   //待定，还诶想好
	this->menuBar()->addMenu(menu);
	action1 = new QAction("dark", this);
	menu->addAction(action1);
	action2 = new QAction("light", this);
	menu->addAction(action2);

	//更换主题
	//+++++++++++++++++++++++++++++++++++++++++++++++
	connect(action1, &QAction::trigger, [&]() {});
	connect(action2, &QAction::trigger, [&]() {});
	//-----------------------------------------------

	widget = new QWidget(this);
	this->setCentralWidget(widget);
	outLayout = new QGridLayout(widget);
	outLayout->setVerticalSpacing(16);
	outLayout->setHorizontalSpacing(20);
	paintWidget = new GraphUi(this);
	outLayout->addWidget(paintWidget, 0, 0, 16, 14);
	list = new QListWidget(this);
	outLayout->addWidget(list, 12, 14, 4, 6);

	groupBox = new QGroupBox(this);
	groupBox->setTitle(tr("choice"));
	outLayout->addWidget(groupBox, 0, 14, 12, 6);
	comboBox = new QComboBox(groupBox);
	comboBox->addItem("asdf");
	inLayout = new QGridLayout(groupBox);
	inLayout->setHorizontalSpacing(8);
	inLayout->setVerticalSpacing(16);
	inLayout->addWidget(comboBox, 1, 1, 1, 2);
}

MainWindow::~MainWindow() {
	delete ui;
}

