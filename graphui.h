#ifndef GRAPHUI_H
#define GRAPHUI_H

#include <QWidget>
#include <QComboBox>
#include <QGroupBox>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPushButton>
#include <QMouseEvent>
#include <QPaintEvent>

#include "graph.h"

class GraphUi : public QWidget, Graph
{
    Q_OBJECT
public:
    explicit GraphUi(QWidget *parent = nullptr);

protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);


signals:


private:

};

#endif // GRAPHUI_H
