#include "heat_calc_str.h"
#include "../input_data.h"
#include "../heatexchanger_st.h"
#include <math.h>

void HeatCalc::AssignStrategies(std::map<std::string,HeatCalc*> &strategies, HeatExchanger *he)
{
    if(dynamic_cast<HeatExchangerShellTube*>(he))
    {
        HeatCalc *s = new HeatCalcStDytn();
        strategies.insert(std::pair<std::string,HeatCalc*>(s->GetName(), s));
        s = new HeatCalcTest();
        strategies.insert(std::pair<std::string,HeatCalc*>(s->GetName(), s));
    }
}

// Exception is being thrown if an equipment type and strategy do not match to each other
class BadEquipmentTypeException: public std::exception
{
    public:
        virtual const char* what(void)
        {
            return "Bad heat exchanger type on calculation!";
        }
};

/*********************** Shell-tube heat exchanger ***********************/
/****************************************************** Dytnersky ********/
/*************************************************************************/
void HeatCalcStDytn::Calculate()
{
    InputData &data = InputData::GetInstance();
    double Re_in = he->GetReInner();
    double Pr_in = he->GetPrInner();

    // Nu
    Nu = 0.023*pow(Re_in,0.8)*pow(Pr_in,0.4);
    Nu = round(Nu*10)/10;

    HeatExchangerShellTube *equip = dynamic_cast<HeatExchangerShellTube*>(he);
    if(!equip)
        throw BadEquipmentTypeException();

    alpha_in = Nu*(data.flow_1.GetSubstance().thermal_conductivity/(equip->pipe_outer_diameter - 2*equip->pipe_thickness));
    alpha_in = round(alpha_in*10)/10;
}

double HeatCalcStDytn::GetNuInner() const
{
    return Nu;
}

double HeatCalcStDytn::GetAlphaInner(void) const
{
    return alpha_in;
}

/*********************** Shell-tube heat exchanger ***********************/
/****************************************************** TEST *************/
/*************************************************************************/
void HeatCalcTest::Calculate()
{
    Nu = 1;
    alpha_in = 2;
}

double HeatCalcTest::GetNuInner() const
{
    return Nu;
}

double HeatCalcTest::GetAlphaInner(void) const
{
    return alpha_in;
}
