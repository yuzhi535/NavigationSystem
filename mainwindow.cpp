#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    widget = new QWidget(this);
    this->setCentralWidget(widget);
    layout = new QGridLayout(widget);
    layout->setVerticalSpacing(30);
    layout->setHorizontalSpacing(30);
    paintWidget = new GraphUi(this);
    layout->addWidget(paintWidget, 10, 10, 10, 10);
    list = new QListWidget(this);
    layout->addWidget(list, 20, 20, 5, 5);


    qDebug() << layout->verticalSpacing();
}

MainWindow::~MainWindow()
{
    delete ui;
}

