#include "tasks.h"
#include "robot.h"
#include "devices.h"

namespace G8
{
namespace Tasks
{
    TASK_RESULT Main(Robot * const pRob)
    {
        LCD.WriteLine("Hey guys, we should really\nwork on the main code\nsometime soon.\n-Larry");
        Sleep(4000);
        return TASK_RESULT_SUCCESS;
    }

    TASK_RESULT PerfTest1(Robot * const pRob)
    {
        while(GetCdSIntensity(pRob->pCds_cell) > 0.2f);

        pRob->pMob->DriveForward(14.0, 70);

        pRob->pMob->RotateCCW(90.0f);

        pRob->pMob->DriveForward(11.5, 70);

        pRob->pMob->RotateCCW(90.0f);

        pRob->pMob->DriveForward(42.0, 70);

        return TASK_RESULT_SUCCESS;
    }

    TASK_RESULT PerfTest3(Robot * const pRob)
    {
        // Initialize RPS
        RPS.InitializeMenu();
        // Calibrate
        pRob->pNav->CalibrateHeading(270.0f);
        pRob->pNav->CalibrateX(18.0f);
        pRob->pNav->CalibrateY(30.5f);

        // Wait for light
        while(GetCdSIntensity(pRob->pCds_cell) > 0.2f);

        // Raise box
        pRob->pBag_servo->SetDegree(90);
        // Drive off light
        pRob->pNav->DriveForwardTo({17.9f, 18.0}, 80.0f);
        // Drive to salt bag
        pRob->pNav->DriveForwardTo({26.6f, 10.0f}, 80.0f);
        // Lower box
        pRob->pBag_servo->SetDegree(180);
        Sleep(500);
        // Backup a bit
        pRob->pMob->DriveBackward(3.0f, 80.0f);
        // Drive to ramp
        pRob->pNav->DriveBackwardTo({31.0f, 23.1f}, 80.0f);
        // Drive up ramp
        pRob->pNav->DriveBackwardTo({31.0f, 45.8f}, 95.0f);
        // Strafe CCW 50 deg*
        pRob->pMob->StrafeCW(50.0f, -80.0f);
        // Drive around snow
        pRob->pNav->DriveBackwardTo({22.5f, 54.8f}, 80.0f);
        // Strafe CCW 90 deg*
        pRob->pMob->StrafeCW(90.0f,-90.0f);
        // Drive by cubby
        pRob->pNav->DriveBackwardTo({9.5f, 44.0f}, 80.0f);
        // Strafe CCW 90 deg
        pRob->pMob->StrafeCCW(90.0f, 80.0f);
        // Drive Forward a bit
        pRob->pMob->DriveForward(3.0f, 80.0f);
        // Raise box
        pRob->pBag_servo->SetDegree(90);
        // Backup a bit
        pRob->pMob->DriveBackward(7.0f, 80.0f);
        // Lower Box
        pRob->pBag_servo->SetDegree(180);
        Sleep(500);
        // Drive Forwards a bit
        pRob->pMob->DriveForward(5.0f, 80.0f);
        // Backup again
        pRob->pMob->DriveBackward(8.0f, 80.0f);

        return TASK_RESULT_SUCCESS;
    }
}



}
