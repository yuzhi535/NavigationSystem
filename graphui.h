#ifndef GRAPHUI_H
#define GRAPHUI_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPushButton>
#include <QMouseEvent>
#include <QPaintEvent>

#include "graph.h"

class GraphUi : public QWidget {
Q_OBJECT
public:
    explicit GraphUi(QWidget *parent = nullptr);

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;


signals:

public slots:


private:
    Graph graph;
    QPoint lastPos;

};

#endif // GRAPHUI_H
