#include "output_data.h"
#include "heatexchanger.h"
#include "heatexchanger_st.h"

OutputData::OutputData()
{
    m_type = SHELL_TUBE_HE;
    he = new HeatExchangerShellTube();
}

OutputData& OutputData::GetInstance()
{
    static OutputData instance;
    return instance;
}

HeatExchanger* OutputData::GetEquipmentUnit()
{
    return he;
}

OutputData::~OutputData()
{ }
