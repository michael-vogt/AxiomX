#ifndef RESULTCOMMAND_H
#define RESULTCOMMAND_H

#include "command.h"

template<typename T, typename U>
class ResultCommand : public Command {
public:
    virtual T getResult() = 0;
    virtual U getResultGraphicsObject() = 0;
};

#endif // RESULTCOMMAND_H
