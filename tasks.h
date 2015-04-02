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

        TASK_RESULT DriveToButtons(Robot * const pRob);

        TASK_RESULT PressButtons(Robot * const pRob);

        TASK_RESULT DriveToCubby(Robot * const pRob);

        TASK_RESULT DepositSaltBag(Robot * const pRob);

        TASK_RESULT DriveToToggle(Robot * const pRob);

        TASK_RESULT PressToggle(Robot * const pRob);
    }
}

#endif // TASKS_H
