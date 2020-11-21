#include "heat_balance.h"

HeatBalance::HeatBalance()
{ }

HeatBalance::~HeatBalance()
{ }


HeatBalance& HeatBalance::GetInstance()
{
    static HeatBalance instance;
    return instance;
}

Substance& HeatBalance::GetSubstanceInPipes(void)
{
    return substance_1;
}

Substance& HeatBalance::GetSubstanceOutPipes(void)
{
    return substance_2;
}
