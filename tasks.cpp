#include "robot.h"

#include "devices.h"

namespace G8
{
    static void PerfTest1(Robot const * pRob)
    {
        while(GetCdSIntensity(pRob->pCds_cell) > 0.2f);

        pRob->pMob->DriveForward(14.0, 70);

        pRob->pMob->RotateCCW(90.0f);

        pRob->pMob->DriveForward(11.5, 70);

        pRob->pMob->RotateCCW(90.0f);

        pRob->pMob->DriveForward(42.0, 70);
    }
}
