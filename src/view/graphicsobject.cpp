#include "graphicsobject.h"

bool GraphicsObject::selected() {
    return m_selected;
}

QGraphicsScene* GraphicsObject::scene() {
    return m_scene;
}

void GraphicsObject::setScene(QGraphicsScene* s) {
    m_scene = s;
}