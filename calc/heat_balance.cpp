#include "heat_balance.h"
#include "input_data.h"

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
    double Q = flow_1->GetUnknownValue()==UNKN_NONE ? flow_1->CalculateHeatFlow() : flow_2->CalculateHeatFlow();

    // Calculate unknown value
    if(flow_1->GetUnknownValue()!=UNKN_NONE)
        flow_1->CalculateUnknown();
    else
        flow_2->CalculateUnknown();
}
