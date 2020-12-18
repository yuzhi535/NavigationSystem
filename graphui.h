#ifndef GRAPHUI_H
#define GRAPHUI_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPushButton>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QDialog>
#include <QMessageBox>

#include "graph.h"

class GraphUi : public QWidget {
Q_OBJECT
public:
	explicit GraphUi(QWidget *parent = nullptr);

	void destroyGraph();
	void addArc(Road road);
	int getVexNum();
	int getVexIndex (const QString& info);
	QString getVExInfo(int index);
	void setVexInfo(int index, QString info);
	QPoint getPos(int index);
	void getShortestRoad(int from, int to);
    void editVertex(QString info, int x, int y);
    const QVector<Road>& getEdge () const;

protected:
	void mouseReleaseEvent(QMouseEvent *event) override;

	void paintEvent(QPaintEvent *event) override;


signals:
	void updateList(QVector<QString> path);

public slots:


private:
	Graph graph;
	QPoint lastPos;
	QVector<Pair> specialVertex;

};

#endif // GRAPHUI_H
