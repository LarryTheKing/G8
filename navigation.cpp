#include "navigation.h"

namespace G8
{
    Navigation::Navigation(Mobility * const pMobility)
        : pSys(pMobility)
    {
        offsetRPS.heading = offsetRPS.x = offsetRPS.y = 0.0f;
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
        pSys->RotateCCW(angle);

        angle = CalcDegreesToRotate(currentPos.heading, heading);

        // What are our tolerances
        const float ROT_TOL = CONST.GetVal<float>("ROT_TOL", C_TYPE_FLOAT);
        const float COR_POWER = CONST.GetVal<float>("COR_POWER", C_TYPE_FLOAT);

        // How many times to try and correct
        int nCorrections = CONST.GetVal<int>("MAX_COR", C_TYPE_INT);

        while((angle >  ROT_TOL  || angle < -ROT_TOL) && (nCorrections-- > 0))
        {
            UpdatePosition();
            angle = CalcDegreesToRotate(currentPos.heading, heading);
            pSys->RotateCCW(angle, COR_POWER);

        }
    }

    float distSquared(Position const a, Position const b)
    {
        float x = (b.x - a.x);
        x *= x;

        float y = (b.y - a.y);
        y *= y;

        return x + y;
    }

    void Navigation::DriveForward(float inches, float percentPower)
    {
        Position start = UpdatePosition();
        pSys->DriveForward(inches, percentPower);

        // How far off are we
        float inchesSq = inches * inches;
        float disp = inchesSq - distSquared(start, UpdatePosition());

        // What are our tolerances
        float MOV_TOL_SQ = CONST.GetVal<float>("MOV_TOL", C_TYPE_FLOAT);
        MOV_TOL_SQ *= MOV_TOL_SQ;
        const float COR_POWER = CONST.GetVal<float>("COR_POWER", C_TYPE_FLOAT);

        // How many times to try and correct
        int nCorrections = CONST.GetVal<int>("MAX_COR", C_TYPE_INT);

        while((disp > MOV_TOL_SQ || disp < -MOV_TOL_SQ) && (nCorrections-- > 0))
        {
            if(inches > 0.0f) { // Was this really a forward movement
                if(disp > 0.0f)
                    pSys->DriveForward(sqrtf(disp), COR_POWER);  // Not there yet, keep moving forwards
                else
                    pSys->DriveBackward(sqrtf(-disp), COR_POWER);// Overshot, move backward
            } else {            // Was this a backward movement in disguise?!
                if(disp > 0.0f)
                    pSys->DriveBackward(sqrtf(disp), COR_POWER); // Not there yet, keep moving backwards
                else
                    pSys->DriveForward(sqrtf(-disp), COR_POWER); // Overshot, move forward
            }

            // What is our new displacement?
            disp = inchesSq - distSquared(start, UpdatePosition());
        }

    }

    void Navigation::DriveBackward(float inches, float percentPower)
    {
        DriveForward(inches, percentPower);
    }
}

