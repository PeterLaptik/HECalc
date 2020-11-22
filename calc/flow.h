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

        double CalculateHeatFlow(void);
        void CalculateUnknown(void);

        void SetSubstance(Substance s);
        void SetFlowRate(double G);
        void SetInletTemperature(double t);
        void SetOutletTemperature(double t);
        void SetUnknownValue(FlowUnknownValue val);
        void SetHeatFlow(double heat);
        void SetIsHotFlow(bool is_hot_flow);

        Substance& GetSubstance(void);
        double GetFlowRate(void) const;
        double GetInletTemperature(void) const;
        double GetOutletTemperature(void) const;
        FlowUnknownValue GetUnknownValue(void) const;
        double GetIsHotFlow(void) const;

    protected:

    private:
        bool is_hot;
        Substance substance;
        double flow_rate;
        double inlet_temperature;
        double outlet_temperature;
        FlowUnknownValue unknown_value;
        double heat_flow;
};

#endif // FLOW_H_INCLUDED
