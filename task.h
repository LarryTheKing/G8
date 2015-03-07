#ifndef TASK_H
#define TASK_H

#include <stdlib.h>
#include <string.h>
#include "ui.h"

#define TASK_RESULT_FAIL        80000000
#define TASK_RESULT_SUCCESS     40000000

#define MAX_TASKS 256

namespace G8
{
    class Robot;

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
         * @brief   Selects a task from the menu
         * @return  SelectTaskFromMenu = the index of the selected task
         */
        size_t SelectTaskFromMenu(void) const;

        /**
         * @brief   Selects a Task from a menu and runs the TaskFunction using the robot
         * @param   pRobot    The Robot to run the task using
         * @return  RunTaskFromMenu = the return value from the Task
         */
        TASK_RESULT RunTaskFromMenu(Robot * const pRobot) const ;

        /**
         * @brief Adds a task to the TaskSystem
         * @param pName The name of the task
         * @param pFunc The pointer to the function
         *
         * @requires pName is a valid c-string no longer than 24 chars ('\0' included)
         *  pFunc is a valid pointer to a function
         */
        bool AddTask(char const * const pName, TaskFunction pFunc);
    };
}

#endif // TASK_H
