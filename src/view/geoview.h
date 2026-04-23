#ifndef GEOVIEW_H
#define GEOVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include "grid.h"
#include "../command/commandmanager.h"
#include "../control/interactionmanager.h"
#include "../tools/tool.h"

class GeoView : public QGraphicsView {
private:
    Tool* m_tool = nullptr;
    InteractionManager* m_interaction = nullptr;
    CommandManager* m_commandManager = nullptr;
    SceneController* m_ctrl = nullptr;
    Grid* m_grid = nullptr;

public:

    GeoView(QGraphicsScene* s, CommandManager* cmd, SceneController* c);

    Grid* grid();

    Tool* tool();

    void setTool(Tool* t);

    void setInteractionManager(InteractionManager* im);

protected:
    void keyPressEvent(QKeyEvent* event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;

    void mouseReleaseEvent(QMouseEvent* event) override;

    void wheelEvent(QWheelEvent* event) override;

    void drawBackground(QPainter *painter, const QRectF &rect) override;

};

#endif // GEOVIEW_H
