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

        /**
         * @brief Displays a menu on the screen. Prompts for a selection
         * @param pTitle    The title to display at the top
         * @param ppNames   The names to display in the menu
         * @param nItems    The number of items
         * @return returns the index of the selected name
         * @requires pTitle and the elements of ppNames are valid c-strings
         */
        size_t MenuSelect(char const * const pTitle, char const * const * const ppNames, size_t const nItems);


        /**
         * @brief Prompts for an integer
         * @param pTitle    The title to display at the top
         * @param old       The old value to display on the screen
         * @return          Returns an __INT32_MIN <= integer <= __INT32_MAX
         */
        int GetInt(char const * const pTitle = NULL, int old = 0);

        /**
         * @brief Prompts for an unsigned integer
         * @param pTitle    The title to display at the top
         * @param old       The old value to display on the screen
         * @return          Returns an 0 <= integer <= __UINT32_MAX
         */
        unsigned int GetIntU(char const * const pTitle = NULL, unsigned int old = 0);

        /**
         * @brief Prompts for float
         * @param pTitle    The title to display at the top
         * @param old       The old value to display on the screen
         * @return          Returns a floating point value
         */
        float GetFloat(char const * const pTitle = NULL, float old = 0);

    }
}

#endif // G8_UI_H
