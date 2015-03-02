#include "navigation.h"
#include "core.cpp"


Navigation::Navigation(MobilitySystem * const pMobilitySystem)
    : pSys(pMobilitySystem)
{
    offsetRPS = {0.0f, 0.0f, 0.0f, 0.0f };
}

Position Navigation::GetRPS()
{
    // Get RPS position information and offset it
    Position rps;
    rps.heading = WrapAngle(RPS.Heading() + offsetRPS.heading);
    rps.x       = RPS.X() + offsetRPS.x;
    rps.y       = RPS.Y() + offsetRPS.y;
    rps.z       = RPS.Z() + offsetRPS.z;

    // Return this new offset position
    return rps;
}

Navigation::CalibrateHeading(int const newHeading)
{
    // Calculates the RPS heading to the nearest 45 deg value
    int headingRPS = (int)(RPS.Heading() / 45.0f) * 45;
    // Wrap 360 degrees to 0 degrees
    if(headingRPS == 360)
        headingRPS = 0;

    // Return the difference between the current heading
    // and the expected heading
    offsetRPS.heading = newHeading - headingRPS;
}

Navigation::CalibrateX(float pos)
{
    offsetRPS.x = pos - RPS.X();
}
Navigation::CalibrateY(float pos)
{
    offsetRPS.y = pos - RPS.Y();
}
Navigation::CalibrateX(float pos)
{
    offsetRPS.z = pos - RPS.Z();
}
