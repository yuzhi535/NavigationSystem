//
// Created by sasuke on 2020/12/17.
//

#include <QTime>
#include <QtGlobal>
#include <queue>

#include "graph.h"

#define FAST 1

void Vertex::setPos(QPoint pos) {
	point = pos;
}

QPoint Vertex::getPos() const {
	return point;
}

Graph::Graph() {
	this->arcNum = this->vexNum = 0;//全部初始化为0
	this->arc.resize(20);
	for (int i = 0; i < 20; ++i) {
		this->arc[i].resize(20);
	}
}

Graph::~Graph() {
	std::fstream ff;
	ff.open("pre.txt", std::ios::out);
	ff << this->vexNum  << ' '<< this->edge.size() << '\n';
	for (int i = 0; i < this->vexNum; ++i) {
		ff << this->vertexes[i].info.toStdString() << ' ' << this->vertexes[i].getPos().x() << ' ' << this->vertexes[i].getPos().y() << '\n';
	}
	for (int i = 0; i < this->edge.size(); ++i) {
		ff << this->edge[i].m_pair.from << ' '<< this->edge[i].m_pair.to << ' ' << this->edge[i].weight << '\n';
	}
	ff.close();
}

void Graph::addVex(const QString &info, int x, int y) {
	if (x && y) {
		this->vertexes.push_back(Vertex(info, x, y));
		qDebug() << this->vexNum << info << " x=" << x << " y=" << y;
		++this->vexNum;
	} else {
		int index;
		for (index = 0; index < vertexes.size() && this->vertexes[index].info != info; ++index) {
			qDebug() << QString("info=%1   vertexes info=%2").arg(info).arg(this->vertexes[index].info);
		}
		if (index == this->vertexes.size()) {
			this->vertexes.push_back(Vertex(info, x, y));
			qDebug() << this->vexNum << info << " x=" << x << " y=" << y;
			++this->vexNum;
		}
	}
}

Status Graph::addArc(int start, int end, int weight) {
	Road tmp(start, end, weight);
	return addArc(tmp);
}

Status Graph::addArc(const Road &road) {
	if (this->vexNum < road.m_pair.from || this->vexNum < road.m_pair.to) {
		return ERR;
	}

	//扩容
	if (this->arc.size() < this->vexNum) {
		this->arc.resize(2 * this->vexNum);
		for (int i = 0; i < this->vexNum; ++i) {
			this->arc[i].resize(2 * this->vexNum);
		}
	}
	qDebug() << QString("from%1 to%2").arg(road.m_pair.from).arg(road.m_pair.to);
	int flag = 1;
	//初始化的权重
	if (this->arc[road.m_pair.from][road.m_pair.to].getDistance() == 0x7f7f7f7f) {
		this->arc[road.m_pair.from][road.m_pair.to].setDistance(road.weight);
		this->arc[road.m_pair.to][road.m_pair.from].setDistance(road.weight);
		if (road.weight != 0) {
			edge.push_back(road);
			++this->arcNum;
			qDebug() << QString("add %1->%2  %3").arg(road.m_pair.from).arg(road.m_pair.to).arg(road.weight);
		}
	} else {
		if (this->arc[road.m_pair.from][road.m_pair.to].getDistance() != 0) {
			flag = 0;
		}
		this->arc[road.m_pair.from][road.m_pair.to].setDistance(road.weight);
		this->arc[road.m_pair.to][road.m_pair.from].setDistance(road.weight);
		if (road.weight != 0 && flag) {
			edge.push_back(road);
			++this->arcNum;
			qDebug() << QString("add %1->%2  %3").arg(road.m_pair.from).arg(road.m_pair.to).arg(road.weight);
		} else if (!flag) {
			int i(road.m_pair.from), j(road.m_pair.to);
			Pair pair(i, j);
			int result = -1;
			for (int k = 0; k < this->edge.size(); ++k) {
				if (i == j)
					continue;
				if (this->edge[k].m_pair == pair) {
					result = k;
					break;
				}
				if (this->edge[k].m_pair == Pair(j, i)) {
					result = k;
					break;
				}
			}
			if (result != -1) {
				edge[result].weight = road.weight;
			}

		} else {
			deleteArc(road.m_pair.from, road.m_pair.to);
		}
	}
	return OK;
}

Status Graph::deleteArc(int start, int end) {
	Pair pair(start, end);
	return deleteArc(pair);
}

Status Graph::deleteArc(const Pair &pair) {
	this->arc[pair.from][pair.to].setDistance(0x7f7f7f7f);
	this->arc[pair.to][pair.from].setDistance(0x7f7f7f7f);

	auto i = edge.begin();
	for (; i != edge.end() && i->m_pair != pair; ++i)
		;
	edge.erase(i);
	return OK;
}

Status Graph::delVex(const QString &info) {
	int ff;//寻找该顶点
	for (ff = 0; ff < this->vexNum && this->vertexes[ff < this->vexNum ? ff : 0].info != info; ++ff)
		;
	if (ff < this->vexNum) {
		if (!this->vexNum) {
			return ERR;
		}
		//不能移除，，，应该置为-1 ，把后面的往前挪
		for (int i = this->edge.size() - 1; i >= 0; --i) {
			int from = this->edge[i].m_pair.from;
			int to = this->edge[i].m_pair.to;
			if (ff == from) {
				this->deleteArc(from, to);
				for (int k = 0; k < this->arc.size(); ++k) {
					for (int l = ff; l < this->vertexes.size() - 1; ++l) {
						this->arc[k][l].setDistance(this->arc[k][l + 1].getDistance());
					}
				}
				for (int k = ff; k < this->vertexes.size() - 1; ++k) {
					for (int l = 0; l < this->vertexes.size(); ++l) {
						this->arc[k][l].setDistance(this->arc[k + 1][l].getDistance());
					}
				}
			} else if (ff == to) {
				this->deleteArc(from, to);
				for (int k = 0; k < this->vertexes.size(); ++k) {
					for (int l = ff; l < this->vertexes.size() - 1; ++l) {
						this->arc[k][l].setDistance(this->arc[k][l + 1].getDistance());
					}
				}
				for (int k = ff; k < this->vertexes.size() - 1; ++k) {
					for (int l = 0; l < this->vertexes.size(); ++l) {
						this->arc[k][l].setDistance(this->arc[k + 1][l].getDistance());
					}
				}
			}
		}
		this->vertexes.remove(ff);//从顶点集合中删除

		for (int index = 0; index < edge.size(); ++index) {
			int v1 = edge[index].m_pair.from;
			int v2 = edge[index].m_pair.to;
			if (v1 && v1 >= ff) {
				--edge[index].m_pair.from;
			}
			if (v2 && v2 >= ff) {
				--edge[index].m_pair.to;
			}
		}
		--this->vexNum;
		return OK;
	} else {
		return ERR;
	}
}

/**
 * @brief initialize from a file
 * @mark 柳园 荷园 菊园 松园 中心体育馆 南核 中核 北核 图书馆 柳园餐厅 荷园餐厅 菊园餐厅 松园餐厅 南门 东门 北门
 *       
 */
void Graph::init_from_file(const QString &fileName) {
	qDebug() << "init from " << fileName;
	std::ifstream in;
	in.open(fileName.toStdString());
	if (!in.is_open()) {
		in.close();
		std::ofstream out;
		out.open(fileName.toStdString());
		out << "16 20\n"
		       "柳园 200 700\n"      //0
		       "荷园 200 550\n"      //1
		       "菊园 200 388\n"      //2
		       "松园 200 222\n"      //3
		       "中心体育馆 150 455\n"//4
		       "南核 370 600\n"      //5
		       "中核 370 450\n"      //6
		       "北核 370 270\n"      //7
		       "图书馆 555 450\n"    //8
		       "柳园餐厅 11 690\n"   //9
		       "荷园餐厅 11 500\n"   //10
		       "菊园餐厅 11 370\n"   //11
		       "松园餐厅 11 210\n"   //12
		       "南门 280 750\n"      //13
		       "东门 760 444\n"      //14
		       "北门 259 111\n"      //15
		       "0 1 12\n"            //liu he
		       "1 2 24\n"            // he ju
		       "2 3 12\n"            //ju song
		       "1 4 12\n"            //he zhongxin
		       "2 4 12\n"            //ju zhongxin
		       "4 5 35\n"            //zhongxin nanhe
		       "4 6 25\n"            //zhongxin zhonghe
		       "4 7 35\n"            //zhongxin beihe
		       "5 8 30\n"            //nanhe tushu
		       "6 8 20\n"            //zhonghe tushu
		       "7 8 30\n"            //beihe tushu
		       "0 9 10\n"            //liu canting
		       "1 10 10\n"           //he canting
		       "2 11 10\n"           //ju canting
		       "3 12 10\n"           //song canting
		       "0 13 14\n"           //liu nan
		       "8 14 9\n"            //tushu dongmen
		       "3 15 20\n"           //song beimen
		       "5 6 10\n"            //nanhe zhonghe
		       "6 7 10\n";           //zhonghe beihe
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
		int j, k, l;//顶点 顶点 距离
		in >> j >> k >> l;
		this->addArc(j, k, l);
	}
}

/**
  * @brief find the shortest road
  * @note use the priority queue to accelerate it
  * 
  */
QVector<QString> &Graph::findShortestRoad(int from, int to, QVector<int> &path) {
	ans.clear();
	path.clear();
	QVector<int> dis(this->vexNum, 0x7f7f7f7f);
#ifndef FAST
	std::queue<int> queue;
	queue.push(from);
	//邻接矩阵的写法
	//先把最近的初始化
	for (int i = 0; i < this->vexNum; ++i) {
		if (this->arc[from][i].getWeight() != -1) {
			dis[i] = this->arc[from][i].getWeight();
			queue.push(i);
		}
	}
	dis[from] = 0;

	while (!queue.empty()) {
		auto tmp = queue.top();
		queue.pop();
		for (int i = 0; i < this->vexNum; ++i) {
			int weight = arc[tmp][i].getWeight();
			if (weight + dis[tmp] >= 0) {
				if (dis[i] > dis[tmp] + weight) {
					dis[i] = dis[tmp] + weight;
					queue.push(i);
				}
			}
		}
	}
#else
	using pair = std::pair<int, int>;// first is distance, second is source
	std::priority_queue<pair, std::vector<pair>, std::greater<pair>> queue;  // 最小堆

	queue.push(std::make_pair(0, from));
	dis[from] = 0;

	while (!queue.empty()) {
		const pair &tmp = queue.top();
		queue.pop();
		int v = tmp.second;
		if (dis[v] < tmp.first) {
			continue;
		}
		for (int i = 0; i < this->vertexes.size(); ++i) {
			int weight = arc[v][i].getWeight();
			if (dis[v] + weight < dis[i]) {
				dis[i] = dis[v] + weight;
				queue.push(std::make_pair(dis[i], i));
			}
		}
	}

#endif

	if (dis[to] != 0x7f7f7f7f) {
		QStack<QString> stack;
		stack.push(this->vertexes[to].info);
		path.push_back(to);
		int index(to);
		//寻找路径
		while (index != from) {
			for (index = 0; index < this->vexNum; ++index) {
				if (dis[index] == dis[to] - this->arc[index][to].getWeight()) {
					stack.push(this->vertexes[index].info);
					path.push_back(index);
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
				int weight = this->arc[i][j].getDistance(), w;
				w = this->arc[i][j].getWeight();
				this->arc[i][j].setWeight(weight);
				Road road(i, j, w);
				auto result = this->edge.indexOf(road);
				if (result != -1)
					this->edge[result].weight = weight;
			}
		}

	} else {
		qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
		for (int i = 0; i < this->vexNum; ++i) {
			for (int j = 0; j < this->vexNum; ++j) {
				int weight = qrand() % 180 + this->arc[i][j].getDistance();
				this->arc[i][j].setWeight(weight);
				Pair pair(i, j);
				int result = -1;
				for (int k = 0; k < this->edge.size(); ++k) {
					if (i == j)
						continue;
					if (this->edge[k].m_pair == pair) {
						result = k;
						break;
					}
					if (this->edge[k].m_pair == Pair(j, i)) {
						result = k;
						break;
					}
				}
				if (result != -1) {
					this->edge[result].weight = weight;
				}
			}
		}
	}
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

//void Graph::setInfo(int index, QString info) {
//	int i = 0;
//	for (; i < this->vertexes.size() && this->vertexes[i].info != info; ++i);
//    //如果找不到点
//    if (i == this->vertexes.size()) {
//        addVex(info, this->vertexes[index].getPos().x(), this->vertexes[index].getPos().y());
//        delVex(getInfo(index));
//    } else { //如果找到了这个点
////        this->deleteArc();
////        this->addArc();
//	}
//}

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
