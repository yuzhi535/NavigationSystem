#include "graphui.h"

/**
 * @brief 初始化图   OK
 * @brief 完善绘图
 * @brief 完善颜色
 * @brief 最好加上鼠标移动顶点
 * @brief 最好加上添加顶点和边，这个功能需要信号槽传递了
 * @param parent
 */
GraphUi::GraphUi(QWidget *parent)
		: QWidget(parent) {
	graph.init_from_file();
}

void GraphUi::mouseReleaseEvent(QMouseEvent *event) {
	update();
}

/**
 * @brief 背景色
 * @brief 边框
 * @brief 顶点
 * @brief 边
 * @brief 顶点名字
 * @param event
 */
void GraphUi::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(QColor(56, 116, 237)));
	painter.drawRect(rect());

	QFont font;
	font.setPointSize(15);
	font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
	painter.setFont(font);

	auto vex_num = graph.getVexNum();
	QPen pen;
	for (auto i = 0; i != vex_num; ++i) {
		pen.setWidth(5);
		pen.setColor(Qt::red);
		painter.setPen(pen);
		QPoint point = graph.getVertex(i);
		painter.drawEllipse(point, 4, 4);
		pen.setColor(Qt::green);
		pen.setWidth(3);
		painter.setPen(pen);
		painter.drawText(QPoint(point.x() + 3, point.y() - 8), graph.getInfo(i));
	}
	for (auto i = graph.edge.begin(); i != graph.edge.end(); ++i) {
		QPoint point1 = graph.getVertex(i->m_pair.from), point2 = graph.getVertex(i->m_pair.to);
		if (!specialVertex.contains(i->m_pair)) {
			pen.setWidth(3);
			pen.setColor(Qt::yellow);
			painter.setPen(pen);
			painter.drawLine(point1, point2);

			font.setPointSize(12);
			pen.setWidth(5);
			pen.setColor(Qt::darkRed);
			pen.setStyle(Qt::SolidLine);
			painter.setPen(pen);
		}
		painter.drawText((point2.x() + point1.x()) / 2, (point1.y() + point2.y()) / 2, QString("%1").arg(i->weight));;
	}
	for (int i = 0; i < specialVertex.size(); ++i) {
		QPoint pos1, pos2;
		pos1.setX(this->getPos(specialVertex[i].from).x());
		pos1.setY(this->getPos(specialVertex[i].from).y());
		pos2.setX(this->getPos(specialVertex[i].to).x());
		pos2.setY(this->getPos(specialVertex[i].to).y());

		pen.setWidth(3);
		pen.setColor(Qt::darkBlue);
		painter.setPen(pen);
		painter.drawLine(pos1, pos2);
	}
}

int GraphUi::getVexNum() {
	return graph.getVexNum();
}

QString GraphUi::getVExInfo(int index) {
	return graph.getInfo(index);
}

QPoint GraphUi::getPos(int index) {
	return graph.getVertex(index);
}

void GraphUi::getShortestRoad(int from, int to) {
	specialVertex.clear();   //清空原来的最短路径
	QVector<int> verteces;
	QVector<QString> &orderedRoad = graph.findShortestRoad(from, to, verteces);

	if (!orderedRoad.empty()) {
		//加载顶点对
		for (int i = 0; i < verteces.size() - 1; ++i) {
			Pair pair(verteces[i], verteces[i + 1]);
			specialVertex.push_back(pair);
		}
		update();
	}
	emit updateList(orderedRoad);
}

void GraphUi::addVertex(QString info, int x, int y) {
	graph.addVex(info, x, y);
}
