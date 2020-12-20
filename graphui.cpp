#include "graphui.h"

/**
 * @brief 初始化图   OK
 * @brief 完善绘图   OK
 * @brief 完善颜色   OK
 * @brief 最好加上鼠标移动顶点
 * @brief 最好加上添加顶点和边，这个功能需要信号槽传递了   OK
 * @param parent
 */
GraphUi::GraphUi(QWidget *parent)
		: QWidget(parent) {
	graph.init_from_file();
	isGroup1 = isGroup2 = 1;
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
	painter.setBrush(QBrush(color[PAINT]));
	painter.drawRect(rect());

	QFont font;
	font.setPointSize(15);
	font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
	painter.setFont(font);

	auto vex_num = graph.getVexNum();
	QPen pen;
	//点
	for (auto i = 0; i != vex_num; ++i) {
		pen.setWidth(5);
		pen.setColor(color[NORMAL]);
		painter.setPen(pen);
		QPoint point = graph.getVertex(i);
		painter.drawEllipse(point, 4, 4);

		pen.setColor(color[IRRELEVANT]);
		pen.setWidth(3);
		painter.setPen(pen);
		painter.drawText(QPoint(point.x() + 3, point.y() - 8), graph.getInfo(i));
	}
	//边
	for (auto i = graph.edge.begin(); i != graph.edge.end(); ++i) {
		QPoint point1 = graph.getVertex(i->m_pair.from), point2 = graph.getVertex(i->m_pair.to);
		if (!specialVertex.contains(i->m_pair)) {
			pen.setWidth(3);
			if (i->weight < 200)
				pen.setColor(color[NORMAL]);
			else {
				pen.setWidth(5);
				pen.setColor(color[GROUP]);
			}
			painter.setPen(pen);
			painter.drawLine(point1, point2);
		}
		font.setPointSize(12);
		pen.setWidth(5);
		pen.setColor(color[TEXT]);
		pen.setStyle(Qt::SolidLine);
		painter.setPen(pen);
		painter.drawText((point2.x() + point1.x()) / 2, (point1.y() + point2.y()) / 2, QString("%1").arg(i->weight));;
	}
	//标记最短路径的边
	for (auto &i : specialVertex) {
		QPoint pos1, pos2;
		pos1.setX(this->getPos(i.from).x());
		pos1.setY(this->getPos(i.from).y());
		pos2.setX(this->getPos(i.to).x());
		pos2.setY(this->getPos(i.to).y());

		pen.setWidth(3);
		pen.setColor(color[TARGET]);
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
	graph.updateGraph(isGroup1 | isGroup2);
	QVector<QString> &orderedRoad = graph.findShortestRoad(from, to, verteces);

	if (!orderedRoad.empty()) {
		//加载顶点对
		for (int i = 0; i < verteces.size() - 1; ++i) {
			Pair pair(verteces[i], verteces[i + 1]);
			specialVertex.push_back(pair);
		}
		update();
	} else {
		QMessageBox::warning(this, tr("warning"),
		                     tr("no path from %1 to %2").arg(this->graph.getInfo(from)).arg(this->graph.getInfo(to)));
	}
	emit updateList(orderedRoad);
}

void GraphUi::editVertex(QString info, int x, int y) {
	int vex_num = graph.getVexNum();
	//不能添加重复节点
	for (int i = 0; i < vex_num; ++i) {
		if (graph.getInfo(i) == info)
			return;
	}
	graph.addVex(info, x, y);
}

const QVector<Road> &GraphUi::getEdge() const {
	return graph.edge;
}

void GraphUi::destroyGraph() {
	for (int i = graph.getVexNum() - 1; i >= 0; --i) {
		graph.delVex(this->getVExInfo(i));
	}
}

void GraphUi::addArc(Road road) {
	qDebug() << QString("add %1->%2  %3").arg(road.m_pair.from).arg(road.m_pair.to).arg(road.weight);
	graph.addArc(road);
}

int GraphUi::getVexIndex(const QString &info) {
	for (int i = 0; i < graph.getVexNum(); ++i) {
		if (graph.getInfo(i) == info) {
			qDebug() << "info = " << info;
			return i;
		}
	}
	return -1;
}

void GraphUi::setVexInfo(int index1, const QString &tip, const QString &info, int w) {
	int i = 0, j = 0, vex_num = this->graph.getVexNum();
	for (; i < vex_num && this->graph.getInfo(i) != info; ++i);
	for (; j < vex_num && this->graph.getInfo(j) != tip; ++j);
	if (i < vex_num && j < vex_num) {  //如果有这个点
		//删除原来的边，增加新的边
		Pair pair(this->graph.edge[index1].m_pair.from, this->graph.edge[index1].m_pair.to);
		this->graph.deleteArc(this->graph.edge[index1].m_pair);
		this->graph.addArc(i, j, w);
	} else {
		qDebug() << QString("cannot find this vertex %1").arg(info);
	}
}

void GraphUi::addVex(QString info) {
	//这里先默认添加的位置，等到编辑顶点的时候进行改动
	graph.addVex(info, 0, 0);
}

bool GraphUi::findVex(QString info) {
	int vex_num = graph.getVexNum();
	for (int i = 0; i < vex_num; ++i) {
		if (graph.getIndex(info) != -1) {
			return true;
		}
	}
	return false;
}

void GraphUi::setPos(const QString &info, int x, int y) {
	int index;
	for (index = 0; index < graph.getVexNum(); ++index) {
		if (info == graph.getInfo(index)) {
			graph.setPos(index, x, y);
			break;
		}
	}
}

void GraphUi::setGroup1(int group) {
	isGroup1 = group;
	qDebug() << QString("isGroup=%1").arg(isGroup1);
}

void GraphUi::setGroup2(int group) {
	isGroup2 = group;
	qDebug() << QString("isGroup=%1").arg(isGroup2);
}

void GraphUi::delArc(Pair pair) {
	graph.deleteArc(pair);
	for (int i = 0; i < graph.edge.size(); ++i) {
		if (graph.edge[i].m_pair == pair) {
			graph.edge.remove(i);
			break;
		}
		if (graph.edge[i].m_pair == Pair(pair.to, pair.from)) {
			graph.edge.remove(i);
			break;
		}
	}
}
