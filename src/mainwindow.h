#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QActionGroup>
#include "control/control.h"
#include "view/view.h"
#include "tools/tools.h"
//#include "core/utility.h"

class MainWindow : public QMainWindow {
public:
    GeoView* m_view;

    MainWindow(SceneController* controller, InteractionManager* interaction, SelectionManager* selection, CommandManager* commandManager);

};

#endif // MAINWINDOW_H
