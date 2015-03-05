#include "task.h"
#include <cstring>

namespace G8
{
    TaskSystem::TaskSystem(char const * const pMenuTitle)
        : nTasks(0)
    {
        // Alloc space for title and copy value
        size_t s    = strlen(pMenuTitle) + 1;
        pTitle      = reinterpret_cast<char *>(malloc(s));
        memcpy(pTitle, pMenuTitle, s);

        // Alloc space for function pointers and titles
        pTasks = reinterpret_cast<TaskFunction*>(malloc(sizeof(TaskFunction) * MAX_TASKS));
        ppNames = reinterpret_cast<char**>(malloc(sizeof(char*) * MAX_TASKS));
    }

    TaskSystem::~TaskSystem(void)
    {
        free(pTitle);
        pTitle = nullptr;

        free(pTasks);
        pTasks = nullptr;

        free(ppNames);
        ppNames = nullptr;
    }

    size_t TaskSystem::Find(const char * const pName) const
    {
        for (size_t i = 0; i < nTasks; i++)
        {
            // Check if the types and names match
            if (strcmp(ppNames[i], pName) == 0)
            {
                return i; // We found a match, return the index
            }
        }

        // Return the UINT32_MAX
        return __UINT32_MAX__;
    }

    TASK_RESULT TaskSystem::RunTask(const size_t index, Robot * const pRobot) const
    {
        if(index < nTasks)
            return pTasks[index](pRobot);

        return TASK_RESULT_FAIL;
    }

    TASK_RESULT TaskSystem::RunTask(const char * const pName, Robot * const pRobot) const
    {
        RunTask(Find(pName), pRobot);
    }

    TASK_RESULT TaskSystem::RunTaskFromMenu(Robot * const pRobot) const
    {
        size_t = UI::MenuSelect(pTitle, ppNames, nTasks);
        return RunTask(index, pRobot);
    }
}
