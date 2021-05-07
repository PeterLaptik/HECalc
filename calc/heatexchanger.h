#ifndef HEATEXCHANGER_H_INCLUDED
#define HEATEXCHANGER_H_INCLUDED

#include <map>

class HeatCalc;

class HeatExchanger
{
    public:
        HeatExchanger() {}
        virtual ~HeatExchanger() {}

        virtual void Calculate(void) = 0;

        virtual double GetReInner(void) const = 0;
        virtual double GetPrInner(void) const = 0;
        virtual double GetNuInner(void) const = 0;
        virtual double GetAlphaInner(void) const = 0;
        virtual const std::map<std::string,HeatCalc*>& GetStrategies(void) = 0;
        virtual void AssignStrategy(const std::string &name) = 0;

        friend class HeatCalc;
};

#endif // HEATEXCHANGER_H_INCLUDED
