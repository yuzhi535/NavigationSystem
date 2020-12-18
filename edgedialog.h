#ifndef EDGEDIALOG_H
#define EDGEDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QGridLayout>
#include <QPushButton>

#include "graphui.h"

class EdgeDialog : public QDialog {
Q_OBJECT
public:
	explicit EdgeDialog(GraphUi *graphUi, QWidget *parent = nullptr);

signals:

public slots:

	void on_button_1_clicked();

	void on_button_2_clicked();

	void onTableItemChanged(int row, int column);

private:
	QTableWidget *tableWidget;
	QGridLayout *layout;
	QPushButton *button1, *button2;
	GraphUi *ui;
	QVector<QPair<QString, QString>> col1;
	QVector<QPair<QString, QString>> col2;
	QVector<QPair<int, int>> col3;
};

#endif // EDGEDIALOG_H
