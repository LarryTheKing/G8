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
        Sleep(1000);
        //while(GetCdSIntensity(pRob->pCds_cell) > 0.2f);

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
        pRob->pNav->DriveForwardTo({17.9f, 17.5}, 80.0f);
        // Drive to salt bag
        pRob->pNav->DriveForwardTo({27.3f, 9.0f}, 80.0f);

        pRob->pNav->RotateTo(315.0f);
        // Lower box
        pRob->pBag_servo->SetDegree(180);
        Sleep(500);
        // Backup a bit
        pRob->pMob->DriveBackward(3.0f, 80.0f);
        // Drive to ramp
        pRob->pNav->DriveBackwardTo({31.0f, 23.1f}, 80.0f);
        // Drive up ramp
        pRob->pNav->DriveBackwardTo({30.5f, 45.8f}, 95.0f);
        // Strafe CCW 50 deg*
        pRob->pMob->StrafeCW(50.0f, -80.0f);
        // Drive around snow
        pRob->pNav->DriveBackwardTo({22.5f, 54.8f}, 80.0f);
        // Strafe CCW 90 deg*
        pRob->pMob->StrafeCW(90.0f,-90.0f);
        // Update my position
        pRob->pNav->UpdatePosition();
        // Drive by cubby
        pRob->pNav->DriveBackwardTo({7.5f, 46.0f}, 80.0f);
        // Orient to 45 deg
        pRob->pNav->RotateTo(45.0f);
        // Drive forward 2 inches
        pRob->pMob->DriveForward(2.0f, 75.0f);
        // Strafe CCW 85 deg
        pRob->pMob->StrafeCCW(85.0f, 80.0f);
        // Drive Forward a bit
        pRob->pMob->DriveForward(5.0f, 80.0f);
        // Raise box
        pRob->pBag_servo->SetDegree(90);
        // Backup a bit
        pRob->pMob->DriveBackward(7.0f, 80.0f);
        // Lower Box
        pRob->pBag_servo->SetDegree(180);
        Sleep(500);
        // Push snow in
        pRob->pMob->DriveForward(7.0f, 80.0f);
        // Backup again
        pRob->pMob->DriveBackward(8.0f, 80.0f);

        return TASK_RESULT_SUCCESS;
    }

    TASK_RESULT PerfTest4(Robot * const pRob)
    {
        PerfTest4_1(pRob);
        PerfTest4_2(pRob);
    }

    TASK_RESULT PerfTest4_1(Robot * const pRob)
    {
        const float LIGHT_START_MAX = CONST.GetVal<float>("LIGHT_START_MAX", C_TYPE_FLOAT);

        // Initialize RPS
        RPS.InitializeMenu();

        // Wait for light
        while(GetCdSIntensity(pRob->pCds_cell) > LIGHT_START_MAX);

        // Calibrate
        pRob->pNav->CalibrateHeading(270.0f);
        pRob->pNav->CalibrateX(18.0f);
        pRob->pNav->CalibrateY(30.5f);

        // Drive off light
        pRob->pNav->DriveForwardTo({18.2f, 18.1f}, 85.0f);

        // Turn arms so that we don't hit the wall
        pRob->pCrank_servo->SetDegree(0.0f);

        // Drive backwards to be in front of ramp
        pRob->pNav->DriveBackwardTo({30.6f, 18.1f}, 80.0f);

        // Face Up ramp
        pRob->pNav->RotateTo(270.0f);

        // Turn the crank back to 90 degrees
        pRob->pCrank_servo->SetDegree(90.0f);

        // Drive up ramp 24 inches
        pRob->pMob->DriveBackward(24.0f, 85.0f);

        // Maunaully ask RPS where I am
        pRob->pNav->UpdatePosition();

        // Drive to crank sortof
        pRob->pNav->DriveBackwardTo({30.9f, 50.1f}, 80.0f);

        // Drive the rest of the way into the crank
        pRob->pMob->DriveBackward(7.5f, 80.0f);

        return TASK_RESULT_SUCCESS;
    }

    TASK_RESULT PerfTest4_2(Robot * const pRob)
    {
        LCD.WriteLine("Test 4.2");
        pRob->pCrank_servo->SetDegree(90.0f);
        Sleep(500);

        //Get light color
        LCD.WriteLine("Getting color");
        LIGHT light = ReadCdS(pRob->pCds_cell);
        while(light == LIGHT_NONE)
        {
            light = ReadCdS(pRob->pCds_cell);
        }

        LCD.WriteLine("Color found");
        // Counter clockwise
        if(light == LIGHT_RED)
        {
            LCD.WriteLine("Red!");
            // Rotate CW + 90 = 90
            pRob->pCrank_servo->SetDegree(180.0f);
            Sleep(500);

            // Back Out
            pRob->pMob->DriveForward(1.5f, 75.0f);

            // Set up for next turn
            pRob->pCrank_servo->SetDegree(40.0f);
            Sleep(500);

            // Drive in
            pRob->pMob->DriveBackward(1.5f, 75.0f);

            // Turn CW + 140 = 230
            pRob->pCrank_servo->SetDegree(180.0f);
            Sleep(500);

            // Back Out
            pRob->pMob->DriveForward(1.5f, 75.0f);

            // Set up for next turn
            pRob->pCrank_servo->SetDegree(40.0f);
            Sleep(500);

            // Drive in
            pRob->pMob->DriveBackward(1.5f, 75.0f);

            // Turn CW + 140 = 370
            pRob->pCrank_servo->SetDegree(180.0f);
            Sleep(500);
        }
        else if(light == LIGHT_BLUE)
        {
            LCD.WriteLine("Blue!");
            // Rotate CCW + 90 = 90
            pRob->pCrank_servo->SetDegree(0.0f);
            Sleep(500);

            // Back Out
            pRob->pMob->DriveForward(1.5f, 75.0f);

            // Set up for next turn
            pRob->pCrank_servo->SetDegree(140.0f);
            Sleep(500);

            // Drive in
            pRob->pMob->DriveBackward(1.5f, 75.0f);

            // Turn CCW + 140 = 230
            pRob->pCrank_servo->SetDegree(0.0f);
            Sleep(500);

            // Back Out
            pRob->pMob->DriveForward(1.5f, 75.0f);

            // Set up for next turn
            pRob->pCrank_servo->SetDegree(140.0f);
            Sleep(500);

            // Drive in
            pRob->pMob->DriveBackward(1.5f, 75.0f);

            // Turn CCW + 140 = 370
            pRob->pCrank_servo->SetDegree(0.0f);
            Sleep(500);
        }

        // Back out
        pRob->pMob->DriveForward(1.5f, 75.0f);

        pRob->pCrank_servo->Off();

        return TASK_RESULT_SUCCESS;
    }

    TASK_RESULT Dance(Robot * const pRob)
    {
        Sleep(300);

        pRob->pMob->DriveForward(14.0, 70);

        pRob->pMob->RotateCCW(360.0f, 80.0f);

        pRob->pMob->RotateCW(360.0f, 80.0f);

        pRob->pMob->DriveForward(3.0f, 70.0f);

        pRob->pMob->RotateCCW(360.0f, 100.0f);

        pRob->pMob->RotateCW(360.0f, 100.0f);

        pRob->pMob->DriveBackward(7.0f, 70.0f);

        pRob->pMob->StrafeCCW(180.0f);

        pRob->pMob->RotateCCW(720.0f, 80.0f);
    }

}
}
