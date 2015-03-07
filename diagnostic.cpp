#include "diagnostic.h"
#include "ui.h"
#include "global.h"

#include <FEHBuzzer.h>

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

    char const ** ppNames = new char const *[CONST.GetLength()]; // Ignore first constant; add one for Quit
    ppNames[0] = "Quit";
    for(int i = 1; i < CONST.GetLength(); i++)
    {
        ppNames[i] = CONST.GetName(i);
    }

    while(size_t index = UI::MenuSelect("Select a constant", ppNames, CONST.GetLength()))
    {
        index;
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

    delete ppNames;

    return TASK_RESULT_SUCCESS;
}

TASK_RESULT Diagnostics(Robot * const pRob)
{
    TaskSystem sys("Choose a diagnostic");
    sys.AddTask("Quit", Quit);
    sys.AddTask("Redefine constants", RedfineConstants);

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
