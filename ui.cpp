#include "ui.h"

namespace G8 {

namespace UI
{

    BUTTON getState(ButtonBoard * const pBB)
    {
        BUTTON state = BUTTON_NONE;
        if(pBB->LeftPressed())
            state |= BUTTON_LEFT;
        if(pBB->MiddlePressed())
            state |= BUTTON_CENTER;
        if(pBB->RightPressed())
            state |= BUTTON_RIGHT;

        return state;
    }

    BUTTON getPressed(BUTTON const oldB, BUTTON const newB)
    {
        return (~oldB) & newB;
    }

    BUTTON waitForPress(ButtonBoard * const pBB)
    {
        FEHBuzzer buzz;

        BUTTON oState = getState(pBB);

        while(true)
        {
            BUTTON nState = getState(pBB);
            BUTTON nPressed = getPressed(oState, nState);

            if(nPressed == BUTTON_LEFT){
                buzz.Tone(FEHBuzzer::F4, 60);
                return BUTTON_LEFT; }
            else if(nPressed == BUTTON_CENTER){
                buzz.Tone(FEHBuzzer::C5, 60);
                return BUTTON_CENTER; }
            else if(nPressed == BUTTON_RIGHT){
                buzz.Tone(FEHBuzzer::F5, 60);
                return BUTTON_RIGHT; }

            oState = nState;

            Sleep(20);
        }
    }

    #define ITEMS_PAGE 12
    size_t MenuSelect(char const * const pTitle, char const * const * const ppNames, size_t const nItems)
    {
        FEHBuzzer buzz;

        ButtonBoard * pBB = new ButtonBoard(
                    static_cast<FEHIO::FEHIOPort>(CONST.GetVal<int>("BANK_BB", C_TYPE_INT)));

        const size_t nPages = nItems / ITEMS_PAGE + 1;
        size_t page = 0;
        size_t row = 0;

        bool pageMode = false;

        BUTTON b = BUTTON_NONE;

        do {
            if(pageMode)
            {
                if(b == BUTTON_LEFT)
                    page = (page > 0 ? page - 1 : nPages - 1);
                else if(b == BUTTON_RIGHT)
                    page = (page + 1 < nPages ? page + 1 : 0);
                else if(b == BUTTON_CENTER)
                    pageMode = false;
            } else {
                if(b == BUTTON_LEFT)
                    row = (row > 0 ? row - 1 : ITEMS_PAGE);
                else if(b == BUTTON_RIGHT)
                    row = (row < ITEMS_PAGE ? row + 1 : 0);
                else if(b == BUTTON_CENTER)
                {
                    if(row < ITEMS_PAGE){
                        int nIndex = page * ITEMS_PAGE + row;
                        if(nIndex < nItems)
                            return nIndex;
                        else
                            buzz.Buzz(60);
                    }
                    else if(row == ITEMS_PAGE)
                        pageMode = true;
                }
            }

            LCD.Clear();
            LCD.WriteLine(pTitle);

            for(size_t i = 0; i < ITEMS_PAGE; i++)
            {
                size_t nIndex = page * ITEMS_PAGE + i;

                LCD.Write(i == row ? '>' : ' ');

                if(nIndex < nItems)
                    LCD.WriteLine(ppNames[nIndex]);
                else
                    LCD.WriteLine(' ');
            }

            LCD.Write(row == ITEMS_PAGE ? (pageMode ? '+' : '>') : ' ');
            LCD.Write("Page ");
            LCD.Write(static_cast<int>(page) + 1);
            LCD.Write(" / ");
            LCD.WriteLine(static_cast<int>(nPages));

            b = waitForPress(pBB);
        } while(b != BUTTON_NONE);
    }
}

} // namespace G8
