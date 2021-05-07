#ifndef HEATEXCHANGER_ST_H_INCLUDED
#define HEATEXCHANGER_ST_H_INCLUDED

#include "heatexchanger.h"
#include "heat_calc.h"
#include <map>

class InputData;

class HeatExchangerShellTube: public HeatExchanger
{
    public:
        HeatExchangerShellTube();
        ~HeatExchangerShellTube();
        // Pipes
        double pipe_outer_diameter; // m
        double pipe_thickness;      // m
        double pipe_length;         // m
        int pipe_number;
        int passes_number;
        // Shell
        double shell_inner_diameter;// m

        double GetReInner(void) const;
        double GetPrInner(void) const;
        double GetNuInner(void) const;
        double GetAlphaInner(void) const;

        virtual void Calculate(void);
        virtual const std::map<std::string,HeatCalc*>& GetStrategies(void);
        virtual void AssignStrategy(const std::string &name);

    private:
        std::map<std::string,HeatCalc*> calc_strategies;
        double Re_in;
        double Pr_in;
        HeatCalc *calc_strategy;
};

#endif // HEATEXCHANGER_ST_H_INCLUDED
