#include "mobility.h"

namespace G8
{
    /**
    * @brief InchToTick Converts a distance and power to number of ticks
    * @param distance   The distance in inches
    *
    * @requires Distance > 0
    */
    int InchToTick(float distance)
    {
        return distance * CONST.GetVal<float>("TICK_INCH", C_TYPE_FLOAT);
    }

    /**
    * @brief DegToTick  Converts an angle to number of ticks
    * @param angle      The angle in degrees
    *
    * @requires -180 < angle <= 180
    * @ensures DegToTick is nonnegative
    */
    int DegToTick(float angle)
    {
        float val = angle * CONST.GetVal<float>("TICK_DEG", C_TYPE_FLOAT);
        return (val > 0 ? val : -val);
    }

    void Mobility::DriveForward(float inches, float percentPower)
    {
        //Reset encoder counts
        pEncoderR->ResetCounts();
        pEncoderL->ResetCounts();

        // Calculate how many ticks we'll encounter
        int counts = InchToTick(inches > 0 ? inches : -inches);

        if(counts == 0) {
            counts = 1; }

        //Set both motors to desired percent
        pMotorR->SetPercent((inches > 0 ? percentPower : - percentPower) * CONST.GetVal<float>("MOD_RIGHT", C_TYPE_FLOAT));
        pMotorL->SetPercent((inches > 0 ? percentPower : - percentPower) * CONST.GetVal<float>("MOD_LEFT", C_TYPE_FLOAT));

        //While the average of the left and right encoder are less than counts,
        //keep running motors
        while((pEncoderL->Counts() + pEncoderR->Counts()) / 2 < counts);

        //Turn off motors
        pMotorR->Stop();
        pMotorL->Stop();
    }

    void Mobility::DriveBackward(float inches, float percentPower)
    {
        DriveForward(-inches, percentPower);
    }

    void Mobility::RotateCCW(float deg, float percentPower)
    {
        //Reset encoder counts
        pEncoderR->ResetCounts();
        pEncoderL->ResetCounts();

        // Calculate how many ticks we'll encounter
        int counts = DegToTick(deg);

        //Set both motors to desired percent
        pMotorR->SetPercent((deg > 0 ? percentPower : -percentPower) * CONST.GetVal<float>("MOD_RIGHT", C_TYPE_FLOAT));
        pMotorL->SetPercent((deg > 0 ? -percentPower : percentPower) * CONST.GetVal<float>("MOD_LEFT", C_TYPE_FLOAT));

        //While the average of the left and right encoder are less than counts,
        //keep running motors
        while((pEncoderL->Counts() + pEncoderR->Counts()) / 2 < counts);

        //Turn off motors
        pMotorR->Stop();
        pMotorL->Stop();
    }

    void Mobility::RotateCW(float deg, float percentPower) {
        RotateCCW(-deg, percentPower); }

    void Mobility::RotateCCW(float deg){
        RotateCCW(deg, CONST.GetVal<float>("ROT_POWER", C_TYPE_FLOAT));}
    void Mobility::RotateCW(float deg){
        RotateCCW(-deg, CONST.GetVal<float>("ROT_POWER", C_TYPE_FLOAT));}

    void Mobility::StrafeCCW(float deg, float percentPower)
    {
        //Reset encoder counts
        pEncoderR->ResetCounts();
        pEncoderL->ResetCounts();

        // Calculate how many ticks we'll encounter
        int counts = DegToTick(deg);

        //Set both motors to desired percent
        if(deg > 0)
            pMotorR->SetPercent(percentPower * CONST.GetVal<float>("MOD_RIGHT", C_TYPE_FLOAT));
        else
            pMotorL->SetPercent(percentPower * CONST.GetVal<float>("MOD_LEFT", C_TYPE_FLOAT));

        //While the average of the left and right encoder are less than counts,
        //keep running motors
        while((pEncoderL->Counts() + pEncoderR->Counts()) / 2 < counts);

        //Turn off motors
        pMotorR->Stop();
        pMotorL->Stop();
    }

    void Mobility::StrafeCW(float deg, float percentPower) {
        StrafeCCW(-deg, percentPower); }

    void Mobility::StrafeCCW(float deg){
        StrafeCCW(deg, CONST.GetVal<float>("ROT_POWER", C_TYPE_FLOAT));}
    void Mobility::StrafeCW(float deg){
        StrafeCCW(-deg, CONST.GetVal<float>("ROT_POWER", C_TYPE_FLOAT));}

}
