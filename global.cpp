#include "global.h"
#include "tasks.h"
#include "diagnostic.h"

namespace G8
{
    CONSTANT_SYS CONST;

    TaskSystem   TASK("Main task menu");

    void DefineConstants(void)
    {
        // Robot constants
        CONST.Add<int>  ("BANK_BB",     3, C_TYPE_INT | C_TYPE_UNSIGNED); // Button Board FEHIO::Bank3
        CONST.Add<int>  ("PIN_RENCODE", 0, C_TYPE_INT | C_TYPE_UNSIGNED); // Right Encoder FEHIO::P0_0
        CONST.Add<int>  ("PIN_LENCODE", 2, C_TYPE_INT | C_TYPE_UNSIGNED); // Left Encoder FEHIO::P0_2
        CONST.Add<int>  ("MOT_RIGHT",   0, C_TYPE_INT | C_TYPE_UNSIGNED); // Right Motor FEHMotor::Motor0
        CONST.Add<int>  ("MOT_LEFT",    1, C_TYPE_INT | C_TYPE_UNSIGNED); // Left Motor FEHMotor::Motor1
        CONST.Add<int>  ("PIN_CDS",     8, C_TYPE_INT | C_TYPE_UNSIGNED); // CdS Cell FEHIO::P1_0
        CONST.Add<int>  ("SERVO_BAG_PORT", 0, C_TYPE_INT | C_TYPE_UNSIGNED);
        CONST.Add<int>  ("SERVO_CRANK_PORT", 1, C_TYPE_INT | C_TYPE_UNSIGNED);

        // Devices constants
        CONST.Add<int>  ("CDS_SAMPLES", 3, C_TYPE_INT | C_TYPE_UNSIGNED);
        CONST.Add<float>("MAX_VOLT",    3.3f, C_TYPE_FLOAT);
        CONST.Add<int>  ("SERVO_BAG_MAX", 2352, C_TYPE_INT);
        CONST.Add<int>  ("SERVO_BAG_MIN", 500, C_TYPE_INT);
        CONST.Add<int>  ("SERVO_CRANK_MAX", 2500, C_TYPE_INT);
        CONST.Add<int>  ("SERVO_CRANK_MIN", 500, C_TYPE_INT);

        CONST.Add<float>("LIGHT_RED_MAX",   0.130f, C_TYPE_FLOAT);
        CONST.Add<float>("LIGHT_BLUE_MAX",  0.400f, C_TYPE_FLOAT);
        CONST.Add<float>("LIGHT_START_MAX", 0.610f, C_TYPE_FLOAT);

        // Mobility constants
        CONST.Add<float>("TICK_INCH",   2.778f, C_TYPE_FLOAT);
        CONST.Add<float>("TICK_DEG",    84.5f / 360.0f, C_TYPE_FLOAT);
        CONST.Add<float>("MOD_LEFT",    59.0f / 60.0f, C_TYPE_FLOAT);
        CONST.Add<float>("MOD_RIGHT",   1.0f, C_TYPE_FLOAT);

        CONST.Add<float>("COR_POWER",   65.0f, C_TYPE_FLOAT);
        CONST.Add<float>("ROT_POWER",   80.0f, C_TYPE_FLOAT);
        CONST.Add<int>  ("COR_TIME_MS", 100, C_TYPE_INT | C_TYPE_UNSIGNED);

        // Navigation constants
        CONST.Add<int>  ("RPS_SAMPLES", 2, C_TYPE_INT | C_TYPE_UNSIGNED);
        CONST.Add<int>  ("MAX_MOV_COR", 6, C_TYPE_INT | C_TYPE_UNSIGNED);// The max number tries to correct rotation
        CONST.Add<int>  ("MAX_ROT_COR", 30, C_TYPE_INT | C_TYPE_UNSIGNED);// The max number tries to correct movement
        CONST.Add<float>("MOV_TOL",     0.5f, C_TYPE_FLOAT);    // Movement tolerance
        CONST.Add<float>("ROT_TOL",     1.2f, C_TYPE_FLOAT);    // Rotation tolerance

        // Task constants
        CONST.Add<int>  ("TIME_OUT_START", 30, C_TYPE_INT | C_TYPE_UNSIGNED); // Time to start after not seeing start light
        CONST.Add<int>  ("TIME_OUT_CRANK", 5, C_TYPE_INT | C_TYPE_UNSIGNED); // Time to wait for crank light

        CONST.Add<int>  ("PIN_BUTTON_R",    16, C_TYPE_INT | C_TYPE_UNSIGNED); // Solenoid for red button FEHIO::P2_0
        CONST.Add<int>  ("PIN_BUTTON_W",    17, C_TYPE_INT | C_TYPE_UNSIGNED); // Solenoid for white button FEHIO::P2_1
        CONST.Add<int>  ("PIN_BUTTON_B",    18, C_TYPE_INT | C_TYPE_UNSIGNED); // Solenoid for blue button FEHIO::P2_2

        CONST.Add<int>  ("SOL_MAX_TRY",     4,   C_TYPE_INT | C_TYPE_UNSIGNED); // How many times to try and hit a solenoid
        CONST.Add<int>  ("SOL_FIRE_MS",     200, C_TYPE_INT | C_TYPE_UNSIGNED); // How long to power on a solenoid
        CONST.Add<int>  ("SOL_WAIT_MS",     500, C_TYPE_INT | C_TYPE_UNSIGNED); // How long to wait before refiring

    }

    void DisablePins(void)
    {
        DigitalOutputPin solR(static_cast<FEHIO::FEHIOPin>(CONST.GetVal<int>("PIN_BUTTON_R")));
        DigitalOutputPin solW(static_cast<FEHIO::FEHIOPin>(CONST.GetVal<int>("PIN_BUTTON_W")));
        DigitalOutputPin solB(static_cast<FEHIO::FEHIOPin>(CONST.GetVal<int>("PIN_BUTTON_B")));
        solR.Write(false);
        solW.Write(false);
        solB.Write(false);
    }

    void DefineTasks(void)
    {
        DisablePins();
        TASK.AddTask("Main",            Tasks::Main);
        TASK.AddTask("Diagnostics",     Tasks::Diagnostics);

        TASK.AddTask("Drive to Salt Bag",   Tasks::DriveToSaltBag);
        TASK.AddTask("Capture Salt Bag",    Tasks::CaptureSaltBag);
        TASK.AddTask("Drive to Crank",      Tasks::DriveToCrank);
        TASK.AddTask("Turn Crank",          Tasks::TurnCrank);
        TASK.AddTask("Drive To Buttons",    Tasks::DriveToButtons);
        TASK.AddTask("Drive To Cubby",      Tasks::DriveToCubby);
        TASK.AddTask("Deposit Salt Bag",    Tasks::DepositSaltBag);
        TASK.AddTask("Drive To Toggle",     Tasks::DriveToToggle);
        TASK.AddTask("Press Toggle",        Tasks::PressToggle);
    }
}
