#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
};*/

#include <QMainWindow>
#include <QToolBar>
#include <QActionGroup>
#include "control/control.h"
#include "view/view.h"
#include "tools/tools.h"

class MainWindow : public QMainWindow {
public:
    GeoView* m_view;

    MainWindow(SceneController* controller, InteractionManager* interaction, SelectionManager* selection) /*,
               PointTool* pointTool,
               LineTool* lineTool,
               MoveTool* moveTool)*/
    {
        // Scene + View
        QGraphicsScene* scene = controller->scene();
        m_view = new GeoView(scene);
        m_view->setRenderHint(QPainter::Antialiasing);
        m_view->setInteractionManager(interaction);
        setCentralWidget(m_view);

        PointTool* pointTool = new PointTool(controller);
        LineTool* lineTool = new LineTool(controller, interaction, scene);
        MoveTool* moveTool = new MoveTool(controller);
        SelectTool* selectTool = new SelectTool(controller, selection, scene);

        // Toolbar
        QToolBar* toolbar = addToolBar("Tools");

        QActionGroup* group = new QActionGroup(this);
        group->setExclusive(true);

        // Aktionen
        QAction* selectAction = toolbar->addAction("Select");
        QAction* moveAction = toolbar->addAction("Move");
        QAction* pointAction = toolbar->addAction("Point");
        QAction* lineAction = toolbar->addAction("Line");

        selectAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
        moveAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_M));
        pointAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_P));
        lineAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_L));

        selectAction->setCheckable(true);
        moveAction->setCheckable(true);
        pointAction->setCheckable(true);
        lineAction->setCheckable(true);

        group->addAction(selectAction);
        group->addAction(moveAction);
        group->addAction(pointAction);
        group->addAction(lineAction);

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

        connect(lineAction, &QAction::triggered, [this, lineTool]() {
            m_view->setTool(lineTool);
        });

        setWindowTitle("AxiomX");
        resize(900, 700);
    }
};

#endif // MAINWINDOW_H
