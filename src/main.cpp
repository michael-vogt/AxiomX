#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QGraphicsScene* scene = new QGraphicsScene();
    scene->setSceneRect(-5000, -5000, 10000, 10000);

    SceneController controller(scene);
    InteractionManager interaction(&controller);
    SelectionManager selection;
    CommandManager commandManager;


    MainWindow window(&controller, &interaction, &selection, &commandManager);
    window.show();

    return app.exec();
}