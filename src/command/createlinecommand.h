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

    CreateLineCommand(SceneController* c, GraphicsPoint* a, GraphicsPoint* b, LineType lineType);

    void execute() override;

    void undo() override;

    Line* getResult() override;

    GraphicsLine* getResultGraphicsObject() override;
};

#endif // CREATELINECOMMAND_H
