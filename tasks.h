#ifndef TASKS_H
#define TASKS_H

#include "task.h"

namespace G8
{
    namespace Tasks
    {
        TASK_RESULT Main(Robot * const pRob);

        TASK_RESULT PerfTest1(Robot * const pRob);

        TASK_RESULT PerfTest3(Robot * const pRob);
    }
}

#endif // TASKS_H
