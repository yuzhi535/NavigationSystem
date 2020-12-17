#include "graphui.h"

/**
 * @brief 初始化图   OK
 * @brief 完善绘图
 * @brief 完善颜色
 * @brief 最好加上鼠标移动顶点
 * @brief 最好加上添加顶点和边，这个功能需要信号槽传递了
 * @param parent
 */
GraphUi::GraphUi(QWidget *parent) : QWidget(parent) {
    graph.init_from_file();
}

void GraphUi::mouseReleaseEvent(QMouseEvent *event) {





    update();
}

void GraphUi::mousePressEvent(QMouseEvent *event) {
    qDebug() << "press";
}


/**
 * @brief 背景色
 * @brief 边框
 * @brief 顶点
 * @brief 边
 * @brief 顶点名字
 * @param event
 */
void GraphUi::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor(  56, 116, 237  )));
    painter.drawRect(rect());






}
