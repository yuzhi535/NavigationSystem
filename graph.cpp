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
}

Graph::~Graph() {

}

void Graph::addVex(QString info, int x, int y) {
    this->vertexes.push_back(Vertex(info, x, y));
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
    if (this->arc.capacity() < this->vexNum) {
        this->arc.resize(2 * this->vexNum);
        for (int i = 0; i < this->vexNum; ++i) {
            this->arc[i].resize(2 * this->vexNum);
        }
    }

    this->arc[road.m_pair.from][road.m_pair.to].setDistance(road.weight);
    this->arc[road.m_pair.to][road.m_pair.from].setDistance(road.weight);
    this->arc[road.m_pair.from][road.m_pair.to].setPair(Pair(road.m_pair.from, road.m_pair.to));
    this->arc[road.m_pair.to][road.m_pair.from].setPair(Pair(road.m_pair.from, road.m_pair.to));

    //邻接表的添加
    //-----------------------





    //-----------------------
    ++this->arcNum;
    return OK;
}

Status Graph::deleteArc(int start, int end) {
    Pair pair(start, end);
    return deleteArc(pair);
}

Status Graph::deleteArc(Pair pair) {
    this->arc[pair.from][pair.to].setDistance(-1);
    this->arc[pair.to][pair.from].setDistance(-1);
    //邻接表的删除
    //---------------------


    //---------------------

    return OK;
}

Status Graph::delVex(QString info) {
    int ff;
    for (ff = this->vertexes.size() - 1; ff < this->vexNum && this->vertexes.at(ff).info != info; ++ff);
    if (ff) {
        if (!this->vexNum) {
            return ERR;
        }
        for (int i = 0; i < this->vexNum; ++i) {
            this->arc[ff][i].setDistance(-1);
            this->arc[ff][i].setWeight(-1);
            this->arc[i][ff].setDistance(-1);
            this->arc[i][ff].setWeight(-1);
        }

        //邻接表的删除


        return OK;
    } else {
        return ERR;
    }


    --this->vexNum;
}

void Graph::init_from_file(QString fileName) {
    qDebug() << "init from " << fileName;
    std::ifstream in;
    in.open(fileName.toStdString());
    if (in.is_open()) {
        int vexNum, arcNum;
        //录入点和边
        in >> vexNum >> arcNum;
        //录入点的信息
        for (int i = 0; i < vexNum; ++i) {
            std::string info;
            int x, y;
            in >> info >> x >> y;
            //------------
            qDebug() << info.c_str() << x << y;
            //------------
            this->addVex(QString(info.c_str()), x, y);
        }

        //录入边的权值  (距离)
        for (int i = 0; i < arcNum; ++i) {
            int j, k, l;  //顶点 顶点 距离
            in >> j >> k >> l;
            this->addArc(j, k, l);
        }

    }
//#define TEST
//#ifdef TEST
//    for (int i = 0; i < this->vexNum; ++i) {
//        for (int j = 0; j < this->vexNum; ++j)
//            qDebug() << i << j << this->arc[i][j].getDistance();
//    }
//#endif
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

}

Arc::~Arc() {

}

void Arc::setPair(Pair pair) {
    this->m_pair = pair;
}
