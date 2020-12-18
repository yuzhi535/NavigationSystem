#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QPoint>
#include <QComboBox>
#include <QGroupBox>
#include <QPushButton>
#include <QListWidget>
#include <QMenu>
#include <QAction>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStringList>
#include <QAbstractItemView>
#include <QKeySequence>

#include "graphui.h"

#if DEV

#include <QSound>

#endif

QT_BEGIN_NAMESPACE
namespace Ui {
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);

	~MainWindow();

public slots:

	// 更换主题
	void action1_triggered();

	void action2_triggered();

	//添加节点 边 删除等
	void action3_triggered();

	void action4_triggered();

	//下拉框
	void comboBox1_triggered(int index);

	void comboBox2_triggered(int index);

	//是否加上人群
	void onCheckBox1_stateChanged();

	//是否加上天气
	void onCheckBox2_stateChanged();

	//最短路径的计算
	void on_button_clicked();

	void updateListWidget(QVector<QString> path);


private:
	Ui::MainWindow *ui;
	QWidget *widget;   //main widget
	QGridLayout *outLayout, *inLayout;
	GraphUi *paintWidget;
	QListWidget *list;
	QGroupBox *groupBox;
	QComboBox *comboBox1;  //起点
	QComboBox *comboBox2;  //终点
	QLabel *label1;  //起点
	QLabel *label2;  //终点
	QCheckBox *checkBox1;   //check group
	QCheckBox *checkBox2;   //check weather
	QTableWidget *tableWidget;  //表格
	QPushButton *button;   //搜索

	//菜单
	QMenu *view;   //视图
	QAction *action1;   //切换主题
	QAction *action2;
	QMenu *edit;  //编辑节点和道路
	QAction *action3;  //节点
	QAction *action4;  //道路



	// the shortest road
	QPoint startPos, lastPos;
	int index1, index2;

};

#endif // MAINWINDOW_H
