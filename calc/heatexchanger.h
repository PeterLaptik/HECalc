#ifndef HEATEXCHANGER_H_INCLUDED
#define HEATEXCHANGER_H_INCLUDED

class HeatExchanger
{
    public:
        virtual void Calculate(void) = 0;

        virtual double GetReInner(void) = 0;
        virtual double GetPrInner(void) = 0;
};

#endif // HEATEXCHANGER_H_INCLUDED
