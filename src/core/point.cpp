#include "point.h"

Point::Point(double x, double y) : m_x(x), m_y(y) {}

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