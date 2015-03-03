#include "robot.h"

namespace G8
{
    Robot::Robot(void)
    {
        pButtons = new ButtonBoard(FEHIO::Bank3);

        pRight_encoder = new DigitalEncoder(FEHIO::P0_0);
        pLeft_encoder = new DigitalEncoder(FEHIO::P0_0);

        pRight_motor = new FEHMotor(FEHMotor::Motor0);
        pLeft_motor  = new FEHMotor(FEHMotor::Motor1);

        pCds_cell = new AnalogInputPin(FEHIO::P1_0);

        pMob = new Mobility(pRight_encoder, pLeft_encoder, pRight_motor, pLeft_motor);

        RPS.InitializeMenu();

        pNav = new Navigation(pMob);
    }
}
