#include "global.h"

namespace G8
{
    CONSTANT_SYS CONST;

    void DefineConstants(void)
    {
        // Devices constants
        CONST.Add<int>  ("CDS_SAMPLES", 3, C_TYPE_INT);
        CONST.Add<float>("MAX_VOLT",    3.3f, C_TYPE_FLOAT);

        CONST.Add<float>("LIGHT_RED_MAX",   0.300f, C_TYPE_FLOAT);
        CONST.Add<float>("LIGHT_BLUE_MAX",  0.650f, C_TYPE_FLOAT);

        // Mobility constants
        CONST.Add<float>("TICK_INCH",   2.778f, C_TYPE_FLOAT);
        CONST.Add<float>("TICK_DEG",    85.5f / 360.0f, C_TYPE_FLOAT);
        CONST.Add<float>("MOD_LEFT",    59.0f / 60.0f, C_TYPE_FLOAT);
        CONST.Add<float>("MOD_RIGHT",   1.0f, C_TYPE_FLOAT);

        CONST.Add<int>  ("COR_POWER",   55, C_TYPE_INT);
        CONST.Add<int>  ("ROT_POWER",   60, C_TYPE_INT);

        // Navigation constants
        CONST.Add<int>  ("MAX_COR", 4, C_TYPE_INT);         // The max number tries to correct
        CONST.Add<float>("MOV_TOL", 0.5f, C_TYPE_FLOAT);    // Movement tolerance
        CONST.Add<float>("ROT_TOL", 1.0f, C_TYPE_FLOAT);    // Rotation tolerance
    }
}
