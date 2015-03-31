#ifndef TASKS_H
#define TASKS_H

#include "task.h"

namespace G8
{
    namespace Tasks
    {
        TASK_RESULT Main(Robot * const pRob);

        TASK_RESULT DriveToSaltBag(Robot * const pRob);

        TASK_RESULT CaptureSaltBag(Robot * const pRob);

        TASK_RESULT DriveToCrank(Robot * const pRob);

        TASK_RESULT TurnCrank(Robot * const pRob);
    }
}

#endif // TASKS_H
