#include "graphui.h"

GraphUi::GraphUi(QWidget *parent) : QWidget(parent) {

}

void GraphUi::mouseReleaseEvent(QMouseEvent* event) {
    qDebug() << "release";
}

void GraphUi::mousePressEvent(QMouseEvent* event) {

}

void GraphUi::paintEvent(QPaintEvent* event) {

}
