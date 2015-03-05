#ifndef GLOBAL_H
#define GLOBAL_H

#include "constant.h"
#include "task.h"

namespace G8
{
    extern CONSTANT_SYS CONST;

    extern TaskSystem   TASK;

    void DefineConstants(void);

    void DefineTasks(void);
}

#endif // GLOBAL_H
