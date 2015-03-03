#include "navigation.h"
#include "core.cpp"

namespace G8
{
    Navigation::Navigation(Mobility * const pMobility)
        : pSys(pMobility)
    {
        offsetRPS = {0.0f, 0.0f, 0.0f };
    }

    Position Navigation::UpdatePosition()
    {
        // Get RPS position information and offset it
        Position rps;
        rps.heading = WrapAngle(RPS.Heading() + offsetRPS.heading);
        rps.x       = RPS.X() + offsetRPS.x;
        rps.y       = RPS.Y() + offsetRPS.y;

        currentPos = rps;

        // Return this new offset position
        return rps;
    }

    void Navigation::CalibrateHeading(int const newHeading)
    {
        // Calculates the RPS heading to the nearest 45 deg value
        int headingRPS = (int)((RPS.Heading() + 22.5f)/ 45.0f) * 45;
        // Wrap 360 degrees to 0 degrees
        if(headingRPS == 360)
            headingRPS = 0;

        // Return the difference between the current heading
        // and the expected heading
        offsetRPS.heading = newHeading - headingRPS;
    }

    void Navigation::CalibrateX(float pos)
    {
        offsetRPS.x = pos - RPS.X();
    }
    void Navigation::CalibrateY(float pos)
    {
        offsetRPS.y = pos - RPS.Y();
    }

    void Navigation::RotateTo(float heading)
    {
        UpdatePosition();

        float angle = CalcDegreesToRotate(currentPos.heading, heading);
        pSys->RotateRight(angle);

        angle = CalcDegreesToRotate(currentPos.heading, heading);

        while(angle >  1.0f  || angle < -1.0f)
        {
            UpdatePosition();
            angle = CalcDegreesToRotate(currentPos.heading, heading);
            pSys->RotateLeft(angle, COR_POWER);

        }
    }
}

