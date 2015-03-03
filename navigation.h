#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <FEHRPS.h>

#include "mobility.h"

namespace G8
{
    struct Position
    {
        float heading;
        float x;
        float y;
    };

    class Navigation
    {
    private:
        MobilitySystem * pSys;

        Position currentPos;    // The adjusted current position
        Position offsetRPS;     // The offset from RPS to current position

    public:
        /**
         * @brief Navigation
         * @param pMobilitySystem   The mobility system to be used in navigation
         *
         * @requires RPS has been initialised
         */
        Navigation(MobilitySystem * const pMobilitySystem);

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
        MobilitySystem * const GetMobilitySystem(void) { return pSys; }

        // Returns teh current position
        Position GetPosition(void) const { return currentPos; }

    public:
        /**
         * @brief Rotate the robot to a specified heading
         * @param heading The heading to rotate to
         *
         * @requires RPS is active
         */
        void RotateTo(float heading);

    };
}

#endif // NAVIGATION_H
