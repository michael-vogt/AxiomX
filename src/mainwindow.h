#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "command/commandmanager.h"
#include "control/interactionmanager.h"
#include "control/scenecontroller.h"
#include "control/selectionmanager.h"
#include "view/geoview.h"

class MainWindow : public QMainWindow {
public:
    GeoView* m_view;

    MainWindow(SceneController* controller, InteractionManager* interaction, SelectionManager* selection, CommandManager* commandManager);

};

#endif // MAINWINDOW_H
