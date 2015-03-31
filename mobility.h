#ifndef MOBILITY_H
#define MOBILITY_H

#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>

#include "global.h"

namespace G8
{
    class Mobility
    {
    private:
        DigitalEncoder * pEncoderR;
        DigitalEncoder * pEncoderL;
        FEHMotor * pMotorR;
        FEHMotor * pMotorL;
    public:
        Mobility(DigitalEncoder * const pRightEncoder,
                       DigitalEncoder * const pLeftEncoder,
                       FEHMotor * const pRightMotor,
                       FEHMotor * const pLeftMotor) :
            pEncoderR(pRightEncoder), pEncoderL(pLeftEncoder),
            pMotorR(pRightMotor), pMotorL(pLeftMotor) {}

    public:
        /**
        * @brief DriveForward   Moves the robot forwards
        * @param inches         The distance the robot must travel
        * @param percentPower   The motor power
        *
        * @requires 0 < percentPower <= 100
        */
        void DriveForward(float inches, float percentPower);

        /**
        * @brief DriveBackward  Moves the robot backwards
        * @param inches         The distance the robot must travel
        * @param percentPower   The motor power
        *
        * @requires 0 < percentPower <= 100
        */
        void DriveBackward(float inches, float percentPower);

        /**
         * @brief RotateLeft    Rotates the robot counter clockwise some degrees
         * @param deg           The angle in degrees to rotate
         * @param percentPower  The power to rotate at
         *
         * @requires            -180 < deg <= 180
         */
        void RotateCCW(float deg, float percentPower);
        void RotateCCW(float deg);

        /**
         * @brief RotateCW      Rotates the robot clockwise some degrees
         * @param deg           The angle in degrees to rotate
         * @param percentPower  The power to rotate at
         *
         * @requires            -180 < deg <= 180
         */
        void RotateCW(float deg, float percentPower);
        void RotateCW(float deg);

        /**
         * @brief StrafeCCW     Strafes the robot counter-clockwise some degrees
         * @param deg           The angle in degrees to rotate
         * @param percentPower  The power to rotate at
         *
         * @requires            -180 < deg <= 180
         */
        void StrafeCCW(float deg, float percentPower);
        void StrafeCCW(float deg);


        /**
         * @brief StrafeCW      Strafes the robot clockwise some degrees
         * @param deg           The angle in degrees to rotate
         * @param percentPower  The power to rotate at
         *
         * @requires            -180 < deg <= 180
         */
        void StrafeCW(float deg, float percentPower);
        void StrafeCW(float deg);

        /**
         * @brief SpinCCW       Spins the robot counter clockwise for some time
         * @param ms            The time to spin in milliseconds
         * @param percentPower  The power to spin at
         */
        void SpinCCW(int ms, float percentPower);

        /**
         * @brief SpinCCW       Spins the robot clockwise for some time
         * @param ms            The time to spin in milliseconds
         * @param percentPower  The power to spin at
         */
        void SpinCW(int ms, float percentPower);
    };
}

#endif // MOBILITY_H
