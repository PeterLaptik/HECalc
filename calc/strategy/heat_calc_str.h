#ifndef HEATCALCSTDYTN_H_INCLUDED
#define HEATCALCSTDYTN_H_INCLUDED

#include "../heat_calc.h"

class HeatCalcStDytn: public HeatCalc
{
    public:
        virtual void Calculate(void);

        virtual double GetNuInner(void) const;
        virtual double GetAlphaInner(void) const;

        virtual std::string GetName(void)
        {
            return "Dytnersky";
        }

};

class HeatCalcTest: public HeatCalc
{
    public:
        virtual void Calculate(void);

        virtual double GetNuInner(void) const;
        virtual double GetAlphaInner(void) const;

        virtual std::string GetName(void)
        {
            return "Test";
        }
};

#endif // HEATCALCSTDYTN_H_INCLUDED
