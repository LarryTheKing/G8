#ifndef G8_UI_H
#define G8_UI_H

#include <stdlib.h>
#include <FEHUtility.h>
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHBuzzer.h>

#define BUTTON_NONE     0x00
#define BUTTON_LEFT     0x01
#define BUTTON_CENTER   0x02
#define BUTTON_RIGHT    0x04

namespace G8 {

    namespace UI
    {
        typedef size_t BUTTON;

        size_t MenuSelect(char const * const pTitle, char const * const * const ppNames, size_t const nItems);
    }
}

#endif // G8_UI_H
