//
// Created by sasuke on 2020/12/17.
//

#ifndef NAVIGATIONSYSTEM_GRAPH_H
#define NAVIGATIONSYSTEM_GRAPH_H

#include <iostream>
#include <fstream>
#include <QString>
#include <QVector>
#include <QMap>    //表示颜色
#include <QQueue>  //最短路径
#include <QColor>  //各种颜色表示不同
#include <QPoint>  //点的坐标

#include <QDebug>

#define DEV 1

enum Status {
    OK, ERR
};

/**
 * @brief 用于图中的路径的起点和终点
 */
struct Pair {
    int from, to;

    Pair() : Pair(-1, -1) {}

    Pair(const Pair& other) : from(other.from), to(other.to) {}  //拷贝构造函数

    Pair(int a, int b) : from(a), to(b) {}
};

/**
 * @brief 用于起点和终点在加上权重，最短路径时有用
 */
struct Road {
    Pair m_pair;
    int weight;

    Road() : Road(Pair(-1, -1), -1) {}

    Road(const Road& other) : m_pair(other.m_pair), weight(other.weight) {} //拷贝构造函数

    Road(Pair pair, int w) : m_pair(pair), weight(w) {}
    Road(int a, int b, int c) : m_pair(a, b), weight(c) {}
};

/**
 * @brief 边 最终的权重  距离 顶点
 */
class Arc {
public:
    Arc();

    ~Arc();

    void setDistance(int num);
    void setWeight(int num);
    int getDistance() const;
    int getWeight() const;
    void setPair(Pair pair);

private:
    int distance;  //距离
    int m_weight;  //最终的权重
    Pair m_pair;   //起点和终点
#if DEV == 2
//实验性内容
    int group;
    int weather;
#endif
};

class Vertex {
public:
    ~Vertex();

    Vertex(QString context, int x, int y) : info(context) {}

    void addInfo(QString context);

    void setPos(QPoint pos);
    QPoint getPos();
    QString info;
    QPoint point;
};

/**
 * @brief 邻接矩阵 邻接表 权重的计算方式  颜色
 */

class Graph {
public:
    Graph();

    ~Graph();

    void init_from_file(QString fileName);

    //添加顶点
    void addVex(QString info, int x, int y);

    //删除顶点
    Status delVex(QString info);

    //加边  注意发送信号槽
    Status addArc(int start, int end, int weight);

    Status addArc(Road road);

    Status addArc(Pair pair, int weight);

    //删除边
    Status deleteArc(int start, int end);

    Status deleteArc(Pair pair);

    enum ArcColor {
        TARGET = 1, OTHER
    };

    enum VexColor {
        AIM = 3, BY, IRRELEVANT
    };


private:
    QVector<QVector<Arc>> arc;  //邻接矩阵
    QVector<Road> edge;         //邻接表
    QVector<Vertex> vertexes;  //顶点集合
    int vexNum, arcNum;  //顶点数量  边的数量

    QVector<QColor> color;

};


#endif //NAVIGATIONSYSTEM_GRAPH_H