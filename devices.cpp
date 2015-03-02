#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>

#include "core.cpp"

#define MAX_VOLT 3.3f

/**
* Determines the number of degrees to rotate to reach a desired heading
* @param Current The current heading in degrees
* @param Desired The desired heading in degrees
*
* @requires 0.0f <= Current < 360.0f and 0.0f <= Desired < 360.0f
* @ensures CalcDegreesToRotate returns a value v: {-180.0f, 180.0f }
*/
static float CalcDegreesToRotate(float Current, float Desired)
{
   float Diff = Desired - Current;
   if(Diff > 180.0f)
      return Diff - 360.0f;
   else if(Diff < -180.0f)
      return Diff + 360.0f;

   return Diff;
}

///////////////////////////////////////////////////
// CdS Cell section
///////////////////////////////////////////////////

#define CDS_SAMPLES 3
/**
* Reads the avreage intensity from a CdS cell
* @param pPin   The AnalogInputPin to read from
* @requires     The CdS cell exists
* @ensures      GetCdSIntensity returns a floating point value [0.0f, 1.0f]
*/
static float GetCdSIntensity(AnalogInputPin * const pPin)
{
    float cVal = pPin->Value();  // Take first sample
    for(int i = 1; i < CDS_SAMPLES; i++) {
        cVal += pPin->Value();  // Add to weighted average
        Sleep(20);              // Wait at least 20 ms between samples
    }
    cVal /= CDS_SAMPLES;                        // Compute true average
    return G8::Clamp(cVal / MAX_VOLT, 0.0f, 1.0f);  // Return average intensity;
}

#define LIGHT_NONE 0
#define LIGHT_RED  1
#define LIGHT_BLUE 2

#define LIGHT_RED_MAX  0.300f
#define LIGHT_BLUE_MAX 0.650f

/**
* Reads from the CdS sensor for ⅕ second and returns what color it sees
* @param pPin   The AnalogInputPin to read from
* @requires     The CdS cell exists and has a yellow filter over it
* @ensures      ReadCdS returns an integer : {LIGHT_NONE, LIGHT_RED, LIGHT_BLUE }
*/
static int ReadCdS(AnalogInputPin * const pPin)
{
   float IntensityCdS = GetCdSIntensity(pPin);
   if(IntensityCdS < LIGHT_RED_MAX)
      return LIGHT_RED;
   else if(IntensityCdS < LIGHT_BLUE_MAX)
      return LIGHT_BLUE;

   return LIGHT_NONE;
}
