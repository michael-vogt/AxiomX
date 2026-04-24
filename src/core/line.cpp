#include <QLineF>
#include "line.h"

Line::Line(Point* a, Point* b) : m_p1(a), m_p2(b) {
    m_p1->addDependent(this);
    m_p2->addDependent(this);
    updateLine();
}

Point* Line::p1() {
    return m_p1;
}

Point* Line::p2() {
    return m_p2;
}

double Line::x1() {
    return m_x1;
}

double Line::x2() {
    return m_x2;
}

double Line::y1() {
    return m_y1;
}

double Line::y2() {
    return m_y2;
}

bool Line::contains(const QPointF& p, LineType lineType)  {
    double D = (p.x() - x1()) * (y2() - y1()) - (p.y() - y1()) * ((x2() - x1()));

    if (std::abs(D) >= 1e-10) {
        return false;
    }

    double t;
    if (std::abs(x2()-x1()) > 1e-10) {
        t = (p.x() - x1()) / (x2() - x1());
    } else if (std::abs(y2() - y1()) > 1e-10) {
        t = (p.y() - y1()) / (y2() - y1());
    } else {
        return true;
    }

    if (t < 0) {
        if (lineType == LINE) return true;
    } else if (t > 1) {
        if (lineType != SEGMENT) return true;
    } else {
        return true;
    }

    return false;
}

std::vector<Point*> Line::intersect(Line* other, LineType lineTypeOther, LineType lineTypeThis) {
    std::vector<Point*> points;

    double dx1 = x2() - x1();
    double dy1 = y2() - y1();
    double dx2 = other->x2() - other->x1();
    double dy2 = other->y2() - other->y1();

    double denominator = dx1 * dy2 - dy1 * dx2;
    if (std::abs(denominator) < 1e-10) {
        return points;
    }

    double t = ((other->x1() - x1()) * dy2 - (other->y1() - y1()) * dx2) / denominator;

    QPointF S(x1() + t * (x2() - x1()), y1() + t * (y2() - y1()));
    bool SinThis = contains(S, lineTypeThis);
    bool SinOther = other->contains(S, lineTypeOther);
    if (SinThis && SinOther) {
        points.push_back(new Point(S.x(), S.y()));
    }

    return points;
}

void Line::update() {
    updateLine();
}

void Line::updateLine() {
    m_x1 = m_p1->x();
    m_y1 = m_p1->y();
    m_x2 = m_p2->x();
    m_y2 = m_p2->y();
}

double Line::distanceToPoint(const QPointF& pos, LineType lineType) {
    QPointF a(m_p1->x(), m_p1->y());
    QPointF b(m_p2->x(), m_p2->y());

    QPointF dir = b - a;

    // berechne die Projektion von pos auf die Gerade durch a und b
    // abhängig vom Linientyp wird der Parameter t beschränkt.
    double t = QPointF::dotProduct(pos - a, dir) / QPointF::dotProduct(dir, dir);
    if (lineType == RAY) t = std::max(t, 0.0);
    if (lineType == SEGMENT) t = std::min(1.0, std::max(t, 0.0));
    QPointF pProj = a + t * dir;

    return QLineF(pos, pProj).length();
}