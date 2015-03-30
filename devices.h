#ifndef DEVICES_H
#define DEVICES_H

#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>

#include "core.h"
#include "global.h"

namespace G8
{
    ///////////////////////////////////////////////////
    // CdS Cell section
    ///////////////////////////////////////////////////
    /**
    * Reads the avreage intensity from a CdS cell
    * @param pPin   The AnalogInputPin to read from
    * @requires     The CdS cell exists
    * @ensures      GetCdSIntensity returns a floating point value [0.0f, 1.0f]
    */
    float GetCdSIntensity(AnalogInputPin * const pPin);

    enum LIGHT {
        LIGHT_NONE   = 0x00,
        LIGHT_RED    = 0x01,
        LIGHT_BLUE   = 0x02,
        LIGHT_BRIGHT = 0xFF
    };

    /**
    * Reads from the CdS sensor for ⅕ second and returns what color it sees
    * @param pPin   The AnalogInputPin to read from
    * @requires     The CdS cell exists and has a yellow filter over it
    * @ensures      ReadCdS returns an integer : {LIGHT_NONE, LIGHT_RED, LIGHT_BLUE }
    */
    LIGHT ReadCdS(AnalogInputPin * const pPin);

}

#endif // DEVICES_H
