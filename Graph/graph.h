#ifndef GRAPH_H
#define GRAPH_H

#include <QQueue>
#include <QPoint>
#include <QMap>
#include <QString>
#include <QPoint>


const int maxVexNum = 20;
/**
 * @brief The Pair struct
 * @attention start vertex -> end vertex
 */
struct Pair
{
    int from, to;
};

/**
 * @brief The EdgeSet class
 */
class EdgeSet
{
public:
    EdgeSet();
    EdgeSet(EdgeSet& other);

    void setGroup(bool key);


private:
    int m_weight;     // the weight of an edge
    Pair m_pair;      // record the vertex from the begin and the end
    int m_group;      // to record the people density
    bool isGroup;     // to decide whether the group arg works

};


/**
 * @brief the set of verteces
 */
typedef class VexSet
{
public:
    VexSet();
    ~VexSet();
    void addInfo (const char* info);
private:
    QString m_info;    // the info of this vertex
    QPoint m_pos;      // the position in the graph ui

} Arc[maxVexNum][maxVexNum];


class Graph
{
public:
    Graph();
    ~Graph();
    void addArc(Pair currPos);
    void addArc(int start, int end);
    void operator << (Pair currPos);
    void deleteArc(Pair currPos);
    void deleteArc(int start, int end);
    void addVex (const char* info);

    int getVexNum ();
    int getArcNum ();

    QVector<int> findShortestRoad (int from, int to);    // to find the shortest road from a to b
    QVector<int> findEulerRoad(int source);              // to find the Euler Road from source

private:
    EdgeSet m_edgeSet;           // the set of the edges;
    int m_vexNum, m_arcNum;
    QVector<VexSet> m_vexSet;    // the set of the verteces;
};

#endif // GRAPH_H
