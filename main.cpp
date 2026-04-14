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

// ---------------- MAIN ----------------
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 800, 600);

    SceneController controller(&scene);

    GeoView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);

    PointTool pointTool(&controller);
    LineTool lineTool(&controller);
    MoveTool moveTool(&controller);

    view.setTool(&lineTool);
    view.show();


    // Modell erstellen
    /*Point* p1 = new Point(100, 100);
    Point* p2 = new Point(300, 300);
    Line* line = new Line(p1, p2);

    // View erstellen
    GraphicsPoint* gp1 = new GraphicsPoint(p1);
    GraphicsPoint* gp2 = new GraphicsPoint(p2);
    GraphicsLine* gl  = new GraphicsLine(line);

    scene.addItem(gl);
    scene.addItem(gp1);
    scene.addItem(gp2);

    gp1->attach();
    gp2->attach();
    gl->attach();

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setWindowTitle("AxiomX");
    view.resize(420, 420);
    view.show();*/

    return app.exec();
}