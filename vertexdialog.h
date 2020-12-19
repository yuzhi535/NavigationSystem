#ifndef VERTEXDIALOG_H
#define VERTEXDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QGridLayout>
#include "graphui.h"

class VertexDialog : public QDialog
{
    Q_OBJECT
public:
    explicit VertexDialog(GraphUi *graphUi, QWidget *parent = nullptr);

signals:
	void updateGraph();
public slots:
	void setPos(int row, int col);

private:
	QTableWidget* tableWidget;
	QGridLayout* layout;
	GraphUi* ui;
};

#endif // VERTEXDIALOG_H
