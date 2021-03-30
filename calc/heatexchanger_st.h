#ifndef HEATEXCHANGER_ST_H_INCLUDED
#define HEATEXCHANGER_ST_H_INCLUDED

#include "heatexchanger.h"

class InputData;

class HeatExchangerShellTube: public HeatExchanger
{
    public:
        HeatExchangerShellTube();
        ~HeatExchangerShellTube();
        // Pipes
        double pipe_outer_diameter;   // m
        double pipe_thickness;  // m
        int pipe_number;
        int passes_number;
        // Shell
        double shell_inner_diameter;

        double GetReInner(void);
        double GetPrInner(void);

        virtual void Calculate(void);

    private:
        double Re_in;
        double Pr_in;
};

#endif // HEATEXCHANGER_ST_H_INCLUDED
