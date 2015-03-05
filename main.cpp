#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>

#include "global.h"
#include "robot.h"
#include "ui.h"

int main(void)
{
    G8::DefineConstants();
    using namespace G8;

    Robot * pRob = new Robot();

    LCD.Clear();

    char* pItems[] = {"Item 1", "Item 2", "Item 3", "Item 4", "Item 5", "Item 6", "Item 7",
                       "Item 8", "Item 9", "Item 10", "Item 11", "Item 12", "Item 13", "Item 14"};
    while(true)
    {
        size_t s = UI::MenuSelect("Test menu", pItems, 14);
        LCD.Clear();
        LCD.WriteLine((int)s);
        Sleep(3000);
    }

    delete pRob;

    return 0;
}

