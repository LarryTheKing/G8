#ifndef CORE
#define CORE

namespace G8
{
    /**
     * @brief Clamp Returns a value within a range
     * @param val   The value to clamp
     * @param min   The minimum value
     * @param max   The maximum value
     * @return      Returns val >= min and <= max
     * @requires    val, min, max are all valid floating point values
     */
    inline float Clamp(float const val, float const min, float const max)
    {
        if(val < min)
            return min;
        else if(val > max)
            return max;

        return val;
    }

    inline float WrapAngle(float angle)
    {
        while(angle > 360.0f)
            angle -= 360.0f;

        while(angle < -360.0f)
            angle += 360.0f;

        return angle;
    }

    inline int WrapAngle(int angle)
    {
        while(angle > 360)
            angle -= 360;

        while(angle < -360)
            angle += 360;

        return angle;
    }
}
#endif
