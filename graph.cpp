//
// Created by sasuke on 2020/12/17.
//


#include "graph.h"

void Vertex::addInfo(QString context) {
	this->info = context;
}

void Vertex::setPos(QPoint pos) {
	point = pos;
}

Vertex::~Vertex() {

}

QPoint Vertex::getPos() {
	return point;
}

Graph::Graph() {
	this->arcNum = this->vexNum = 0;  //全部初始化为0
	this->arc.resize(20);
	for (int i = 0;i < 20; ++i ) {
		this->arc[i].resize(20);
	}
}

Graph::~Graph() {

}

void Graph::addVex(QString info, int x, int y) {
	this->vertexes.push_back(Vertex(info, x, y));
	qDebug() << this->vexNum << info << " x=" << x << " y=" << y;
	++this->vexNum;
}

Status Graph::addArc(int start, int end, int weight) {
	Road tmp(start, end, weight);
	return addArc(tmp);
}

Status Graph::addArc(Pair pair, int weight) {
	Road tmp(pair, weight);
	return addArc(tmp);
}

Status Graph::addArc(Road road) {
	if (this->vexNum < road.m_pair.from || this->vexNum < road.m_pair.to) {
		return ERR;
	}

	//扩容
	if (this->arc.size() < this->vexNum) {
		int size = this->arc.size();
		this->arc.resize(2 * this->vexNum);
		for (int i = 0; i < this->vexNum; ++i) {
			this->arc[i].resize(2 * this->vexNum);
		}
	}
	qDebug() << QString("from%1 to%2").arg(road.m_pair.from).arg(road.m_pair.to);
	this->arc[road.m_pair.from][road.m_pair.to].setDistance(road.weight);
	this->arc[road.m_pair.to][road.m_pair.from].setDistance(road.weight);
	this->arc[road.m_pair.from][road.m_pair.to].setPair(Pair(road.m_pair.from, road.m_pair.to));
	this->arc[road.m_pair.to][road.m_pair.from].setPair(Pair(road.m_pair.from, road.m_pair.to));
	if (road.weight != -1) {
		edge.push_back(road);
		++this->arcNum;
		qDebug() << QString("add %1->%2  %3").arg(road.m_pair.from).arg(road.m_pair.to).arg(road.weight);
	} else {
		deleteArc(road.m_pair.from, road.m_pair.to);
	}
	return OK;
}

Status Graph::deleteArc(int start, int end) {
	Pair pair(start, end);
	return deleteArc(pair);
}

Status Graph::deleteArc(Pair pair) {
	this->arc[pair.from][pair.to].setDistance(-1);
	this->arc[pair.to][pair.from].setDistance(-1);

	auto i = edge.begin();
	for (; i != edge.end() && i->m_pair != pair; ++i);
	edge.erase(i);
	return OK;
}

Status Graph::delVex(QString info) {
	int ff;  //寻找该顶点
	for (ff = this->vertexes.size() - 1; ff < this->vexNum && this->vertexes[ff].info != info; --ff);
	if (ff) {
		if (!this->vexNum) {
			return ERR;
		}

		//不能移除，，，应该置为-1 ，把后面的往前挪
		for (int i = this->vexNum - 1; i >= 0; --i) {
			if (this->arc[i].size() > ff + 1)
				this->arc[i].remove(ff);
		}
		qDebug() << "ttttttttt";
		this->arc.remove(ff);
		this->vertexes.remove(ff);   //葱顶点集合中删除

		for (auto i = edge.begin(); i != edge.end(); ++i) {
			if (i->m_pair.from == ff || i->m_pair.to == ff) {
				i = edge.erase(i);
				--i;
			}
		}
		--this->vexNum;
		return OK;
	} else {
		return ERR;
	}
}

void Graph::init_from_file(QString fileName) {
	qDebug() << "init from " << fileName;
	std::ifstream in;
	in.open(fileName.toStdString());
	if (!in.is_open()) {
		in.close();
		std::ofstream out;
		out.open(fileName.toStdString());
		out << "4 5\n"
		       "a 1 2\n"
		       "b 23 35\n"
		       "c 45 6\n"
		       "d 56 7\n"
		       "0 1 12\n"
		       "0 2 23\n"
		       "0 3 1\n"
		       "1 3 22\n"
		       "1 2 11";
		out.close();
		in.open(fileName.toStdString());
	}
	int vex_num, arc_num;
	//录入点和边
	in >> vex_num >> arc_num;
	//录入点的信息
	for (int i = 0; i < vex_num; ++i) {
		std::string info;
		int x, y;
		in >> info >> x >> y;
		this->addVex(QString(info.c_str()), x, y);
	}

	//录入边的权值  (距离)
	for (int i = 0; i < arc_num; ++i) {
		int j, k, l;  //顶点 顶点 距离
		in >> j >> k >> l;
		this->addArc(j, k, l);
	}
}

QVector<QString> &Graph::findShortestRoad(int from, int to, QVector<int> &pos) {
	ans.clear();
	pos.clear();
	this->updateGraph(1);
	QVector<int> dis(this->vexNum, 0x7f7f7f7f);
	QQueue<int> queue;
	queue.push_back(from);
	//邻接矩阵的写法
	//先把最近的初始化
	for (int i = 0; i < this->vexNum; ++i) {
		if (this->arc[from][i].getWeight() != -1) {
			dis[i] = this->arc[from][i].getWeight();
			queue.push_back(i);
		}
	}
	dis[from] = 0;

	while (!queue.empty()) {
		auto tmp = queue.front();
		queue.pop_front();
		for (int i = 0; i < this->vexNum; ++i) {
			int weight = arc[tmp][i].getWeight();
			if (weight + dis[tmp] >= 0) {
				if (dis[i] > dis[tmp] + weight) {
					dis[i] = dis[tmp] + weight;
					queue.push_back(i);
				}
			}
		}
	}

	if (dis[to] != 0x7f7f7f7f) {
		QStack<QString> stack;
		stack.push(this->vertexes[to].info);
		pos.push_back(to);
		int index(to);
		//寻找路径
		while (index != from) {
			for (index = 0; index < this->vexNum; ++index) {
				if (dis[index] == dis[to] - this->arc[index][to].getWeight()) {
					stack.push(this->vertexes[index].info);
					pos.push_back(index);
					to = index;
					if (index == from)
						break;
				}
			}
		}
		//正过来
		while (!stack.empty()) {
			ans.push_back(stack.top());
			stack.pop();
		}

	} else {
		//这里因该弹出警告框
		qDebug() << "can't find the path";
		qDebug() << "Please check your graph";
	}
	return ans;
}

void Graph::updateGraph(int group) {
	//默认为距离
	if (group == 1) {
		for (int i = 0; i < this->vexNum; ++i) {
			for (int j = 0; j < this->vexNum; ++j) {
				this->arc[i][j].setWeight(this->arc[i][j].getDistance());
			}
		}

	} else if (group == 2) {

	} else if (group == 3) {

	}
}

int Graph::getArcNum() {
	return this->arcNum;
}

int Graph::getVexNum() {
	return this->vexNum;
}

QPoint Graph::getVertex(int index) {
	return this->vertexes[index].getPos();
}

QString Graph::getInfo(int index) {
	return this->vertexes[index].info;
}

void Graph::setInfo(int index, QString info) {
	int i = 0;
	for (; i < this->vertexes.size() && this->vertexes[i].info != info; ++i);
	if (i == this->vertexes.size())
		this->vertexes[index].info = info;
	else {
		addVex(info, this->vertexes[index].getPos().x(), this->vertexes[index].getPos().y());
		delVex(getInfo(index));

	}
}

int Graph::getIndex(QString info) {
	int vex_num = this->vertexes.size();
	for (int i = 0; i < vex_num; ++i) {
		if (info == this->vertexes[i].info) {
			return i;
		}
	}
	return -1;
}

void Graph::setPos(int index, int x, int y) {
	if (index < vertexes.size()) {
		vertexes[index].setPos(QPoint(x, y));
		qDebug() << "got it";
	}
}

void Arc::setDistance(int num) {
	this->distance = num;
}

void Arc::setWeight(int num) {
	this->m_weight = num;
}

int Arc::getDistance() const {
	return this->distance;
}

int Arc::getWeight() const {
	return this->m_weight;
}

Arc::Arc() {
	distance = 0x7f7f7f7f;
}

Arc::~Arc() {

}

void Arc::setPair(Pair pair) {
	this->m_pair = pair;
}
