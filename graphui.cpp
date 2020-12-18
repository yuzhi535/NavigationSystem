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

void
GraphUi::mouseReleaseEvent(QMouseEvent *event) {
	qDebug() << "currPos=" << event->pos();
	update();
}

void
GraphUi::mousePressEvent(QMouseEvent *event) {
	qDebug() << "press";
}

/**
 * @brief 背景色
 * @brief 边框
 * @brief 顶点
 * @brief 边
 * @brief 顶点名字
 * @param event
 */
void
GraphUi::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(QColor(56, 116, 237)));
	painter.drawRect(rect());

	qDebug() << graph.edge.size();
	auto vex_num = graph.getVexNum();
	for (auto i = 0; i != vex_num; ++i) {
		QPen pen;
		pen.setWidth(5);
		pen.setColor(Qt::red);
		painter.setPen(pen);
		QPoint point = graph.getVertex(i);
		qDebug() << point;
		painter.drawEllipse(point, 4, 4);
		pen.setColor(Qt::green);
		pen.setWidth(3);
		painter.setPen(pen);
		painter.drawText(QPoint(point.x() + 3, point.y() - 8), graph.getInfo(i));
	}
	for (auto i = graph.edge.begin(); i != graph.edge.end(); ++i) {
		QPen pen;
		pen.setWidth(3);
		pen.setColor(Qt::yellow);
		painter.setPen(pen);
		QPoint point1 = graph.getVertex(i->m_pair.from), point2 = graph.getVertex(i->m_pair.to);
		painter.drawLine(point1, point2);
	}
}

int GraphUi::getVexNum() {
	return graph.getVexNum();
}

QString GraphUi::getVExInfo(int index) {
	return graph.getInfo(index);
}
