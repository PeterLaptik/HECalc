#include "flow.h"
#include <math.h>


Flow::Flow()
{
    unknown_value = UNKN_NONE;
    is_hot = true;
}

Flow::~Flow()
{ }


double Flow::CalculateHeatFlow()
{
    if(unknown_value!=UNKN_NONE)
        return heat_flow = 0;

    FluidType fluid_type = substance.type;
    switch(fluid_type)
    {
        case F_GAS:
        case F_LIQUID:
        case F_WATER:
            heat_flow = flow_rate*substance.heat_capacity*fabs(inlet_temperature - outlet_temperature);
            break;
        case F_BOILING_LIQUID:
            heat_flow = substance.heat_vaporization*flow_rate;
            break;
        case F_CONDENSING_VAPOUR:
        case F_CONDENSING_VAPOUR_WATER:
            heat_flow = substance.heat_condensation*flow_rate;
            break;
    }
    heat_flow = round(heat_flow*10)/10;
    return heat_flow;
}

void Flow::CalculateUnknown()
{
    // For liquids and gases
    // Q = G*c*dT
    if((substance.type==F_GAS)||(substance.type==F_LIQUID)||(substance.type==F_WATER))
    {
        // G = Q/(c*dT)
        if(unknown_value==UNKN_RATE)
        {
            flow_rate = heat_flow/(substance.heat_capacity*fabs(inlet_temperature - outlet_temperature));
        }
        // dT = Q/(G*c)
        // Tin - Tout = Q/(G*c)
        if(unknown_value==UNKN_T_IN)
        {
            double delta_t = heat_flow/(flow_rate*substance.heat_capacity);
            if(is_hot)
                inlet_temperature = delta_t + outlet_temperature;
            else
                inlet_temperature = outlet_temperature - delta_t;
        }
        // dT = Q/(G*c)
        // Tin - Tout = Q/(G*c)
        if(unknown_value==UNKN_T_OUT)
        {
            double delta_t = heat_flow/(flow_rate*substance.heat_capacity);
            if(is_hot)
                outlet_temperature = inlet_temperature - delta_t;
            else
                outlet_temperature = delta_t + inlet_temperature;
        }
    }

    if(substance.type==F_BOILING_LIQUID)
    {
        // G = Q/r
        if(unknown_value==UNKN_RATE)
        {
            flow_rate = heat_flow/(substance.heat_vaporization);
        }
    }

    if((substance.type==F_CONDENSING_VAPOUR)||(substance.type==F_CONDENSING_VAPOUR_WATER))
    {
        // G = Q/r
        if(unknown_value==UNKN_RATE)
        {
            flow_rate = heat_flow/(substance.heat_vaporization);
        }
    }
}

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

void Flow::SetHeatFlow(double heat)
{
    heat_flow = heat;
}

void Flow::SetIsHotFlow(bool is_hot_flow)
{
    is_hot = is_hot_flow;
}

Substance& Flow::GetSubstance()
{
    return substance;
}

const Substance& Flow::GetSubstance() const
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

double Flow::GetIsHotFlow() const
{
    return heat_flow;
}
