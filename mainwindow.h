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
#include "view.h"

class MainWindow : public QMainWindow {
public:
    GeoView* view;

    MainWindow(SceneController* controller,
               PointTool* pointTool,
               LineTool* lineTool,
               MoveTool* moveTool)
    {
        // Scene + View
        QGraphicsScene* scene = controller->getScene();
        view = new GeoView(scene);
        view->setRenderHint(QPainter::Antialiasing);
        setCentralWidget(view);

        // Toolbar
        QToolBar* toolbar = addToolBar("Tools");

        QActionGroup* group = new QActionGroup(this);
        group->setExclusive(true);

        // Aktionen
        QAction* moveAction = toolbar->addAction("Move");
        QAction* pointAction = toolbar->addAction("Point");
        QAction* lineAction = toolbar->addAction("Line");

        moveAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_M));
        pointAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_P));
        lineAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_L));

        moveAction->setCheckable(true);
        pointAction->setCheckable(true);
        lineAction->setCheckable(true);

        group->addAction(moveAction);
        group->addAction(pointAction);
        group->addAction(lineAction);

        // Default Tool
        moveAction->setChecked(true);
        view->setTool(moveTool);

        // 🔥 Verbindungen
        connect(moveAction, &QAction::triggered, [=]() {
            view->setTool(moveTool);
        });

        connect(pointAction, &QAction::triggered, [=]() {
            view->setTool(pointTool);
        });

        connect(lineAction, &QAction::triggered, [=]() {
            view->setTool(lineTool);
        });

        setWindowTitle("AxiomX");
        resize(900, 700);
    }
};

#endif // MAINWINDOW_H
