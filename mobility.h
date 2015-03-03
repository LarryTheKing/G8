#ifndef MOBILITY_H
#define MOBILITY_H

#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>

#define TICK_INCH   2.778f // Motor ticks per inch of travel at 100 percent power
#define TICK_DEG    85.5f / 360.0f
#define TICK_POWER  1.0f / 100.0f

#define MOD_LEFT    (59.0f / 60.0f)
#define MOD_RIGHT    1.0f

#define COR_POWER   55
#define ROT_POWER   60

namespace G8
{
    class MobilitySystem
    {
    private:
        DigitalEncoder * pEncoderR;
        DigitalEncoder * pEncoderL;
        FEHMotor * pMotorR;
        FEHMotor * pMotorL;
    public:
        MobilitySystem(DigitalEncoder * const pRightEncoder,
                       DigitalEncoder * const pLeftEncoder,
                       FEHMotor * const pRightMotor,
                       FEHMotor * const pLeftMotor) :
            pEncoderR(pRightEncoder), pEncoderL(pLeftEncoder),
            pMotorR(pRightMotor), pMotorL(pLeftMotor) {}

    public:
        /**
        * @brief Moves the robot forward Distance at Power
        * @param Distance The distance the robot must travel
        * @param Power The motor power
        *
        * @requires 0 < Power <= 100
        */
        void DriveForward(float inches, int power);

        /**
        * @brief Moves the robot backward Distance at Power
        * @param Distance The distance the robot must travel
        * @param Power The motor power
        *
        * @requires 0 < Power <= 100
        */
        void DriveBackward(float inches, int power);

        /**
         * @brief RotateLeft    Rotates the robot left some degrees
         * @param deg           The angle in degrees to rotate
         *
         * @requires            -180 < deg <= 180
         */
        void RotateLeft(float deg, float power = ROT_POWER);

        /**
         * @brief RotateRight    Rotates the robot right some degrees
         * @param deg           The angle in degrees to rotate
         *
         * @requires            -180 < deg <= 180
         */
        void RotateRight(float deg, float power = ROT_POWER);
    };
}

#endif // MOBILITY_H
