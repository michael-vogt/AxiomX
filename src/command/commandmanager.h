#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <stack>
#include "command.h"

class CommandManager {
public:
    std::stack<Command*> undoStack;
    std::stack<Command*> redoStack;

    void execute(Command* cmd);

    void undo();

    void redo();
};

#endif // COMMANDMANAGER_H
