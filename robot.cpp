#include "robot.h"

namespace G8
{
    Robot::Robot(void)
    {
        ButtonBoard buttons(FEHIO::Bank3);

        DigitalEncoder right_encoder(FEHIO::P0_0);
        DigitalEncoder left_encoder(FEHIO::P0_1);

        FEHMotor right_motor(FEHMotor::Motor0);
        FEHMotor left_motor(FEHMotor::Motor1);

        AnalogInputPin  cds_cell(FEHIO::P1_0);
    }
}
