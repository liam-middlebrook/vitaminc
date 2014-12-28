#include "util.h"

double vc_maxval(int count, ...){
        va_list values;
        int i;
        double max;

        va_start(values, count);

        max = 0.0f;
        for(i = 0; i < count; ++i)
        {
                double val = va_arg(values, double);
                max = (max > val) ? max : val;
        }
 
        va_end(values);
        return max;
}
        
double vc_minval(int count, ...){
        va_list values;
        int i;
        double min;

        va_start(values, count);
        
        min = 0.0f;
        for(i = 0; i < count; ++i)
        {
                double val = va_arg(values, double);
                min = (min < val) ? min : val;
        }
 
        va_end(values);
        return min;
}
