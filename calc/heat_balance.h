#ifndef HEAT_BALANCE_H_INCLUDED
#define HEAT_BALANCE_H_INCLUDED

#include "substance.h"

class HeatBalance
{
    public:
        virtual ~HeatBalance();

        static HeatBalance& GetInstance(void);
        void Calculate(void);

    protected:

    private:
        HeatBalance() { };
        HeatBalance(const HeatBalance&);
        HeatBalance& operator=(const HeatBalance&);
};

#endif // HEAT_BALANCE_H_INCLUDED
