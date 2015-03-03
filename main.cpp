#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>



#include "mobility.h"
#include "navigation.h"

#include "devices.h"
#include "global.h"

//Declarations for encoders & motors
ButtonBoard buttons(FEHIO::Bank3);

DigitalEncoder right_encoder(FEHIO::P0_0);
DigitalEncoder left_encoder(FEHIO::P0_1);

FEHMotor right_motor(FEHMotor::Motor0);
FEHMotor left_motor(FEHMotor::Motor1);

AnalogInputPin  cds_cell(FEHIO::P1_0);

int main(void)
{
    G8::DefineConstants();
    using namespace G8;

    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );

    Mobility * mSys
            = new Mobility(&right_encoder, &left_encoder,
                                 &right_motor, &left_motor);

    RPS.InitializeMenu();

    Navigation * pNav = new Navigation(mSys);

    pNav->CalibrateHeading(270);

    LCD.WriteLine("0 deg");
    pNav->RotateTo(0.0f);

    Sleep(2000);

    LCD.WriteLine("90 deg");
    pNav->RotateTo(90.0f);

    Sleep(2000);

    LCD.WriteLine("270 deg");
    pNav->RotateTo(270.0f);

    Sleep(2000);

    LCD.WriteLine("180 deg");
    pNav->RotateTo(180.0f);

    Sleep(2000);

    return 0;
}

