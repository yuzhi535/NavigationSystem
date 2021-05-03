#ifndef VERTEXDIALOG_H
#define VERTEXDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QGridLayout>
#include <QPushButton>
#include "graphui.h"

class VertexDialog : public QDialog {
Q_OBJECT
public:
	explicit VertexDialog(GraphUi *graphUi, QWidget *parent = nullptr);

    VertexDialog(const VertexDialog& another) = delete;

    ~VertexDialog();

signals:

	void updateGraph();

public slots:

	void setPos(int row, int col);

	void on_button2_clicked();

private:
	QTableWidget *tableWidget;
	QPushButton *button1;
	QPushButton *button2;
	QGridLayout *layout;
	GraphUi *ui;
    bool isValid;
};

#endif // VERTEXDIALOG_H
