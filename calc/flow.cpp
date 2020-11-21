#include "flow.h"

Flow::Flow()
{
    unknown_value = UNKN_NONE;
}

Flow::~Flow()
{ }

void Flow::SetSubstance(Substance s)
{
    substance = s;
}

void Flow::SetFlowRate(double G)
{
    flow_rate = G;
}

void Flow::SetInletTemperature(double Tin)
{
    inlet_temperature = Tin;
}

void Flow::SetOutletTemperature(double Tout)
{
    outlet_temperature = Tout;
}

void Flow::SetUnknownValue(FlowUnknownValue val)
{
    unknown_value = val;
}

Substance& Flow::GetSubstance()
{
    return substance;
}

double Flow::GetFlowRate() const
{
    return flow_rate;

}
double Flow::GetInletTemperature() const
{
    return inlet_temperature;
}

double Flow::GetOutletTemperature() const
{
    return outlet_temperature;
}

FlowUnknownValue Flow::GetUnknownValue() const
{
    return unknown_value;
}
