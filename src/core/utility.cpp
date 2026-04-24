#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include "utility.h"
#include "../view/graphicscircle.h"
#include "../view/graphicsline.h"
#include "../view/graphicspoint.h"

template<typename Base, typename T>
inline bool instanceOf(T* ptr) {
    return (dynamic_cast<Base*>(ptr) != nullptr);
}

QString lineTypeToString(LineType lineType) {
    switch (lineType) {
    case SEGMENT:
        return "Segment";
    case RAY:
        return "Ray";
    case LINE:
        return "Line";
    default:
        return "Unknown";
    }
}

LineType lineTypeFromInt(int lt) {
    if (lt == 0) return SEGMENT;
    if (lt == 1) return RAY;
    return LINE;

}

void printGraphicsObjectsToConsole(std::vector<GraphicsObject*> graphics) {
    qDebug() << "graphics contains " << QString::number(graphics.size()) + " elements:";
    for (auto go : graphics) {
        auto gp = dynamic_cast<GraphicsPoint*>(go);
        if (gp) qDebug() << gp;
        auto gl = dynamic_cast<GraphicsLine*>(go);
        if (gl) qDebug() << gl;
        auto gc = dynamic_cast<GraphicsCircle*>(go);
        if (gc) qDebug() << gc;
    }
}

void save(SceneController* ctrl, const QString& filename) {
    QJsonObject root;

    QJsonArray pointsArray;
    QJsonArray linesArray;

    // Punkte
    for (auto g : ctrl->graphics()) {
        if (auto gp = dynamic_cast<GraphicsPoint*>(g)) {
            QJsonObject obj;
            obj["id"] = gp->model()->id();
            obj["x"] = gp->model()->x();
            obj["y"] = gp->model()->y();
            pointsArray.append(obj);
        }
    }

    // Linien
    for (auto g : ctrl->graphics()) {
        if (auto gl = dynamic_cast<GraphicsLine*>(g)) {
            QJsonObject obj;
            obj["a"] = gl->model()->p1()->id();
            obj["b"] = gl->model()->p2()->id();
            obj["lt"] = gl->lineType();
            linesArray.append(obj);
        }
    }

    root["points"] = pointsArray;
    root["lines"] = linesArray;

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(root).toJson());
    }
}

void load(SceneController* ctrl, const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return;

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);

    QJsonObject root = doc.object();

    std::map<int, Point*> pointMap;

    // 🔴 Szene leeren
    for (auto g : ctrl->graphics())
        ctrl->scene()->removeItem(dynamic_cast<QGraphicsItem*>(g));

    ctrl->graphics().clear();

    // Punkte laden
    for (auto val : root["points"].toArray()) {
        QJsonObject obj = val.toObject();

        int id = obj["id"].toInt();
        double x = obj["x"].toDouble();
        double y = obj["y"].toDouble();

        Point* p = new Point(x, y);
        p->setId(id);
        auto gp = new GraphicsPoint(p, ctrl->scene());
        gp->sync();

        ctrl->scene()->addItem(gp);
        pointMap[id] = p;

        //ctrl->nextId = std::max(ctrl->nextId, id + 1);
    }

    // Linien laden
    for (auto val : root["lines"].toArray()) {
        QJsonObject obj = val.toObject();

        int a = obj["a"].toInt();
        int b = obj["b"].toInt();
        LineType lt = lineTypeFromInt(obj["lt"].toInt());

        Line* l = new Line(pointMap[a], pointMap[b]);
        auto gl = new GraphicsLine(l, lt, ctrl->scene());
        gl->sync();

        ctrl->scene()->addItem(gl);
    }
}