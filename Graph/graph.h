#ifndef GRAPH_H
#define GRAPH_H

#include <QQueue>
#include <QPoint>
#include <QMap>
#include <QString>
#include <QPoint>
#include <fstream>
#include <QDebug>
#include <string>


const int maxVexNum = 20;
/**
 * @brief The Pair struct
 * @attention start vertex -> end vertex
 */
struct Pair
{
    int from, to;
    Pair() : Pair(-1, -1) {}
    Pair(int a, int b) : from(a), to(b) {}
};

/**
 * @brief The EdgeSet class
 */
typedef class EdgeSet
{
public:
    EdgeSet();
    EdgeSet(EdgeSet& other);

    void setGroup(bool key);   //change the weight
    void setWeight(int weight);
    int getWeight() { return m_weight; }


private:
    int m_weight;     // the weight of an edge
    Pair m_pair;      // record the vertex from the begin and the end
    int m_group;      // to record the people density
    bool isGroup;     // to decide whether the group arg works

} Arc[maxVexNum][maxVexNum];


/**
 * @brief the set of verteces
 */
class VexSet
{
public:
    VexSet();
    VexSet(std::string info) : m_info(info) {}
    ~VexSet();
    void addInfo (std::string info);
private:
    std::string m_info;    // the info of this vertex
    QPoint m_pos;      // the position in the graph ui

} ;


class Graph
{
public:
    Graph();
    ~Graph();
    void init(std::fstream& out);
    void addArc(Pair currPos, int weight = 1);
    void addArc(int start, int end, int weight = 1);
    void deleteArc(Pair currPos);
    void deleteArc(int start, int end);
    void addVex (const std::string info);
    void deleteVex();
    void show();

    int getVexNum ();
    int getArcNum ();

    QVector<int> findShortestRoad (int from, int to);    // to find the shortest road from a to b
    QVector<int> findEulerRoad(int source);              // to find the Euler Road from source

private:
    Arc m_edgeSet;           // the set of the edges;
    int m_vexNum, m_arcNum;
    QVector<VexSet> m_vexSet;    // the set of the verteces;
};

#endif // GRAPH_H
