#ifndef CREATELINECOMMAND_H
#define CREATELINECOMMAND_H

#include "resultcommand.h"
#include "../control/scenecontroller.h"

class CreateLineCommand : public ResultCommand<Line*, GraphicsLine*> {
public:
    SceneController* m_ctrl;
    GraphicsPoint* m_a;
    GraphicsPoint* m_b;

    Line* m_line = nullptr;
    GraphicsLine* m_gline = nullptr;
    LineType m_lineType;

    CreateLineCommand(SceneController* c, GraphicsPoint* a, GraphicsPoint* b, LineType lineType)
        : m_ctrl(c), m_a(a), m_b(b), m_lineType(lineType) {}

    void execute() override {
        m_line = new Line(m_a->model(), m_b->model());
        m_gline = new GraphicsLine(m_line, m_ctrl->scene());
        m_gline->setLineType(m_lineType);

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

    GraphicsLine* getResultGraphicsObject() override {
        return m_gline;
    }
};

#endif // CREATELINECOMMAND_H
