#ifndef MOVEPOINTCOMMAND_H
#define MOVEPOINTCOMMAND_H

#include "command.h"
#include "../core/point.h"

class MovePointCommand : public Command {
public:
    Point* m_point;

    double m_oldX, m_oldY;
    double m_newX, m_newY;

    MovePointCommand(Point* p,
                     double oldX, double oldY,
                     double newX, double newY)
        : m_point(p),
        m_oldX(oldX), m_oldY(oldY),
        m_newX(newX), m_newY(newY) {}

    void execute() override {
        m_point->set(m_newX, m_newY);
    }

    void undo() override {
        m_point->set(m_oldX, m_oldY);
    }
};

#endif // MOVEPOINTCOMMAND_H
