#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>

#include "robot.h"
#include "global.h"

int main(void)
{
    using namespace G8;

    LCD.Clear();

    DefineConstants();
    DefineTasks();

    Robot * pRob = new Robot();

    while(TASK.RunTaskFromMenu(pRob) != TASK_RESULT_FAIL);

    delete pRob;

    return 0;
}

