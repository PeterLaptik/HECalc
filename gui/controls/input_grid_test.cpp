#include "input_grid.h"
#include "../../calc/input_data.h"
#include "../events/events.h"

void HEInputGrid::TestCase_1()
{
    InputData &data = InputData::GetInstance();
    data.flow_1.SetUnknownValue(UNKN_NONE);
    data.flow_2.SetUnknownValue(UNKN_T_OUT);

    prop_flow_1->SetValue(6.0);
    prop_t_inlet_1->SetValue(112.5);
    prop_t_outlet_1->SetValue(40);
    prop_substance_density_1->SetValue(986);
    prop_substance_heatcapacity_1->SetValue(4190);
    prop_substance_thermalconductivity_1->SetValue(0.662);
    prop_substance_viscosity_1->SetValue(0.00054);

    prop_flow_2->SetValue(21.8);
    prop_t_inlet_2->SetValue(20);
    prop_unknown_value->SetChoiceSelection(5);
    prop_substance_density_2->SetValue(996);
    prop_substance_heatcapacity_2->SetValue(4180);
    prop_substance_thermalconductivity_2->SetValue(0.618);
    prop_substance_viscosity_2->SetValue(0.000804);
    // Update all
    wxPostEvent(this, wxCommandEvent(wxEVT_PG_CHANGED, this->GetId()));
}
