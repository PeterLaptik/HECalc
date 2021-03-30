#include "heatexchanger_st.h"
#include "input_data.h"
#include <math.h>

const double PI = 3.14;


HeatExchangerShellTube::HeatExchangerShellTube()
{ }

HeatExchangerShellTube::~HeatExchangerShellTube()
{ }


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
}

 double HeatExchangerShellTube::GetReInner()
 {
     return Re_in;
 }

 double HeatExchangerShellTube::GetPrInner()
 {
     return Pr_in;
 }

