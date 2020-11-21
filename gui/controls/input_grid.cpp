#include "input_grid.h"
#include "../dialogues/dlgsubstance.h"
#include "../../calc/input_data.h"
#include "../../calc/heat_balance.h"
#include "../events/events.h"


// Custom event to notify high-level window on input data updating
// See event.h
wxDEFINE_EVENT(wxINPUT_UPDATED, EventInputUpdated);


HEInputGrid::HEInputGrid(wxWindow *parent, wxWindowID id)
    : wxPropertyGrid(parent, id, wxDefaultPosition, wxDefaultSize, wxPG_SPLITTER_AUTO_CENTER)
{
    // Add default fields
    // Substance #1
    section_substance_1 = this->Append(new wxPropertyCategory(_("Substance 1")));
    prop_substance_name_1 = dynamic_cast<wxPropertySubstance*>(this->Append(new wxPropertySubstance(this, _("Name 1"))));
    section_substance_props_1 = this->Append(new wxPropertyCategory(_("Substance 1 properties")));
    prop_substance_density_1 = this->Append(new wxFloatProperty(_("Density r1, kg/cub. m")));
    prop_substance_heatcapacity_1 = this->Append(new wxFloatProperty(_("Heat capacity c1, J/(kg.K)")));
    prop_substance_heatvaporization_1 = this->Append(new wxFloatProperty(_("Heat vaporization R1, J/kg")));
    prop_substance_heatcondensation_1 = this->Append(new wxFloatProperty(_("Heat condensation R1, J/kg")));
    prop_substance_thermalconductivity_1 = this->Append(new wxFloatProperty("Thermal conductivity q1, J/(kg.K)"));
    prop_substance_viscosity_1 = this->Append(new wxFloatProperty(_("Viscosity v1, Pa.sec")));
    // Flow #1
    section_flow_1 = this->Append(new wxPropertyCategory(_("Flow 1 (in pipes)")));
    prop_flow_1 = this->Append(new wxFloatProperty(_("Flow rate G1, kg/sec")));
    prop_t_inlet_1 = this->Append(new wxFloatProperty(_("Inlet temperature T1in, deg. C")));
    prop_t_outlet_1 = this->Append(new wxFloatProperty(_("Outlet temperature T1out, deg. C")));
    // Substance #2
    section_substance_2 = this->Append(new wxPropertyCategory(_("Substance 2")));
    prop_substance_name_2 = dynamic_cast<wxPropertySubstance*>(this->Append(new wxPropertySubstance(this, _("Name 2"))));
    section_substance_props_2 = this->Append(new wxPropertyCategory(_("Substance 2 properties")));
    prop_substance_density_2 = this->Append(new wxFloatProperty(_("Density r2, kg/cub. m")));
    prop_substance_heatcapacity_2 = this->Append(new wxFloatProperty(_("Heat capacity c2, J/(kg.K)")));
    prop_substance_heatvaporization_2 = this->Append(new wxFloatProperty(_("Heat vaporization R2, J/kg")));
    prop_substance_heatcondensation_2 = this->Append(new wxFloatProperty(_("Heat condensation R2, J/kg")));
    prop_substance_thermalconductivity_2 = this->Append(new wxFloatProperty(_("Thermal conductivity q2, J/(kg.K)")));
    prop_substance_viscosity_2 = this->Append(new wxFloatProperty(_("Viscosity v2, Pa.sec")));
    // Flow #2
    section_flow_2 = this->Append(new wxPropertyCategory(_("Flow 2 (out pipes)")));
    prop_flow_2 = this->Append(new wxFloatProperty(_("Flow rate G2, kg/sec")));
    prop_t_inlet_2 = this->Append(new wxFloatProperty(_("Inlet temperature T2in, deg. C")));
    prop_t_outlet_2 = this->Append(new wxFloatProperty(_("Outlet temperature T2out, deg. C")));
    section_settings = this->Append(new wxPropertyCategory(_("Settings")));
    // Flow direction
    flow_directions.Add("counter-current");     // #0
    flow_directions.Add("so-current");          // #1
    prop_flow_type = dynamic_cast<wxEnumProperty*>(this->Append(new wxEnumProperty(_("Direction"), wxPG_LABEL, flow_directions)));
    // Unknown values
    // Insert unknown values enumeration
    unknown_values_map = {{0, "G1"}, {1, "T1in"}, {2, "T1out"}, {3, "G2"}, {4, "T2in"}, {5, "T2out"}};
    unknown_props_map.insert({{0, prop_flow_1}, {1, prop_t_inlet_1}, {2, prop_t_outlet_1},
                            {3, prop_flow_2}, {4, prop_t_inlet_2}, {5, prop_t_outlet_2}});

    for(auto i: unknown_values_map)
        unknown_values.Add(i.second);

    prop_unknown_value = dynamic_cast<wxEnumProperty*>(this->Append(new wxEnumProperty(_("Unknown value"), wxPG_LABEL, unknown_values)));

    // Size
    this->SetColumnProportion(0, 4);
    this->SetColumnProportion(1, 1);
    // Collapse substance properties
    this->Collapse(section_substance_props_1);
    this->Collapse(section_substance_props_2);
    // Event handling and default values
    Connect(wxID_ANY, wxEVT_PG_CHANGED,(wxObjectEventFunction)&HEInputGrid::OnPropertyChanged);
    InitWithDefaultSubstances();
}

HEInputGrid::~HEInputGrid()
{ }


// Show property values for the substances assigned by default
void HEInputGrid::InitWithDefaultSubstances()
{
    // Send dummy events to fill substances properties of the grid
    wxPostEvent(this, wxCommandEvent(wxEVT_PG_CHANGED, prop_substance_name_1->GetId()));
    wxPostEvent(this, wxCommandEvent(wxEVT_PG_CHANGED, prop_substance_name_2->GetId()));
}

// Refreshes substances properties
// The properties are to be refreshed only if a substance has been changed,
// to avoid by-hand changes to be reseted
void HEInputGrid::OnPropertyChanged(wxCommandEvent &event)
{
    int win_id = event.GetId();
    // First substance
    if(win_id==prop_substance_name_1->GetId())
    {
        prop_substance_density_1->SetValue(prop_substance_name_1->GetSubstance().density);
        prop_substance_heatcapacity_1->SetValue(prop_substance_name_1->GetSubstance().heat_capacity);
        prop_substance_heatvaporization_1->SetValue(prop_substance_name_1->GetSubstance().heat_vaporization);
        prop_substance_heatcondensation_1->SetValue(prop_substance_name_1->GetSubstance().heat_condensation);
        prop_substance_thermalconductivity_1->SetValue(prop_substance_name_1->GetSubstance().thermal_conductivity);
        prop_substance_viscosity_1->SetValue(prop_substance_name_1->GetSubstance().viscosity);
    }
    // Second substance
    if(win_id==prop_substance_name_2->GetId())
    {
        prop_substance_density_2->SetValue(prop_substance_name_2->GetSubstance().density);
        prop_substance_heatcapacity_2->SetValue(prop_substance_name_2->GetSubstance().heat_capacity);
        prop_substance_heatvaporization_2->SetValue(prop_substance_name_2->GetSubstance().heat_vaporization);
        prop_substance_heatcondensation_2->SetValue(prop_substance_name_2->GetSubstance().heat_condensation);
        prop_substance_thermalconductivity_2->SetValue(prop_substance_name_2->GetSubstance().thermal_conductivity);
        prop_substance_viscosity_2->SetValue(prop_substance_name_2->GetSubstance().viscosity);
    }
    // Disable unknown property
    int unknown = prop_unknown_value->GetChoiceSelection();
    std::map<int, wxPGProperty*>::iterator values = unknown_props_map.find(unknown);
    if(values!=unknown_props_map.end())
    {
        for(auto i: unknown_props_map)
            i.second->Enable(true);
         // Disable only selected value
        (*values).second->Enable(false);
    }
    // Assign property values
    InputData &input_data = InputData::GetInstance();
    // Flow #1
    input_data.flow_1.GetSubstance().name = prop_substance_name_1->GetValueString();
    input_data.flow_1.GetSubstance().density = prop_substance_density_1->GetValue();
    input_data.flow_1.GetSubstance().heat_capacity = prop_substance_heatcapacity_1->GetValue();
    input_data.flow_1.GetSubstance().heat_vaporization = prop_substance_heatvaporization_1->GetValue();
    input_data.flow_1.GetSubstance().heat_condensation = prop_substance_heatcondensation_1->GetValue();
    input_data.flow_1.GetSubstance().thermal_conductivity = prop_substance_thermalconductivity_1->GetValue();
    input_data.flow_1.GetSubstance().viscosity = prop_substance_viscosity_1->GetValue();
    input_data.flow_1.SetFlowRate(prop_flow_1->GetValue());
    input_data.flow_1.SetInletTemperature(prop_t_inlet_1->GetValue());
    input_data.flow_1.SetOutletTemperature(prop_t_outlet_1->GetValue());
    // Flow #2
    input_data.flow_2.GetSubstance().name = prop_substance_name_2->GetValueString();
    input_data.flow_2.GetSubstance().density = prop_substance_density_2->GetValue();
    input_data.flow_2.GetSubstance().heat_capacity = prop_substance_heatcapacity_2->GetValue();
    input_data.flow_2.GetSubstance().heat_vaporization = prop_substance_heatvaporization_2->GetValue();
    input_data.flow_2.GetSubstance().heat_condensation = prop_substance_heatcondensation_2->GetValue();
    input_data.flow_2.GetSubstance().thermal_conductivity = prop_substance_thermalconductivity_2->GetValue();
    input_data.flow_2.GetSubstance().viscosity = prop_substance_viscosity_2->GetValue();
    input_data.flow_2.SetFlowRate(prop_flow_2->GetValue());
    input_data.flow_2.SetInletTemperature(prop_t_inlet_2->GetValue());
    input_data.flow_2.SetOutletTemperature(prop_t_outlet_2->GetValue());
    // Assign unknown value
    switch(unknown)
    {
        case 0:
            input_data.flow_1.SetUnknownValue(UNKN_RATE);
            input_data.flow_2.SetUnknownValue(UNKN_NONE);
            break;
        case 1:
            input_data.flow_1.SetUnknownValue(UNKN_T_IN);
            input_data.flow_2.SetUnknownValue(UNKN_NONE);
            break;
        case 2:
            input_data.flow_1.SetUnknownValue(UNKN_T_OUT);
            input_data.flow_2.SetUnknownValue(UNKN_NONE);
            break;
        case 3:
            input_data.flow_2.SetUnknownValue(UNKN_RATE);
            input_data.flow_1.SetUnknownValue(UNKN_NONE);
            break;
        case 4:
            input_data.flow_2.SetUnknownValue(UNKN_T_IN);
            input_data.flow_1.SetUnknownValue(UNKN_NONE);
            break;
        case 5:
            input_data.flow_2.SetUnknownValue(UNKN_T_OUT);
            input_data.flow_1.SetUnknownValue(UNKN_NONE);
            break;
    }
    // Flows directions
    int direction = prop_flow_type->GetChoiceSelection();
    switch(direction)
    {
        case 0:
            input_data.direction = FLOW_COUNTER_CURRENT;
            break;
        case 1:
            input_data.direction = FLOW_SO_CURRENT;
            break;
    }
    // Notify parent frames about updated input data
    wxPostEvent(this, EventInputUpdated(wxINPUT_UPDATED, this->GetId()));
}
