#include "input_data.h"
#include "flow.h"
#include <math.h>
#include <float.h>

const std::string ERR_VALUE_G1 = "Error: wrong value for flow rate G1";
const std::string ERR_VALUE_G2 = "Error: wrong value for flow rate G2";
const std::string ERR_TEMP_1 = "Error: constant temperature for the flow #1";
const std::string ERR_TEMP_2 = "Error: constant temperature for the flow #2";
const std::string ERR_HEATING = "Error: both flows are being heated";
const std::string ERR_COOLING = "Error: both flows are being cooled";
const std::string ERR_WRONG_DIFF = "Error: too small temperature difference";
const std::string ERR_END_DIFF = "Error: wrong temperature differences at the end of a heat exchanger";
const std::string ERR_START_TEMP = "Error: wrong input temperatures";
const std::string ERR_FLOW_NOT_HEATING = "Error: flow must be heated";
const std::string ERR_FLOW_NOT_COOLING = "Error: flow must be cooled";
const double MIN_DIFF = 0.1;


bool InputData::CheckData() const
{
    msg = "";
    // Flow rates check
    if((flow_1.GetFlowRate()<=0)&&(flow_1.GetUnknownValue()!=UNKN_RATE))
        return SetMessage(ERR_VALUE_G1);

    if((flow_2.GetFlowRate()<=0)&&(flow_2.GetUnknownValue()!=UNKN_RATE))
        return SetMessage(ERR_VALUE_G2);

    // Flow temperatures
    if((fabs(flow_1.GetInletTemperature()-flow_1.GetOutletTemperature())<DBL_MIN)
       &&(!IsCondensingOrBoiling(flow_1)))
            return SetMessage(ERR_TEMP_1);

    if((fabs(flow_2.GetInletTemperature()-flow_2.GetOutletTemperature())<DBL_MIN)
       &&(!IsCondensingOrBoiling(flow_2)))
            return SetMessage(ERR_TEMP_2);

    if((!IsCondensingOrBoiling(flow_1))&&(!IsCondensingOrBoiling(flow_2))/*&&(IsFlowUnknown())*/)
    {
        if((IsFlowHeating(flow_1))&&(IsFlowHeating(flow_2)))
            return SetMessage(ERR_HEATING);

        if((!IsFlowHeating(flow_1))&&(!IsFlowHeating(flow_2)))
            return SetMessage(ERR_COOLING);

        if(direction==FLOW_SO_CURRENT)
        {
            double diff_1 = flow_1.GetInletTemperature() - flow_2.GetInletTemperature();
            double diff_2 = flow_1.GetOutletTemperature() - flow_2.GetOutletTemperature();
            if((fabs(diff_1)<MIN_DIFF)||(fabs(diff_2)<MIN_DIFF))
                return SetMessage(ERR_WRONG_DIFF);

            if((diff_1<0)&&(diff_2>0))
                return SetMessage(ERR_END_DIFF);

            if((diff_1>0)&&(diff_2<0))
                return SetMessage(ERR_END_DIFF);
        }

        if(direction==FLOW_COUNTER_CURRENT)
        {
            double diff_1 = flow_1.GetInletTemperature() - flow_2.GetOutletTemperature();
            double diff_2 = flow_1.GetOutletTemperature() - flow_2.GetInletTemperature();
            if((fabs(diff_1)<MIN_DIFF)||(fabs(diff_2)<MIN_DIFF))
                return SetMessage(ERR_WRONG_DIFF);

            if((diff_1<0)&&(diff_2>0))
                return SetMessage(ERR_END_DIFF);

            if((diff_1>0)&&(diff_2<0))
                return SetMessage(ERR_END_DIFF);
        }

        double heating_temp = IsFlowHeating(flow_1) ? flow_1.GetInletTemperature() : flow_2.GetInletTemperature();
        double cooling_temp = IsFlowHeating(flow_2) ? flow_1.GetInletTemperature() : flow_2.GetInletTemperature();
        if(cooling_temp<heating_temp)
            return SetMessage(ERR_START_TEMP);
    }

    if((IsCondensingOrBoiling(flow_1))^(IsCondensingOrBoiling(flow_2)))
    {
        Flow cb_flow = IsCondensingOrBoiling(flow_1) ? flow_1 : flow_2;
        Flow n_flow = IsCondensingOrBoiling(flow_1) ? flow_2 : flow_1;

        if(((cb_flow.GetSubstance().type==F_CONDENSING_VAPOUR)
           ||(cb_flow.GetSubstance().type==F_CONDENSING_VAPOUR_WATER))
           &&(!IsFlowHeating(n_flow)))
           return SetMessage(ERR_FLOW_NOT_HEATING);

        if(((cb_flow.GetSubstance().type==F_BOILING_LIQUID)
           &&(IsFlowHeating(n_flow))))
           return SetMessage(ERR_FLOW_NOT_COOLING);

        if(cb_flow.GetSubstance().type==F_BOILING_LIQUID)
        {
            if((n_flow.GetInletTemperature()<cb_flow.GetInletTemperature())
               ||(n_flow.GetOutletTemperature()<cb_flow.GetInletTemperature()))
            return SetMessage(ERR_END_DIFF);
        }

        if(((cb_flow.GetSubstance().type==F_CONDENSING_VAPOUR)
           ||(cb_flow.GetSubstance().type==F_CONDENSING_VAPOUR_WATER)))
        {
            if((n_flow.GetInletTemperature()>cb_flow.GetInletTemperature())
               ||(n_flow.GetOutletTemperature()>cb_flow.GetInletTemperature()))
            return SetMessage(ERR_END_DIFF);
        }

        if(direction==FLOW_SO_CURRENT)
        {
            double diff_1 = flow_1.GetInletTemperature() - flow_2.GetInletTemperature();
            double diff_2 = flow_1.GetOutletTemperature() - flow_2.GetOutletTemperature();
            if((fabs(diff_1)<MIN_DIFF)||(fabs(diff_2)<MIN_DIFF))
                return SetMessage(ERR_WRONG_DIFF);
        }

        if(direction==FLOW_COUNTER_CURRENT)
        {
            double diff_1 = flow_1.GetInletTemperature() - flow_2.GetOutletTemperature();
            double diff_2 = flow_1.GetOutletTemperature() - flow_2.GetInletTemperature();
            if((fabs(diff_1)<MIN_DIFF)||(fabs(diff_2)<MIN_DIFF))
                return SetMessage(ERR_WRONG_DIFF);
        }
    }

    return true;
}

bool InputData::IsFlowHeating(const Flow &flow) const
{
    return flow.GetInletTemperature() - flow.GetOutletTemperature() < 0;
}


bool InputData::IsCondensingOrBoiling(const Flow &flow) const
{
    return ((flow.GetSubstance().type==F_BOILING_LIQUID)
          ||(flow.GetSubstance().type==F_CONDENSING_VAPOUR)
          ||(flow.GetSubstance().type==F_CONDENSING_VAPOUR_WATER));
}

bool InputData::IsFlowUnknown() const
{
    return (flow_1.GetUnknownValue()==UNKN_RATE)||(flow_2.GetUnknownValue()==UNKN_RATE);
}

bool InputData::SetMessage(const std::string &message) const
{
    msg = message;
    return false;
}
