/*#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "AxiomX_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return QCoreApplication::exec();
}*/

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>

#include "core.h"
#include "view.h"
#include "mainwindow.h"

// ---------------- MAIN ----------------
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QGraphicsScene* scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 800, 600);

    SceneController controller(scene);

    //GeoView view(&scene);
    //view.setRenderHint(QPainter::Antialiasing);

    PointTool pointTool(&controller);
    LineTool lineTool(&controller);
    MoveTool moveTool(&controller);

    MainWindow window(&controller, &pointTool, &lineTool, &moveTool);
    window.show();

    //view.setTool(&lineTool);
    //view.show();

    return app.exec();
}