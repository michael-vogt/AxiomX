#ifndef CREATELINECOMMAND_H
#define CREATELINECOMMAND_H

#include "resultcommand.h"
#include "../control/scenecontroller.h"

class CreateLineCommand : public ResultCommand<Line*> {
public:
    SceneController* m_ctrl;
    Point* m_a;
    Point* m_b;

    Line* m_line = nullptr;
    GraphicsLine* m_gline = nullptr;

    CreateLineCommand(SceneController* c, Point* a, Point* b)
        : m_ctrl(c), m_a(a), m_b(b) {}

    void execute() override {
        m_line = new Line(m_a, m_b);
        m_gline = new GraphicsLine(m_line, m_ctrl->scene());

        m_ctrl->scene()->addItem(m_gline);
        m_gline->attach();

        m_ctrl->graphics().push_back(m_gline);
    }

    void undo() override {
        m_ctrl->scene()->removeItem(m_gline);
        auto graphics = m_ctrl->graphics();
        graphics.erase(std::remove(graphics.begin(), graphics.end(), m_gline), graphics.end());
    }

    Line* getResult() override {
        return m_line;
    }
};

#endif // CREATELINECOMMAND_H
