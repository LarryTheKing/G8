#include "mobility.h"

namespace G8
{
    /**
    * @brief InchToTick Converts a distance and power to number of ticks
    * @param distance   The distance in inches
    * @param power      The motor power
    *
    * @requires 0 < Power <= 100 and Distance > 0
    */
    int InchToTick(float distance, int power)
    {
        return distance * TICK_INCH;// * TICK_POWER / power;
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
        float val = angle * TICK_DEG;
        return (val > 0 ? val : -val);
    }

    void MobilitySystem::DriveForward(float inches, int power)
    {
        //Reset encoder counts
        pEncoderR->ResetCounts();
        pEncoderL->ResetCounts();

        // Calculate how many ticks we'll encounter
        int counts = InchToTick(inches > 0 ? inches : -inches, power);

        //Set both motors to desired percent
        pMotorR->SetPercent((inches > 0 ? power : - power) * MOD_RIGHT);
        pMotorL->SetPercent((inches > 0 ? power : - power) * MOD_LEFT);

        //While the average of the left and right encoder are less than counts,
        //keep running motors
        while((pEncoderL->Counts() + pEncoderR->Counts()) / 2 < counts);

        //Turn off motors
        pMotorR->Stop();
        pMotorL->Stop();
    }

    void MobilitySystem::DriveBackward(float inches, int power)
    {
        DriveForward(-inches, power);
    }

    void MobilitySystem::RotateLeft(float deg, float power)
    {
        //Reset encoder counts
        pEncoderR->ResetCounts();
        pEncoderL->ResetCounts();

        // Calculate how many ticks we'll encounter
        int counts = DegToTick(deg);

        //Set both motors to desired percent
        pMotorR->SetPercent((deg > 0 ? power : -power) * MOD_RIGHT);
        pMotorL->SetPercent((deg > 0 ? -power : power) * MOD_LEFT);

        //While the average of the left and right encoder are less than counts,
        //keep running motors
        while((pEncoderL->Counts() + pEncoderR->Counts()) / 2 < counts);

        //Turn off motors
        pMotorR->Stop();
        pMotorL->Stop();
    }

    void MobilitySystem::RotateRight(float deg, float power)
    {
        RotateLeft(-deg, power);
    }
}
