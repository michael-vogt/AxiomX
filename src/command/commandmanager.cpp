#include "commandmanager.h"

void CommandManager::execute(Command *cmd) {
    cmd->execute();
    undoStack.push(cmd);

    // redo wird invalidiert
    while (!redoStack.empty()) {
        delete redoStack.top();
        redoStack.pop();
    }
}

void CommandManager::undo() {
    if (undoStack.empty()) return;

    Command* cmd = undoStack.top();
    undoStack.pop();

    cmd->undo();
    redoStack.push(cmd);
}

void CommandManager::redo() {
    if (redoStack.empty()) return;

    Command* cmd = redoStack.top();
    redoStack.pop();

    cmd->execute();
    undoStack.push(cmd);
}