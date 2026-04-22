#ifndef CREATECIRCLECOMMAND_H
#define CREATECIRCLECOMMAND_H

#include "resultcommand.h"
#include "../control/scenecontroller.h"
#include "../view/graphicscircle.h"

class CreateCircleCommand : public ResultCommand<Circle*, GraphicsCircle*> {
public:
    SceneController* m_ctrl;
    GraphicsPoint* m_center;
    GraphicsPoint* m_pointOnCircle;
    //double m_radius;

    Circle* m_circle = nullptr;
    GraphicsCircle* m_gcircle = nullptr;

    CreateCircleCommand(SceneController* c, GraphicsPoint* center, GraphicsPoint* pointOnCircle);

    void execute() override;

    void undo() override;

    Circle* getResult() override;

    GraphicsCircle* getResultGraphicsObject() override;
};

#endif // CREATECIRCLECOMMAND_H
