#include "devices.h"

namespace G8
{
    float GetCdSIntensity(AnalogInputPin * const pPin)
    {
        int CDS_SAMPLES = CONST.GetVal<int>("CDS_SAMPLES", C_TYPE_INT);
        float cVal = pPin->Value();  // Take first sample
        for(int i = 1; i < CDS_SAMPLES; i++) {
            cVal += pPin->Value();  // Add to weighted average
            Sleep(20);              // Wait at least 20 ms between samples
        }
        if(CDS_SAMPLES)
            cVal /= CDS_SAMPLES;                        // Compute true average
        // Return average intensity;
        return Clamp(cVal / CONST.GetVal<float>("MAX_VOLT", C_TYPE_FLOAT), 0.0f, 1.0f);
    }

    LIGHT ReadCdS(AnalogInputPin * const pPin)
    {
       float IntensityCdS = GetCdSIntensity(pPin);
       if(IntensityCdS < CONST.GetVal<float>("LIGHT_RED_MAX", C_TYPE_FLOAT))
          return LIGHT_RED;
       else if(IntensityCdS < CONST.GetVal<float>("LIGHT_BLUE_MAX", C_TYPE_FLOAT))
          return LIGHT_BLUE;

       return LIGHT_NONE;
    }
}
