#ifndef QGRAPH_H
#define QGRAPH_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPixmap>
#include <QPushButton>
#include <QPainter>
#include <QPoint>
#include <QBrush>

/**
 * @brief The QGraph class
 * @target to implement the graphic interface of the graph
 */
class QGraph : public QWidget
{
    Q_OBJECT
public:
    explicit QGraph(QWidget *parent = nullptr);


protected:
    void mousePressedEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);

signals:



private:
    QPoint startPos, lastPos;
};

#endif // QGRAPH_H
