#ifndef CORE_H
#define CORE_H

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
    float   Clamp(float const val, float const min, float const max);

    float   WrapAngle(float angle);
    int     WrapAngleI(int angle);

    /**
    * Determines the number of degrees to rotate to reach a desired heading
    * @param current The current heading in degrees
    * @param desired The desired heading in degrees
    *
    * @requires 0.0f <= current < 360.0f and 0.0f <= desired < 360.0f
    * @ensures CalcDegreesToRotate returns a value v: {-180.0f, 180.0f }
    */
    float   CalcDegreesToRotate(float current, float desired);

}

#endif // CORE_H
