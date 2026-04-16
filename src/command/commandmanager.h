#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <stack>
#include "command.h"

class CommandManager {
public:
    std::stack<Command*> undoStack;
    std::stack<Command*> redoStack;

    void execute(Command* cmd) {
        cmd->execute();
        undoStack.push(cmd);

        // redo wird invalidiert
        while (!redoStack.empty()) {
            delete redoStack.top();
            redoStack.pop();
        }
    }

    void undo() {
        if (undoStack.empty()) return;

        Command* cmd = undoStack.top();
        undoStack.pop();

        cmd->undo();
        redoStack.push(cmd);
    }

    void redo() {
        if (redoStack.empty()) return;

        Command* cmd = redoStack.top();
        redoStack.pop();

        cmd->execute();
        undoStack.push(cmd);
    }
};

#endif // COMMANDMANAGER_H
