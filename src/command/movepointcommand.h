#ifndef MOVEPOINTCOMMAND_H
#define MOVEPOINTCOMMAND_H

#include "command.h"
#include "../core/point.h"

class MovePointCommand : public Command {
public:
    Point* m_point;

    double m_oldX, m_oldY;
    double m_newX, m_newY;

    MovePointCommand(Point* p, double oldX, double oldY, double newX, double newY);

    void execute() override;

    void undo() override;
};

#endif // MOVEPOINTCOMMAND_H
