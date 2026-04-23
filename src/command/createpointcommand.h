#ifndef CREATEPOINTCOMMAND_H
#define CREATEPOINTCOMMAND_H

#include "resultcommand.h"
#include "../control/scenecontroller.h"
#include "../view/graphicspoint.h"

class CreatePointCommand : public ResultCommand<Point*, GraphicsPoint*> {
public:
    SceneController* m_ctrl;
    double m_x, m_y;
    bool m_isTemporaryPoint;

    Point* m_point = nullptr;
    GraphicsPoint* m_gpoint = nullptr;

    CreatePointCommand(SceneController* c, double x, double y, bool isTemporaryPoint = false);

    void execute() override;

    void undo() override;

    Point* getResult() override;

    GraphicsPoint* getResultGraphicsObject() override;
};

#endif // CREATEPOINTCOMMAND_H
