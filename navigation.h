#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <FEHLCD.h>
#include <FEHRPS.h>
#include <math.h>

#include "core.h"
#include "global.h"
#include "mobility.h"

namespace G8
{

    struct Point
    {
        float x;
        float y;
    };

    struct Position
    {
        float heading;
        union
        {
            Point point;
            struct{
                float x;
                float y;
            };
        };
    };

    class Navigation
    {
    private:
        Mobility * pSys;

        Position currentPos;    // The adjusted current position
        Position offsetRPS;     // The offset from RPS to current position

    public:
        /**
         * @brief Navigation
         * @param pMobility   The mobility system to be used in navigation
         *
         * @requires RPS has been initialised
         */
        Navigation(Mobility * const pMobility);

        /**
         * @brief Fetches RPS position and offsets it
         * @return Returns the offset RPS position
         *
         * @updates currentPos
         *
         * @requires RPS has been initialised
         */
        Position UpdatePosition(void);

        /**
         * @brief Calibrates the heading system to a (45 deg x N) offset of RPS
         * @param newHeading The desired current heading
         *
         * @requires RPS is activated, newHeading is a scalar mutiple 45 deg
         */
        void CalibrateHeading(int const newHeading);
        /**
         * @brief Calibrates the position in the X direction to a certain value
         * @param pos The global X position to satisfy
         */
        void CalibrateX(float pos);
        /**
         * @brief Calibrates the position in the Y direction to a certain value
         * @param pos The global Y position to satisfy
         */
        void CalibrateY(float pos);

    public:
        // Returns a pointer to the mobility system
        Mobility * const GetMobility(void) { return pSys; }

        // Returns the current position
        Position GetPosition(void) const { return currentPos; }

    public:
        /**
         * @brief Rotate the robot to a specified heading
         * @param heading The heading to rotate to
         *
         * @requires RPS is active
         */
        void RotateTo(float heading);

        void FaceTowards(Point const point);

        void FaceAway(Point const point);

        /**
         * @brief Drives the robot forward a specified distance
         * @param inches        The distance to travel
         * @param percentPower  The desired power as a percent
         */
        void DriveForward(float inches, float percentPower);

        /**
         * @brief Drives the robot backward a specified distance
         * @param inches        The distance to travel
         * @param percentPower  The desired power as a percent
         */
        void DriveBackward(float inches, float percentPower);


        /**
         * @brief Drives the robot forward to a specific point
         * @param inches        The point to drive to
         * @param percentPower  The desired power as a percent
         */
        void DriveForwardTo(Point const point, float const percentPower);

        /**
         * @brief Drives the robot backward to a specific point
         * @param inches        The point to drive to
         * @param percentPower  The desired power as a percent
         */
        void DriveBackwardTo(Point const point, float const percentPower);

    };
}

#endif // NAVIGATION_H
