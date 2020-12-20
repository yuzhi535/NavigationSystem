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

	bool findVex(QString info);

	void setPos(const QString &info, int x, int y);

	void addArc(Road road);

	void delArc(Pair pair);

	void addVex(QString info);

	int getVexNum();

	int getVexIndex(const QString &info);

	QString getVExInfo(int index);

    void setVexInfo(int index1, const QString& tip, const QString& info, int w);

	QPoint getPos(int index);

	void getShortestRoad(int from, int to);

	void editVertex(QString info, int x, int y);

	const QVector<Road> &getEdge() const;

	void setGroup1(int group);

	void setGroup2(int group);

	QColor color[9] = {
			QColor(25, 154, 242), QColor(243, 39, 19), QColor(21, 21, 20),
			QColor(216, 56, 237), QColor(237, 215, 56), QColor(66, 66, 63),
			QColor( 255, 253, 161 ), QColor(208, 250, 239), QColor(238, 131, 178)};
	enum ArcColor {
		TARGET = 0, GROUP, NORMAL
	};

	enum VexColor {
		AIM = 3, BY, IRRELEVANT
	};

	enum BackGroudColor {
		PAINT = 6, BG, TEXT
	};

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
	int isGroup1;
	int isGroup2;


};

#endif // GRAPHUI_H
