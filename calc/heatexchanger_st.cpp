#include "heatexchanger_st.h"
#include "input_data.h"
#include <math.h>
#include "strategy/heat_calc_str.h"

const double PI = 3.14;


HeatExchangerShellTube::HeatExchangerShellTube()
{
    HeatCalc::AssignStrategies(calc_strategies, this);
    calc_strategy = new HeatCalcStDytn();
}

HeatExchangerShellTube::~HeatExchangerShellTube()
{
    for(std::map<std::string,HeatCalc*>::iterator it=calc_strategies.begin(); it!=calc_strategies.end(); ++it)
        delete (*it).second;
}

const std::map<std::string,HeatCalc*>& HeatExchangerShellTube::GetStrategies()
{
    return calc_strategies;
}

void HeatExchangerShellTube::AssignStrategy(const std::string &name)
{
    HeatCalc *str = calc_strategies.find(name)!=calc_strategies.end() ? (*calc_strategies.find(name)).second : nullptr;
    if(str)
        calc_strategy = str;
}

void HeatExchangerShellTube::Calculate()
{
    InputData &data = InputData::GetInstance();
    double G1 = data.flow_1.GetFlowRate();
    double mu = data.flow_1.GetSubstance().viscosity;
    double rho = data.flow_1.GetSubstance().density;

    // Pipe area
    double d = pipe_outer_diameter - 2*pipe_thickness;
    double S = PI*(d*d)/4/passes_number;
    double Sall = S*pipe_number;

    // Average fluid velocity
    double voluminate_flow = G1/rho;
    double v = voluminate_flow/Sall;

    // Reynold's coefficient
    Re_in = round((v*d*rho)/mu);

    // Prandtle coefficient
    double c = data.flow_1.GetSubstance().heat_capacity;
    double lambda = data.flow_1.GetSubstance().thermal_conductivity;
    Pr_in = round(c*mu/lambda*100)/100;

    if(!calc_strategy)
        return;

    calc_strategy->AssignHeatExchanger(this);
    calc_strategy->Calculate();

}

double HeatExchangerShellTube::GetNuInner() const
{
    if(!calc_strategy)
        return -1;

    return calc_strategy->GetNuInner();
}

double HeatExchangerShellTube::GetReInner() const
{
    return Re_in;
}

double HeatExchangerShellTube::GetPrInner() const
{
    return Pr_in;
}

double HeatExchangerShellTube::GetAlphaInner(void) const
{
    if(!calc_strategy)
        return -1;

    return calc_strategy->GetAlphaInner();
}
