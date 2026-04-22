#include "movepointcommand.h"

MovePointCommand::MovePointCommand(Point* p,
                 double oldX, double oldY,
                 double newX, double newY)
    : m_point(p),
    m_oldX(oldX), m_oldY(oldY),
    m_newX(newX), m_newY(newY) {}

void MovePointCommand::execute() {
    m_point->set(m_newX, m_newY);
}

void MovePointCommand::undo() {
    m_point->set(m_oldX, m_oldY);
}