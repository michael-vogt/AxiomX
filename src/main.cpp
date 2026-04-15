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

/*#include "control/control.h"
#include "core/core.h"
#include "view/view.h"*/
#include "allincludes.h"
#include "mainwindow.h"

// ---------------- MAIN ----------------
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QGraphicsScene* scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 800, 600);

    SceneController controller(scene);
    InteractionManager interaction(&controller);
    SelectionManager selection;


    MainWindow window(&controller, &interaction, &selection);
    window.show();

    return app.exec();
}