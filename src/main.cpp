#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QGraphicsScene* scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 800, 600);

    SceneController controller(scene);
    InteractionManager interaction(&controller);
    SelectionManager selection;
    CommandManager commandManager;


    MainWindow window(&controller, &interaction, &selection, &commandManager);
    window.show();

    return app.exec();
}