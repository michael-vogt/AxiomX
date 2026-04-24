#include <QToolBar>
#include <QActionGroup>
#include "mainwindow.h"
#include "core/utility.h"
#include "tools/circletool.h"
#include "tools/intersectiontool.h"
#include "tools/linetool.h"
#include "tools/movetool.h"
#include "tools/perpendiculartool.h"
#include "tools/pointtool.h"
#include "tools/selecttool.h"

MainWindow::MainWindow(SceneController* controller, InteractionManager* interaction, SelectionManager* selection, CommandManager* commandManager) {
    // Scene + View
    QGraphicsScene* scene = controller->scene();
    m_view = new GeoView(scene, commandManager, controller);
    m_view->setRenderHint(QPainter::Antialiasing);
    m_view->setInteractionManager(interaction);
    setCentralWidget(m_view);

    SnapManager* snapManager = m_view->snapManager();
    if (!snapManager) {
        snapManager = new SnapManager(controller);
        m_view->setSnapManager(snapManager)        ;
    }
    PointTool* pointTool = new PointTool(controller, commandManager, snapManager);
    LineTool* lineTool = new LineTool(controller, interaction, scene, commandManager, snapManager);
    MoveTool* moveTool = new MoveTool(controller);
    SelectTool* selectTool = new SelectTool(controller, selection, scene);
    CircleTool* circleTool = new CircleTool(controller, interaction, scene, commandManager, snapManager);
    IntersectionTool* intersectionTool = new IntersectionTool(controller, commandManager);
    PerpendicularTool* perpendicularTool = new PerpendicularTool(controller, commandManager, snapManager);

    // Toolbar
    QToolBar* toolbar = addToolBar("Tools");

    QActionGroup* group = new QActionGroup(this);
    group->setExclusive(true);

    // Aktionen
    QAction* selectAction = toolbar->addAction("Select");
    QAction* moveAction = toolbar->addAction("Move");
    QAction* pointAction = toolbar->addAction("Point");
    QAction* lineAction = toolbar->addAction(lineTypeToString(lineTool->lineType()));
    QAction* circleAction = toolbar->addAction("Circle");
    QAction* intersectionAction = toolbar->addAction("Intersect");
    QAction* perpendicularAction = toolbar->addAction("Perpendicular");

    selectAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    moveAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_M));
    pointAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_P));
    lineAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_L));
    circleAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_C));
    intersectionAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_I));
    perpendicularAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_P));

    selectAction->setCheckable(true);
    moveAction->setCheckable(true);
    pointAction->setCheckable(true);
    lineAction->setCheckable(true);
    circleAction->setCheckable(true);
    intersectionAction->setCheckable(true);
    perpendicularAction->setCheckable(true);

    group->addAction(selectAction);
    group->addAction(moveAction);
    group->addAction(pointAction);
    group->addAction(lineAction);
    group->addAction(circleAction);
    group->addAction(intersectionAction);
    group->addAction(perpendicularAction);

    // Default Tool
    moveAction->setChecked(true);
    m_view->setTool(moveTool);

    // 🔥 Verbindungen
    connect(selectAction, &QAction::triggered, [this, selectTool]() {
        m_view->setTool(selectTool);
    });

    connect(moveAction, &QAction::triggered, [this, moveTool]() {
        m_view->setTool(moveTool);
    });

    connect(pointAction, &QAction::triggered, [this, pointTool]() {
        m_view->setTool(pointTool);
    });

    connect(lineAction, &QAction::triggered, [this, lineTool, lineAction]() {
        if (m_view->tool() == lineTool) {
            lineTool->toggleLineType();
            lineAction->setText(lineTypeToString(lineTool->lineType()));
        } else {
            m_view->setTool(lineTool);
        }
    });

    connect(circleAction, &QAction::triggered, [this, circleTool]() {
        m_view->setTool(circleTool);
    });

    connect(intersectionAction, &QAction::triggered, [this, intersectionTool]() {
        m_view->setTool(intersectionTool);
    });

    connect(perpendicularAction, &QAction::triggered, [this, perpendicularTool]() {
        m_view->setTool(perpendicularTool);
    });

    setWindowTitle("AxiomX");
    resize(900, 700);
}