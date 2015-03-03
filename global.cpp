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
    }
}
