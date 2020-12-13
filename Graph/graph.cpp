#include "graph.h"

Graph::Graph()
{

}

Graph::~Graph()
{

}

#include <iostream>
#include <cstdlib>
void Graph::init(std::fstream &out)
{
    if (out.is_open())
    {
        out >> m_vexNum >> m_arcNum;   //init the vexnum and arcnum
        std::cout << m_vexNum << m_arcNum;
        for (int i = 0; i < m_vexNum; ++i)
        {
            std::string info;
            out >> info;
            addVex(info);
        }

        for (int i = 0; i < m_arcNum; ++i)
        {
            int from, to, weight;
            out >> from >> to >> weight;
            addArc(from, to, weight);
        }
        out.close();
    }
}

void Graph::show()
{
    std::cout << '\n';
    for (int i = 0; i < this->m_vexNum; ++i)
    {
        for (int j = 0; j < this->m_vexNum; ++j)
            std::cout << this->m_edgeSet[i][j].getWeight() << ' ';
        std::cout << '\n';
    }
}

void EdgeSet::setWeight(int weight)
{
    m_weight = weight;
}

void Graph::addArc(Pair currPos, int weight)
{
    if (currPos.from > maxVexNum || currPos.to > maxVexNum)
    {
        qDebug() << "add arc can't do this";
        return;
    }
    m_edgeSet[currPos.from][currPos.to].setWeight(weight);
}

void Graph::addArc(int start, int end, int weight)
{
    Pair pair(start, end);
    addArc(pair, weight);
}

void Graph::addVex(const std::string info)
{
    m_vexSet.push_back(VexSet(info));
}

void Graph::deleteArc(Pair currPos)
{
    if (currPos.from > maxVexNum || currPos.to > maxVexNum)
    {
        qDebug() << "delete arc can't do this";
        return;
    }
    m_edgeSet[currPos.from][currPos.to].setWeight(-1);
}

void Graph::deleteArc(int start, int end)
{
    Pair pair(start, end);
    deleteArc(pair);
}

void Graph::deleteVex()
{
    --m_vexNum;
    m_vexSet.pop_back();
}

int Graph::getVexNum()
{
    return m_vexNum;
}

int Graph::getArcNum()
{
    return m_arcNum;
}

QVector<int> Graph::findShortestRoad(int from, int to)
{
    return QVector<int> {0};
}

QVector<int> Graph::findEulerRoad(int source)
{
    return QVector<int> {0};
}

VexSet::VexSet()
{

}

VexSet::~VexSet()
{

}

void VexSet::addInfo(std::string info)
{
    m_info = info;
}

EdgeSet::EdgeSet()
{
    m_weight = -1;
}

EdgeSet::EdgeSet(EdgeSet& other)
{
    this->isGroup = other.isGroup;
    this->m_group = other.m_group;
    this->m_pair = other.m_pair;
    this->m_weight = other.m_weight;
}

void EdgeSet::setGroup(bool key)
{
    if (key)
    {

    }
    else
    {

    }
}


