#include "point.h"

Point::Point(double x, double y) : m_id(-1), m_x(x), m_y(y) {}

int Point::id() {
    return m_id;
}

void Point::setId(int id) {
    m_id = id;
}

double Point::x() {
    return m_x;
}

double Point::y() {
    return m_y;
}

void Point::set(double nx, double ny) {
    m_x = nx;
    m_y = ny;
    notify();
}

void Point::update() {}