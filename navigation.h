#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <FEHRPS.h>

#include "mobility.h"

struct Position
{
    float heading;
    float x;
    float y;
    float z;
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
     * @requires RPS has been initialised
     */
    Position GetRPS();

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
    /**
     * @brief Calibrates the position in the Z direction to a certain value
     * @param pos The global Z position to satisfy
     */
    void CalibrateZ(float pos);

};

#endif // NAVIGATION_H
