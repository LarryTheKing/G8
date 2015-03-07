#include "diagnostic.h"
#include "ui.h"
#include "global.h"
#include "robot.h"

#include <FEHBuzzer.h>
#include <new>

namespace G8 {

namespace Tasks {

#define TASK_RESULT_QUIT    0x20000000
TASK_RESULT Quit(Robot * const pRob)
{
    return TASK_RESULT_SUCCESS | TASK_RESULT_QUIT;
}

TASK_RESULT RedfineConstants(Robot * const pRob)
{
    FEHBuzzer buzz;

    const size_t length = CONST.GetLength() + 1;
    char const ** ppNames = new char const *[length]; // Ignore first constant; add one for Quit
    ppNames[0] = "Quit";
    ppNames[length - 1] = "!!!RESET ALL!!!";
    for(int i = 1; i < CONST.GetLength(); i++)
    {
        ppNames[i] = CONST.GetName(i);
    }

    while(size_t index = UI::MenuSelect("Select a constant", ppNames, length))
    {
        if(index == length -1)
        {
            // Delete and rebuild constants
            CONST.~CONSTANT_SYS();
            new (&CONST) CONSTANT_SYS();
            DefineConstants();
            // Show message
            LCD.WriteLine("All CONSTANTS reset!");
            Sleep(2000);
        }else{
            switch(CONST.GetType(index))
            {
            case C_TYPE_INT:
                CONST.Redefine<int>(index, UI::GetInt(CONST.GetName(index), CONST.GetVal<int>(index)));
                break;
            case C_TYPE_INT | C_TYPE_UNSIGNED:
                CONST.Redefine<unsigned int>(index, UI::GetIntU(CONST.GetName(index), CONST.GetVal<unsigned int>(index)));
                break;
            default:
                buzz.Beep();
                break;
            }
        }
    }

    delete ppNames;

    return TASK_RESULT_SUCCESS;
}

TASK_RESULT RebuildRobot(Robot * const pRob)
{
    pRob->~Robot();

    if(new (pRob) Robot())
    {
        LCD.WriteLine("Rebuild successful");
        Sleep(2000);
        return TASK_RESULT_SUCCESS;
    }

    LCD.WriteLine("Rebuild failed");
    Sleep(2000);
    return TASK_RESULT_FAIL;
}

TASK_RESULT Diagnostics(Robot * const pRob)
{
    TaskSystem sys("Choose a diagnostic");
    sys.AddTask("Quit", Quit);
    sys.AddTask("Redefine constants", RedfineConstants);
    sys.AddTask("Rebuild Robot", RebuildRobot);

    while(true)
    {
        TASK_RESULT r = sys.RunTaskFromMenu(pRob);
        if((r & TASK_RESULT_QUIT) == TASK_RESULT_QUIT)
            return TASK_RESULT_SUCCESS;
        else if((r & TASK_RESULT_FAIL) == TASK_RESULT_FAIL)
            return r;
    }

    // We shouldn't get here
    return TASK_RESULT_FAIL;
}

}

} // namespace G8
