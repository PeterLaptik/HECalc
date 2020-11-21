#ifndef HEAT_BALANCE_H_INCLUDED
#define HEAT_BALANCE_H_INCLUDED

#include "substance.h"

class HeatBalance
{
    public:
        virtual ~HeatBalance();

        static HeatBalance& GetInstance(void);

        Substance& GetSubstanceInPipes(void);
        Substance& GetSubstanceOutPipes(void);

    protected:

    private:
        static HeatBalance *instance;

        HeatBalance();
        HeatBalance(const HeatBalance&);
        HeatBalance& operator=(const HeatBalance&);

        Substance substance_1;
        Substance substance_2;
};

#endif // HEAT_BALANCE_H_INCLUDED
