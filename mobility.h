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
        * @brief Moves the robot forwards
        * @param Distance The distance the robot must travel
        * @param Power The motor power
        *
        * @requires 0 < percentPower <= 100
        */
        void DriveForward(float inches, float percentPower);

        /**
        * @brief Moves the robot backwards
        * @param inches     The distance the robot must travel
        * @param percent    Power The motor power
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
    };
}

#endif // MOBILITY_H
