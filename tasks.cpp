#include "robot.h"

#include "devices.cpp"

namespace G8
{
    static void PerfTest1(Robot const * pRob)
    {
        while(GetCdSIntensity(&cds_cell) > 0.2f);

        pRob->pMobility->DriveForward(14.0, 70);

        pRob->pMobility->RotateCCW(90.0f);

        pRob->pMobility->DriveForward(11.5, 70);

        pRob->pMobility->RotateCCW(90.0f);

        pRob->pMobility->DriveForward(42.0, 70);
    }
}
