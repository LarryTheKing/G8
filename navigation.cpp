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

        const int nSamples = CONST.GetVal<int>("RPS_SAMPLES", C_TYPE_INT);
        if(nSamples > 1)
        {
            for(int i = 1; i < nSamples; i++)
            {
                Sleep(20);
                rps.heading += WrapAngle(RPS.Heading() + offsetRPS.heading);
                rps.x       += RPS.X() + offsetRPS.x;
                rps.y       += RPS.Y() + offsetRPS.y;
            }

            rps.heading /= nSamples;
            rps.x /= nSamples;
            rps.y /= nSamples;
        }

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

        LCD.Write("H Offset : ");
        LCD.WriteLine(offsetRPS.heading);
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
        // Where are we now
        UpdatePosition();
        // How much do we need to rotate
        float angle = CalcDegreesToRotate(GetPosition().heading, heading);
        // Rotate us this amount
        pSys->RotateCCW(angle);

        // Where are we now
        UpdatePosition();
        // How much more do we need to rotate
        angle = CalcDegreesToRotate(GetPosition().heading, heading);

        // What are our tolerances
        const float ROT_TOL = CONST.GetVal<float>("ROT_TOL", C_TYPE_FLOAT);
        const float COR_POWER = CONST.GetVal<float>("COR_POWER", C_TYPE_FLOAT);

        // How many times to try and correct
        int nCorrections = CONST.GetVal<int>("MAX_ROT_COR", C_TYPE_INT);

        const int   COR_TIME_MS = CONST.GetVal<int>("COR_TIME_MS", C_TYPE_INT);

        while((angle >  ROT_TOL  || angle < -ROT_TOL) && ((nCorrections--) > 0))
        {
            // Rotate us towards the correct angle
            pSys->SpinCCW(angle > 0 ? COR_TIME_MS : -COR_TIME_MS, COR_POWER);

            Sleep(80);

            // How much more do we need to rotate
            angle = CalcDegreesToRotate(UpdatePosition().heading, heading);
        }
    }

    #define DEG_RAD (360.0f / (2.0f * 3.14159f))
    void Navigation::FaceTowards(Point const point)
    {
        UpdatePosition();
        float x = point.x - GetPosition().x;
        float y = point.y - GetPosition().y;

        if(x == 0.0f && y == 0.0f)
            return;

        float desiredHeading = (y > 0 ? 90.0f : 270.0f);
        if(x != 0.0f)
        {
            desiredHeading = WrapAngle((x > 0.0f ? atanf(y / x) * DEG_RAD : atanf(y / x) * DEG_RAD + 180.0f));
        }

        RotateTo(desiredHeading);
    }

    void Navigation::FaceAway(Point const point)
    {
        float x = GetPosition().x - point.x;
        float y = GetPosition().y - point.y;

        if(x == 0.0f && y == 0.0f)
            return;

        float desiredHeading = (y > 0 ? 90.0f : 270.0f);
        if(x != 0.0f)
        {
            desiredHeading = WrapAngle((x > 0.0f ? atanf(y / x) * DEG_RAD : atanf(y / x) * DEG_RAD + 180.0f));
        }

        RotateTo(desiredHeading);
    }

    float distSquared(Position const a, Position const b)
    {
        float x = (b.x - a.x);
        x *= x;

        float y = (b.y - a.y);
        y *= y;

        return x + y;
    }

    float dist(Position const a, Position const b)
    {
        return sqrtf(distSquared(a, b));
    }

    void Navigation::DriveForward(float inches, float percentPower)
    {
        LCD.Write("Drive forward(in) ");
        LCD.WriteLine(inches);
        Position start = UpdatePosition();
        pSys->DriveForward(inches, percentPower);

        // How far off are we
        float disp = (inches > 0 ? inches : - inches) - dist(start, UpdatePosition());

        // What are our tolerances
        float MOV_TOL= CONST.GetVal<float>("MOV_TOL", C_TYPE_FLOAT);
        const float COR_POWER = CONST.GetVal<float>("COR_POWER", C_TYPE_FLOAT);

        // How many times to try and correct
        int nCorrections = CONST.GetVal<int>("MAX_MOV_COR", C_TYPE_INT);

        while((disp > MOV_TOL || disp < -MOV_TOL) && (nCorrections-- > 0))
        {
            if(inches > 0.0f) { // Was this really a forward movement
                    pSys->DriveForward(disp, COR_POWER);  // Not there yet, keep moving forwards
            } else {            // Was this a backward movement in disguise?!
                    pSys->DriveBackward(disp, COR_POWER); // Not there yet, keep moving backwards
            }

            // What is our new displacement?
            disp = (inches > 0 ? inches : - inches) - dist(start, UpdatePosition());
        }

        LCD.WriteLine("DONE");
    }

    void Navigation::DriveBackward(float inches, float percentPower)
    {
        DriveForward(-inches, percentPower);
    }

    void Navigation::DriveForwardTo(const Point point, const float percentPower)
    {
        // Face towards the poit
        FaceTowards(point);

        // How far do we have to drive
        UpdatePosition();
        float x = point.x - GetPosition().x;
        float y = point.y - GetPosition().y;
        float dist = sqrtf(x * x + y * y);

        // Drive forward this distance
        DriveForward(dist, percentPower);
    }

    void Navigation::DriveBackwardTo(const Point point, const float percentPower)
    {
        // Face towards the poit
        FaceAway(point);

        // How far do we have to drive
        UpdatePosition();
        float x = point.x - GetPosition().x;
        float y = point.y - GetPosition().y;
        float dist = sqrtf(x * x + y * y);

        // Drive forward this distance
        DriveBackward(dist, percentPower);
    }
}

