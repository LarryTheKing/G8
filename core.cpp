#include "core.h"

namespace G8
{
    float Clamp(float const val, float const min, float const max)
    {
        if(val < min)
            return min;
        else if(val > max)
            return max;

        return val;
    }

    float WrapAngle(float angle)
    {
        while(angle > 360.0f)
            angle -= 360.0f;

        while(angle < -360.0f)
            angle += 360.0f;

        return angle;
    }

    int WrapAngleI(int angle)
    {
        while(angle > 360)
            angle -= 360;

        while(angle < -360)
            angle += 360;

        return angle;
    }

    float CalcDegreesToRotate(float current, float desired)
    {
       float Diff = desired - current;
       if(Diff > 180.0f)
          return Diff - 360.0f;
       else if(Diff < -180.0f)
          return Diff + 360.0f;

       return Diff;
    }
}

