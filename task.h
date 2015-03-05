#ifndef TASK_H
#define TASK_H

#include <stdlib.h>
#include "robot.h"
#include "ui.h"

#define TASK_RESULT_FAIL        80000000
#define TASK_RESULT_SUCCESS     40000000

#define MAX_TASKS 256

namespace G8
{
    typedef size_t TASK_RESULT;

    typedef TASK_RESULT (*TaskFunction) (Robot *);

    class TaskSystem
    {
        TaskFunction *  pTasks;
        char**          ppNames;
        char*           pTitle;
        size_t          nTasks;
    public:
        TaskSystem(char const * const pMenuTitle);
        ~TaskSystem(void);

    public:
        size_t GetLength(void) const { return nTasks; }

    public:
        /**
        * @brief Finds the index to a TaskFunction
        * @param pName The null terminated name of the Task
        * @return Returns the index of the first corresponding TaskFunction,
        * or UINT32_MAX if not found
        */
        size_t Find(char const * const pName) const;

        /**
         * @brief Runs a TaskFunction using the robot
         * @param index     The index of the task to run
         * @param pRobot    The Robot to run the task using
         * @return RunTask = the return value from the Task
         */
        TASK_RESULT RunTask(size_t const index, Robot * const pRobot) const;

        /**
         * @brief Runs a TaskFunction using the robot
         * @param pName     The name of the task to run
         * @param pRobot    The Robot to run the task using
         * @return RunTask = the return value from the Task
         */
        TASK_RESULT RunTask(char const * const pName, Robot * const pRobot) const;

        /**
         * @brief Selects a Task from a menu and runs the TaskFunction using the robot
         * @param pRobot    The Robot to run the task using
         * @return RunTaskFromMenu = the return value from the Task
         */
        TASK_RESULT RunTaskFromMenu(Robot * const pRobot) const ;

        void AddTask(char const * const pName, TaskFunction pFunc);
    };
}

#endif // TASK_H
