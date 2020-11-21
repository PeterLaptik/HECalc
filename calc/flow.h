#ifndef FLOW_H_INCLUDED
#define FLOW_H_INCLUDED

#include "substance.h"

enum FlowUnknownValue
{
    UNKN_NONE, UNKN_T_IN, UNKN_T_OUT, UNKN_RATE
};

class Flow
{
    public:
        Flow();
        ~Flow();
        void SetSubstance(Substance s);
        void SetFlowRate(double G);
        void SetInletTemperature(double t);
        void SetOutletTemperature(double t);
        void SetUnknownValue(FlowUnknownValue val);

        Substance& GetSubstance(void);
        double GetFlowRate(void) const;
        double GetInletTemperature(void) const;
        double GetOutletTemperature(void) const;
        FlowUnknownValue GetUnknownValue(void) const;

    protected:

    private:
        Substance substance;
        double flow_rate;
        double inlet_temperature;
        double outlet_temperature;
        FlowUnknownValue unknown_value;

};

#endif // FLOW_H_INCLUDED
