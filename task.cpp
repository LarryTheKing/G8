#include "task.h"

#define nullptr NULL

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

        memset(pTasks, 0x00, sizeof(TaskFunction) * MAX_TASKS );
        memset(ppNames, 0x00, sizeof(char*) * MAX_TASKS);
    }

    TaskSystem::~TaskSystem(void)
    {
        free(pTitle);
        pTitle = nullptr;

        free(pTasks);
        pTasks = nullptr;

        for(size_t i = 0; i < MAX_TASKS; i++)
        {
            if(ppNames[i])
            {
                free(ppNames[i]);
                ppNames[i] = nullptr;
            }
        }

        free(ppNames);
        ppNames = nullptr;
    }

    size_t TaskSystem::Find(const char * const pName) const
    {
        for (size_t i = 0; i < nTasks; i++)
        {
            // Check if the names match
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
        size_t index = UI::MenuSelect(pTitle, ppNames, nTasks);
        return RunTask(index, pRobot);
    }

    bool TaskSystem::AddTask(const char * const pName, TaskFunction pFunc)
    {
        // Is there any space left to store this task
        if(nTasks >= MAX_TASKS)
            return false;

        // Store the function pointer
        pTasks[nTasks] = pFunc;

        // Store the name
        size_t sSize = strlen(pName) + 1;

        if(ppNames[nTasks] = reinterpret_cast<char*>(malloc(sSize)))
            memcpy(ppNames[nTasks], pName, sSize);
        else
            return false;

        // Increment number of tasks
        nTasks++;

        // All done!
        return true;
    }
}
