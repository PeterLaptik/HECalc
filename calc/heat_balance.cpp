#include "heat_balance.h"
#include "input_data.h"
#include <math.h>

HeatBalance::HeatBalance()
            : K(1.0)
{ }

HeatBalance::~HeatBalance()
{ }

HeatBalance& HeatBalance::GetInstance()
{
    static HeatBalance instance;
    return instance;
}


void HeatBalance::Calculate()
{
    InputData &data = InputData::GetInstance();
    Flow *flow_1 = &data.flow_1;
    Flow *flow_2 = &data.flow_2;

    // Define hot and cold flows
    double t_flow_1_max = flow_1->GetInletTemperature() > flow_1->GetOutletTemperature() ?
                        flow_1->GetInletTemperature() : flow_1->GetInletTemperature();

    double t_flow_2_max = flow_2->GetInletTemperature() > flow_2->GetOutletTemperature() ?
                        flow_2->GetInletTemperature() : flow_2->GetInletTemperature();

    if(t_flow_1_max>t_flow_2_max)
    {
        flow_1->SetIsHotFlow(true);
        flow_2->SetIsHotFlow(false);
    }
    else
    {
        flow_1->SetIsHotFlow(false);
        flow_2->SetIsHotFlow(true);
    }

    // Heat flow
    heat_flow = flow_1->GetUnknownValue()==UNKN_NONE ? flow_1->CalculateHeatFlow() : flow_2->CalculateHeatFlow();
    // Set heat flow for a flow with unknown values
    if(flow_1->GetUnknownValue()==UNKN_NONE)
        flow_2->SetHeatFlow(heat_flow);
    else
        flow_1->SetHeatFlow(heat_flow);

    // Calculate unknown value
    if(flow_1->GetUnknownValue()!=UNKN_NONE)
        flow_1->CalculateUnknown();
    else
        flow_2->CalculateUnknown();

    // Logarithmic temperature difference
    CalculateMeanTemperatureDifference();
}

void HeatBalance::CalculateMeanTemperatureDifference()
{
    InputData &data = InputData::GetInstance();
    Flow &flow_1 = data.flow_1;
    Flow &flow_2 = data.flow_2;
    // Heat exchanger left side
    double T_left_1 = flow_1.GetInletTemperature();
    double T_left_2 = data.direction==FLOW_COUNTER_CURRENT ? flow_2.GetOutletTemperature() : flow_2.GetInletTemperature();
    // Heat exchanger right side
    double T_right_1 = flow_1.GetOutletTemperature();
    double T_right_2 = data.direction==FLOW_COUNTER_CURRENT ? flow_2.GetInletTemperature() : flow_2.GetOutletTemperature();
    // Max and Min differences
    double dt_left = fabs(T_left_1-T_left_2);
    double dt_right = fabs(T_right_1-T_right_2);
    double dt_max = dt_left > dt_right ? dt_left : dt_right;
    double dt_min = dt_left > dt_right ? dt_right : dt_left;
    // Result temperature difference
    dT = (dt_max - dt_min)/log(dt_max/dt_min);
    dT = round(dT*10)/10;
}


void HeatBalance::SetPrelimHeatTransferCoefficient(double coeff)
{
    K = coeff;
}
