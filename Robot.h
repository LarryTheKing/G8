#ifndef ROBOT_H
#define ROBOT_H

#include "mobility.h"
#include "navigation.h"

#define PIN_RIGHT_ENCODER
#define PIN_LEFT_ENCODER
#define PIN_CDS_CELL

namespace G8
{
    class Robot
    {
    public:
        ButtonBoard * pButtons;

        DigitalEncoder *  pRight_encoder;
        DigitalEncoder *  pLeft_encoder;

        FEHMotor * pRight_motor;
        FEHMotor * pLeft_motor;

        AnalogInputPin * pCds_cell;

    public:
        Mobility *      pMob;
        Navigation *    pNav;

        Robot(void);
    };
}

#endif // ROBOT_H
