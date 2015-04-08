#include "tasks.h"
#include "robot.h"
#include "devices.h"

namespace G8
{
namespace Tasks
{
    TASK_RESULT Main(Robot * const pRob)
    {
        DriveToSaltBag(pRob);
        CaptureSaltBag(pRob);
        DriveToCrank(pRob);
        TurnCrank(pRob);
        DriveToButtons(pRob);
        PressButtons(pRob);
        DriveToCubby(pRob);
        DepositSaltBag(pRob);
        DriveToToggle(pRob);
        PressToggle(pRob);

        return TASK_RESULT_SUCCESS;
    }

    TASK_RESULT DriveToSaltBag(Robot * const pRob)
    {
        // Wait for middle button
        while(pRob->pButtons->MiddlePressed());

        // Get starting intensity
        const float LIGHT_START_MAX = CONST.GetVal<float>("LIGHT_START_MAX", C_TYPE_FLOAT);

        // Initialize RPS
        RPS.InitializeMenu();

        LCD.WriteLine("Press Left To Begin");
        while(!pRob->pButtons->LeftPressed());
        LCD.WriteLine("Running");

        // Get start time out
        const unsigned TIME_OUT_START = CONST.GetVal<int>("TIME_OUT_START", C_TYPE_INT);

        unsigned int timeStart = TimeNowSec();
        // Wait for light or time out
        while(GetCdSIntensity(pRob->pCds_cell) > LIGHT_START_MAX){
            if(TimeNowSec() - timeStart > TIME_OUT_START)
                break;
        }

        // Calibrate RPS
        pRob->pNav->CalibrateHeading(270.0f);
        pRob->pNav->CalibrateX(18.0f);
        pRob->pNav->CalibrateY(30.0f); // Change to 30.5f!!!!!!!!!!

        // Maunaully ask RPS where I am
        pRob->pNav->UpdatePosition();

        // Turn arms so that we don't hit the wall
        pRob->pCrank_servo->SetDegree(0.0f);
        // Lower box
        pRob->pBag_servo->SetDegree(180);
        // Drive off light
        pRob->pMob->DriveForward(10.0f, 90.0f);

        // Raise box
        pRob->pBag_servo->SetDegree(45);

        // Just bcuz
        Sleep(100);
        pRob->pNav->UpdatePosition();

        // Drive to salt bag
        pRob->pNav->DriveForwardTo({27.3f, 11.5f}, 80.0f);

        // Just bcuz
        Sleep(100);

        /// Check for weird ghost offset
        int nTry = 0;
        while(pRob->pNav->UpdatePosition().y > 10.5f || pRob->pNav->GetPosition().x < 24.9f)
        {
            pRob->pMob->DriveBackward(10.0f, 80.0f);

            // Just bcuz
            Sleep(100);

            pRob->pNav->DriveForwardTo({27.3f, 10.3f}, 80.0f);

            nTry++;

            if(nTry > 3)
                break;
        }

        pRob->pNav->RotateTo(315.0f);

        return TASK_RESULT_SUCCESS;
    }

    TASK_RESULT CaptureSaltBag(Robot * const pRob)
    {
        // Lower box
        pRob->pBag_servo->SetDegree(180);
        Sleep(500);
        // Backup a bit
        pRob->pMob->DriveBackward(3.0f, 80.0f);

        return TASK_RESULT_SUCCESS;
    }

    TASK_RESULT DriveToCrank(Robot * const pRob)
    {
        // Turn arms so that we don't hit the wall
        pRob->pCrank_servo->SetDegree(0.0f);

        // Drive backwards to be in front of ramp
        pRob->pNav->DriveBackwardTo({30.9f, 18.1f}, 80.0f); // 30.9x

        // Face Up ramp
        pRob->pNav->RotateTo(270.0f);

        // Turn the crank back to 90 degrees
        pRob->pCrank_servo->SetDegree(90.0f);

        // Drive up ramp 24 inches
        pRob->pMob->DriveBackward(24.0f, 90.0f);

        // Maunaully ask RPS where I am
        pRob->pNav->UpdatePosition();

        // Drive to crank sort of
        pRob->pNav->DriveBackwardTo({31.5f, 50.1f}, 80.0f);

        // Drive the rest of the way into the crank
        pRob->pMob->DriveBackward(7.5f, 80.0f);

        return TASK_RESULT_SUCCESS;
    }

    TASK_RESULT TurnCrank(Robot * const pRob)
    {
        // Get start time out
        const unsigned TIME_OUT_CRANK = CONST.GetVal<int>("TIME_OUT_CRANK", C_TYPE_INT);

        //Get light color
        LCD.WriteLine("Getting color");

        // Try once, record what time it is now
        LIGHT light = ReadCdS(pRob->pCds_cell);
        unsigned int timeStart = TimeNowSec();
        while(light == LIGHT_NONE)
        {
            light = ReadCdS(pRob->pCds_cell);
            if(TimeNowSec() - timeStart > TIME_OUT_CRANK)
            {
                LCD.WriteLine("Time out!");
                light = LIGHT_RED;  // Assume red
                break;
            }
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
            pRob->pMob->DriveBackward(2.2f, 75.0f);

            // Turn CW + 140 = 230
            pRob->pCrank_servo->SetDegree(180.0f);
            Sleep(500);

            // Back Out
            pRob->pMob->DriveForward(1.5f, 75.0f);

            // Set up for next turn
            pRob->pCrank_servo->SetDegree(40.0f);
            Sleep(500);

            // Drive in
            pRob->pMob->DriveBackward(2.2f, 75.0f);

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
            pRob->pNav->RotateTo(270.0f);
            Sleep(300);

            // Drive in
            pRob->pMob->DriveBackward(2.2f, 75.0f);

            // Turn CCW + 140 = 230
            pRob->pCrank_servo->SetDegree(0.0f);
            Sleep(500);

            // Back Out
            pRob->pMob->DriveForward(1.5f, 75.0f);

            // Set up for next turn
            pRob->pCrank_servo->SetDegree(140.0f);
            pRob->pNav->RotateTo(270.0f);
            Sleep(300);

            // Drive in
            pRob->pMob->DriveBackward(2.2f, 75.0f);

            // Turn CCW + 140 = 370
            pRob->pCrank_servo->SetDegree(0.0f);
            Sleep(500);
        }

        // Back out
        pRob->pMob->DriveForward(3.5f, 75.0f);

        pRob->pCrank_servo->Off();

        return TASK_RESULT_SUCCESS;
    }

    TASK_RESULT DriveToButtons(Robot * const pRob)
    {
        // Drive around snow pile
        pRob->pNav->RotateTo(300.0f);

        pRob->pMob->DriveBackward(3.0f, 80.0f);

        pRob->pNav->DriveBackwardTo({17.2f, 59.7f}, 85.0f);

        pRob->pNav->DriveBackwardTo({15.0f, 62.3f}, 85.0f);

        return TASK_RESULT_SUCCESS;
    }

    enum BUTTON_COLOR
    {
        BUTTON_COLOR_RED    = 0x1,
        BUTTON_COLOR_WHITE  = 0x2,
        BUTTON_COLOR_BLUE   = 0x4
    };

    bool CheckHit(BUTTON_COLOR color)
    {
        if(color == BUTTON_COLOR_RED)
            return RPS.RedButtonPressed();
        else if(color = BUTTON_COLOR_BLUE)
            return RPS.BlueButtonPressed();
        else if(color = BUTTON_COLOR_WHITE)
            return RPS.WhiteButtonPressed();
        else
            return true;
    }

    void HitButton(BUTTON_COLOR color, Robot * const pRob)
    {
        const unsigned int SOL_MAX_TRY = CONST.GetVal<int>("SOL_MAX_TRY", C_TYPE_INT);
        const int SOL_FIRE_MS = CONST.GetVal<int>("SOL_FIRE_MS", C_TYPE_INT);
        const int SOL_WAIT_MS = CONST.GetVal<int>("SOL_WAIT_MS", C_TYPE_INT);

        FEHIO::FEHIOPin pin;
        if(color == BUTTON_COLOR_RED)
            pin = static_cast<FEHIO::FEHIOPin>(CONST.GetVal<int>("PIN_BUTTON_R"));
        else if(color == BUTTON_COLOR_WHITE)
            pin = static_cast<FEHIO::FEHIOPin>(CONST.GetVal<int>("PIN_BUTTON_W"));
        else
            pin = static_cast<FEHIO::FEHIOPin>(CONST.GetVal<int>("PIN_BUTTON_B"));

        DigitalOutputPin sol(pin);

        for(int i = 0; i < SOL_MAX_TRY; i++)
        {
            if(color != BUTTON_COLOR_BLUE)
            {
                sol.Write(true);
                Sleep(SOL_FIRE_MS);
                sol.Write(false);
            }
            else
            {
                pRob->pNav->RotateTo(345.0f);
                pRob->pNav->RotateTo(315.0f);
                pRob->pMob->DriveBackward(1.0f, 80.0f);
            }


            Sleep(100);
            if(CheckHit(color))
                break;

            if(color != BUTTON_COLOR_BLUE)
            {
                Sleep(SOL_WAIT_MS);
            }
        }

    }

    TASK_RESULT PressButtons(Robot * const pRob)
    {        
        pRob->pNav->RotateTo(315.0f);
        pRob->pMob->DriveBackward(1.0f, 80.0f);

        // JUST USE A BLOCK /////////////////
        for(int i = 0;
            i < 10 && (RPS.ButtonsPressed() != 3);
            i++)
        {
            pRob->pMob->DriveForward(1.5f, 80.0f);
            pRob->pMob->DriveBackward(2.2f, 80.0f);
        }

        pRob->pMob->DriveForward(3.0f, 80.0f);

        return TASK_RESULT_SUCCESS;

        ///////////////////

        BUTTON_COLOR order[3];
        order[RPS.RedButtonOrder() - 1] = BUTTON_COLOR_RED;
        order[RPS.WhiteButtonOrder() - 1] = BUTTON_COLOR_WHITE;
        order[RPS.BlueButtonOrder() - 1] = BUTTON_COLOR_BLUE;

        for(int i = 0; i < 3; i++)
        {
            HitButton(order[i], pRob);
        }

        pRob->pMob->DriveForward(3.0f, 80.0f);

        return TASK_RESULT_SUCCESS;
    }

    TASK_RESULT DriveToCubby(Robot * const pRob)
    {
        Sleep(100);
        // Drive by cubby
        pRob->pNav->DriveBackwardTo({12.7f, 58.3}, 85.0f);
        pRob->pNav->DriveBackwardTo({4.8f, 52.0f}, 85.0f);
        // Orient to 75 deg
        pRob->pNav->RotateTo(75.0f);
        // Scoot a bit
        pRob->pMob->DriveForward(1.2f, 80.0f);
        // Strafe CCW 40 deg
        pRob->pMob->StrafeCCW(40.0f, 80.0f);
        // Ensure we are facing the right way
        pRob->pNav->RotateTo(135.0f);
        // Drive Forward a bit
        pRob->pMob->DriveForward(5.0f, 80.0f);

        return TASK_RESULT_SUCCESS;
    }

    TASK_RESULT DepositSaltBag(Robot * const pRob)
    {
        // Raise box
        pRob->pBag_servo->SetDegree(60);
        // Backup a bit
        pRob->pMob->DriveBackward(7.0f, 80.0f);
        // Lower Box
        pRob->pBag_servo->SetDegree(180);
        Sleep(500);
        // Push bag in
        pRob->pMob->DriveForward(7.0f, 80.0f);
        // Backup again
        pRob->pMob->DriveBackward(4.5f, 80.0f);


        return TASK_RESULT_SUCCESS;
    }

    TASK_RESULT DriveToToggle(Robot * const pRob)
    {
        // Drive to top of ramp
        pRob->pNav->DriveBackwardTo({6.4f, 46.0f}, 80.0f);
        pRob->pNav->DriveBackwardTo({4.0f, 41.4f}, 80.0f);

        // Turn arms so that we don't hit the wall
        pRob->pCrank_servo->SetDegree(0.0f);
        // Raise box
        pRob->pBag_servo->SetDegree(10);

        // Drive to bottom of ramp
        pRob->pNav->RotateTo(90.0f);
        pRob->pNav->DriveBackwardTo({pRob->pNav->GetPosition().x, 22.7f}, 80.0f);

        // Raise box
        pRob->pBag_servo->SetDegree(10.0f); // From 0.0f

        // Determine which direction
        if(RPS.OilDirec() == 0) // RIGHT?
        {
            // Drive to other side of switch
            pRob->pNav->RotateTo(0.0f);
            pRob->pNav->DriveForwardTo({14.2f, 16.1f}, 80.0f);
            pRob->pNav->DriveForwardTo({21.1f, 4.5f}, 80.0f);


            // Orient West
            pRob->pNav->RotateTo(180.0f);
        }
        else
        {
            Sleep(110);
            // Drive to the right side
            pRob->pNav->DriveForwardTo({8.5f, 18.4f}, 80.0f);

            // Orient south
            pRob->pNav->RotateTo(250.0f);
        }

        return TASK_RESULT_SUCCESS;
    }

    TASK_RESULT PressToggle(Robot * const pRob)
    {
        while(!RPS.OilPress())
        {

            if(RPS.OilDirec() == 0){
                pRob->pNav->DriveForwardTo({14.6f, 4.5f}, 80.0f);
                pRob->pMob->RotateCW(100.0f);

                // Orient West
                pRob->pNav->RotateTo(180.0f);
                pRob->pMob->DriveBackward(4.0f, 80.0f);
            }
            else
            {
                pRob->pMob->DriveForward(6.0f, 90.0f);
                pRob->pMob->StrafeCW(10.0f);
                // Orient West
                pRob->pNav->RotateTo(250.0f);
            }
            pRob->pMob->DriveBackward(4.0f, 80.0f);
        }

        pRob->pBag_servo->Off();
        pRob->pCrank_servo->Off();

        // Woooh!!!!! All done
        return TASK_RESULT_SUCCESS;
    }

}
}
