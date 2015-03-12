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

        // Devices constants
        CONST.Add<int>  ("CDS_SAMPLES", 3, C_TYPE_INT | C_TYPE_UNSIGNED);
        CONST.Add<float>("MAX_VOLT",    3.3f, C_TYPE_FLOAT);
        CONST.Add<int>  ("SERVO_BAG_MAX", 2352, C_TYPE_INT);
        CONST.Add<int>  ("SERVO_BAG_MIN", 500, C_TYPE_INT);

        CONST.Add<float>("LIGHT_RED_MAX",   0.300f, C_TYPE_FLOAT);
        CONST.Add<float>("LIGHT_BLUE_MAX",  0.650f, C_TYPE_FLOAT);

        // Mobility constants
        CONST.Add<float>("TICK_INCH",   2.778f, C_TYPE_FLOAT);
        CONST.Add<float>("TICK_DEG",    84.5f / 360.0f, C_TYPE_FLOAT);
        CONST.Add<float>("MOD_LEFT",    59.0f / 60.0f, C_TYPE_FLOAT);
        CONST.Add<float>("MOD_RIGHT",   1.0f, C_TYPE_FLOAT);

        CONST.Add<float>("COR_POWER",   65.0f, C_TYPE_FLOAT);
        CONST.Add<float>("ROT_POWER",   80.0f, C_TYPE_FLOAT);

        // Navigation constantsm
        CONST.Add<int>  ("RPS_SAMPLES", 2, C_TYPE_INT | C_TYPE_UNSIGNED);
        CONST.Add<int>  ("MAX_COR",     6, C_TYPE_INT | C_TYPE_UNSIGNED); // The max number tries to correct
        CONST.Add<float>("MOV_TOL",     0.5f, C_TYPE_FLOAT);    // Movement tolerance
        CONST.Add<float>("ROT_TOL",     1.5f, C_TYPE_FLOAT);    // Rotation tolerance
    }

    void DefineTasks(void)
    {
        TASK.AddTask("Main",            Tasks::Main);
        TASK.AddTask("Diagnostics",     Tasks::Diagnostics);
        TASK.AddTask("Perf Test 1",     Tasks::PerfTest1);
        TASK.AddTask("Perf Test 3",     Tasks::PerfTest3);
    }
}
