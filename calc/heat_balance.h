#ifndef HEAT_BALANCE_H_INCLUDED
#define HEAT_BALANCE_H_INCLUDED

#include "substance.h"

class HeatBalance
{
    public:
        virtual ~HeatBalance();

        static HeatBalance& GetInstance(void);
        void Calculate(void);

        void SetPrelimHeatTransferCoefficient(double coeff);

        double GetHeatFlow(void) const
        {
            return heat_flow;
        }

        double GetTemperatureDifference(void) const
        {
            return dT;
        }

    protected:

    private:
        HeatBalance();
        HeatBalance(const HeatBalance&);
        HeatBalance& operator=(const HeatBalance&);
        void CalculateMeanTemperatureDifference(void);

        double heat_flow;
        double K;   // Preliminary heat transfer coefficient
        double dT;  // Mean logarithmic temperature difference
};

#endif // HEAT_BALANCE_H_INCLUDED
