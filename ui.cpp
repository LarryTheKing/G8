#include "ui.h"
#include "constant.h"

namespace G8 {

extern CONSTANT_SYS CONST;

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

        ButtonBoard BB(static_cast<FEHIO::FEHIOPort>(CONST.GetVal<int>("BANK_BB", C_TYPE_INT)));

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
                        if(nIndex < nItems){
                            LCD.Clear();
                            return nIndex;}
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

            b = waitForPress(&BB);
        } while(b != BUTTON_NONE);
    }

    #define N_PLACES    10
    #define PAD_Y       3
    #define ASCII_NUM_START 0x30
    long long GetLongLong(const char * const pTitle, long long old, bool sign)
    {
        ButtonBoard BB(static_cast<FEHIO::FEHIOPort>(CONST.GetVal<int>("BANK_BB", C_TYPE_INT)));

        char vals[N_PLACES + 1] = {0};

        long long place = 1000000000;
        vals[N_PLACES] = ( old < 0 ? 1 : 0);
        for(int i = N_PLACES - 1; i >= 0; i--)
        {
            vals[i] = old / place;
            old %= place;
            place /= 10;
        }

        int     nIndex = 0;
        bool    editMode = false;

        BUTTON b = BUTTON_NONE;

        do {
            if(!editMode)
            {
                if(b == BUTTON_LEFT)
                    nIndex = (nIndex < N_PLACES + 1 ? nIndex + 1 : 0);
                else if(b == BUTTON_RIGHT)
                    nIndex = (nIndex == 0 ? N_PLACES + 1 : nIndex - 1);
                else if(b == BUTTON_CENTER)
                {
                    if(nIndex == N_PLACES)
                    {
                        if(sign)
                        {
                            if(vals[N_PLACES] == 0)
                                vals[N_PLACES] = 1;
                            else
                                vals[N_PLACES] = 0;
                        }
                    }
                    else if(nIndex != N_PLACES + 1)
                        editMode = true;
                    else
                    {
                        long long sum = vals[0];
                        long long place = 10;
                        for(int i = 1; i < N_PLACES; i++)
                        {
                            sum += vals[i] * place;
                            place *= 10;
                        }

                        if(vals[N_PLACES] == 1)
                            return -sum;

                        return sum;
                    }
                }
            } else {
                if(b == BUTTON_CENTER)
                    editMode = false;
                else if(nIndex < N_PLACES)
                {
                    if(b == BUTTON_LEFT)
                        vals[nIndex] = (vals[nIndex] > 0 ? vals[nIndex] - 1 : 9);
                    else if(b == BUTTON_RIGHT)
                        vals[nIndex] = (vals[nIndex] < 9 ? vals[nIndex] + 1 : 0);
                }
            }

            // Clear the screen and write the title
            LCD.Clear();
            if(pTitle){
                LCD.WriteLine(pTitle); }

            // Pad Y
            for(int i = 0; i < PAD_Y; i++)
                LCD.WriteLine(' ');

            // Draw top markers
            LCD.Write(nIndex == N_PLACES + 1 ? "  ||||  " : "        ");
            LCD.Write(nIndex == N_PLACES ? "| " : "  ");

            for(int i = N_PLACES - 1; i >= 0; i--)
            {
                LCD.Write(i == nIndex ? (editMode ? '^' : '|') : ' ');
                if(i % 3 == 0 && i != 0)
                    LCD.Write(' ');
            }
            LCD.WriteLine(' ');

            // Draw text
            LCD.Write("  Done  ");
            LCD.Write(vals[N_PLACES] == 1 ? "- " : "+ ");

            for(int i = N_PLACES - 1; i >= 0; i--)
            {
                LCD.Write((char)(vals[i] + ASCII_NUM_START));
                if(i % 3 == 0 && i != 0)
                    LCD.Write(',');
            }
            LCD.WriteLine(' ');

            // Draw bottom markers
            LCD.Write(nIndex == N_PLACES + 1 ? "  ||||  " : "        ");
            LCD.Write(nIndex == N_PLACES ? "| " : "  ");

            for(int i = N_PLACES - 1; i >= 0; i--)
            {
                LCD.Write(i == nIndex ? (editMode ? 'v' : '|') : ' ');
                if(i % 3 == 0 && i != 0)
                    LCD.Write(' ');
            }
            LCD.WriteLine(' ');

            b = waitForPress(&BB);
        } while(b != BUTTON_NONE);
    }

    int GetInt(const char * const pTitle, int old)
    {
        // Get a value
        long long sum = GetLongLong(pTitle, old, true);

        // Check that it is within bounds
        if(sum > __INT32_MAX__)
            return __INT32_MAX__;
        else if(sum < - (__INT32_MAX__))
            return -(__INT32_MAX__);
        else
            return (int)sum;    // Return the int
    }

    unsigned int GetIntU(const char * const pTitle, unsigned int old)
    {
        // Get a value
        long long sum = GetLongLong(pTitle, old, false);

        // Check that it is within bounds
        if(sum > __UINT32_MAX__)
            return __UINT32_MAX__;
        else if(sum < 0)
            return 0;
        else
            return (unsigned int)sum;   // Return unsigned int
    }

    float GetFloat(char const * const pTitle, float old)
    {
        ButtonBoard BB(static_cast<FEHIO::FEHIOPort>(CONST.GetVal<int>("BANK_BB", C_TYPE_INT)));

        char vals[N_PLACES + 1] = {0};

        if(old < 0){
            vals[N_PLACES] = 1;
            old = -old;
        }
        else
            vals[N_PLACES] = 0;

        int exponent = 0;
        while(old > 999999.0f)
        {
            old /= 10.0f;
            exponent++;
        }

        while(old < 99999.0f)
        {
            old *= 10;
            exponent--;
        }

        long long place = 100000;
        int iOld = old;
        for(int i = N_PLACES - 1; i >= 4; i--)
        {
            vals[i] = iOld / place;
            iOld %= place;
            place /= 10;
        }

        if(exponent < 0){
            vals[3] = 1;
            exponent = -exponent;
        }
        else
            vals[3] = 0;

        place = 100;
        for(int i = 2; i >= 0; i--)
        {
            vals[i] = exponent / place;
            exponent %= place;
            place /= 10;
        }




        int     nIndex = 4;
        bool    editMode = false;

        BUTTON b = BUTTON_NONE;

        do {
            if(!editMode)
            {
                if(b == BUTTON_LEFT)
                    nIndex = (nIndex < N_PLACES + 1 ? nIndex + 1 : 0);
                else if(b == BUTTON_RIGHT)
                    nIndex = (nIndex == 0 ? N_PLACES + 1 : nIndex - 1);
                else if(b == BUTTON_CENTER)
                {
                    if(nIndex == N_PLACES || nIndex == 3)
                    {
                        if(vals[nIndex] == 0)
                            vals[nIndex] = 1;
                        else
                            vals[nIndex] = 0;
                    }
                    else if(nIndex != N_PLACES + 1)
                        editMode = true;
                    else
                    {
                        char * pString = new char[0xF];
                        memset(pString, 0x00, 0xF);
                        size_t si = 0;
                        if(vals[N_PLACES])
                            pString[si++] = '-';

                        for(int i = N_PLACES - 1; i >= 0; i--)
                        {
                            pString[si++] = (vals[i] + ASCII_NUM_START);
                            if(i == 4)
                            {
                                if(vals[3]){
                                    pString[si++]='E';
                                    pString[si++]='-';
                                } else {
                                    pString[si++]='E';
                                }
                                i--;
                            }
                        }

                        float result = atof(pString);
                        delete pString;
                        return result;
                    }
                }
            } else {
                if(b == BUTTON_CENTER)
                    editMode = false;
                else if(nIndex < N_PLACES)
                {
                    if(b == BUTTON_LEFT)
                        vals[nIndex] = (vals[nIndex] > 0 ? vals[nIndex] - 1 : 9);
                    else if(b == BUTTON_RIGHT)
                        vals[nIndex] = (vals[nIndex] < 9 ? vals[nIndex] + 1 : 0);
                }
            }

            // Clear the screen and write the title
            LCD.Clear();
            if(pTitle){
                LCD.WriteLine(pTitle); }

            // Pad Y
            for(int i = 0; i < PAD_Y; i++)
                LCD.WriteLine(' ');

            // Draw top markers
            LCD.Write(nIndex == N_PLACES + 1 ? "  ||||  " : "        ");
            LCD.Write(nIndex == N_PLACES ? "| " : "  ");

            for(int i = N_PLACES - 1; i >= 0; i--)
            {
                LCD.Write(i == nIndex ? (editMode ? '^' : '|') : ' ');
                if(i == 4)
                    LCD.Write("  ");
            }
            LCD.WriteLine(' ');

            // Draw text
            LCD.Write("  Done  ");
            LCD.Write(vals[N_PLACES] == 1 ? "- " : "+ ");

            for(int i = N_PLACES - 1; i >= 0; i--)
            {
                LCD.Write((char)(vals[i] + ASCII_NUM_START));
                if(i == 4)
                {
                    LCD.Write(" E");
                    LCD.Write(vals[3] == 1 ? "-" : "+");
                    i--;
                }
            }
            LCD.WriteLine(' ');

            // Draw bottom markers
            LCD.Write(nIndex == N_PLACES + 1 ? "  ||||  " : "        ");
            LCD.Write(nIndex == N_PLACES ? "| " : "  ");

            for(int i = N_PLACES - 1; i >= 0; i--)
            {
                LCD.Write(i == nIndex ? (editMode ? 'v' : '|') : ' ');
                if(i == 4)
                    LCD.Write("  ");
            }
            LCD.WriteLine(' ');

            b = waitForPress(&BB);
        } while(b != BUTTON_NONE);
    }

}

} // namespace G8
