#ifndef HEAT_CALC_H_INCLUDED
#define HEAT_CALC_H_INCLUDED

#include "heatexchanger.h"
#include <string>
#include <map>

// Strategy
// Implementation of calculation
class HeatCalc
{
    public:
        void AssignHeatExchanger(HeatExchanger *parent)
        {
            he = parent;
        }

        static void AssignStrategies(std::map<std::string,HeatCalc*> &strategies, HeatExchanger *he);

        virtual void Calculate(void) = 0;

        virtual double GetNuInner(void) const = 0;
        virtual double GetAlphaInner(void) const = 0;
        virtual std::string GetName(void) = 0;

    protected:
        HeatExchanger *he;
        double Nu;
        double alpha_in;
};

#endif // HEAT_CALC_H_INCLUDED
