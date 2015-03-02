#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>

#include "mobility.h"

#include "devices.cpp"

//Declarations for encoders & motors
ButtonBoard buttons(FEHIO::Bank3);

DigitalEncoder right_encoder(FEHIO::P0_0);
DigitalEncoder left_encoder(FEHIO::P0_1);

FEHMotor right_motor(FEHMotor::Motor0);
FEHMotor left_motor(FEHMotor::Motor1);

AnalogInputPin  cds_cell(FEHIO::P1_0);

int main(void)
{
    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );

    MobilitySystem * mSys
            = new MobilitySystem(&right_encoder, &left_encoder,
                                 &right_motor, &left_motor);

    while(GetCdSIntensity(&cds_cell) > 0.2f);

    mSys->DriveForward(14.0, 70);

    mSys->RotateLeft(90.0f);

    mSys->DriveForward(11.5, 70);

    mSys->RotateLeft(90.0f);

    mSys->DriveForward(42.0, 70);

    return 0;
}

