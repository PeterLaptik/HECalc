#ifndef INPUT_GRID_H_INCLUDED
#define INPUT_GRID_H_INCLUDED

#define TEST

#include "input_grid_props.h"
#include <wx/propgrid/propgrid.h>
#include <map>

// Grid for input calculation data
class HEInputGrid: public wxPropertyGrid
{
    public:
        HEInputGrid(wxWindow *parent, wxWindowID id);
        virtual ~HEInputGrid();

        #ifdef TEST
            void TestCase_1(void);
        #endif // TEST

    protected:
        void OnPropertyChanged(wxCommandEvent &event);
        // Properties pointers
        wxPGProperty *section_substance_1;
        wxPGProperty *section_substance_props_1;
        wxPropertySubstance *prop_substance_name_1;
        wxPGProperty *prop_substance_density_1;
        wxPGProperty *prop_substance_heatcapacity_1;
        wxPGProperty *prop_substance_heatvaporization_1;
        wxPGProperty *prop_substance_heatcondensation_1;
        wxPGProperty *prop_substance_thermalconductivity_1;
        wxPGProperty *prop_substance_viscosity_1;
        wxPGProperty *section_flow_1;
        wxPGProperty *prop_flow_1;
        wxPGProperty *prop_t_inlet_1;
        wxPGProperty *prop_t_outlet_1;
        wxPGProperty *section_substance_2;
        wxPGProperty *section_substance_props_2;
        wxPropertySubstance *prop_substance_name_2;
        wxPGProperty *prop_substance_density_2;
        wxPGProperty *prop_substance_heatcapacity_2;
        wxPGProperty *prop_substance_heatvaporization_2;
        wxPGProperty *prop_substance_heatcondensation_2;
        wxPGProperty *prop_substance_thermalconductivity_2;
        wxPGProperty *prop_substance_viscosity_2;
        wxPGProperty *section_flow_2;
        wxPGProperty *prop_flow_2;
        wxPGProperty *prop_t_inlet_2;
        wxPGProperty *prop_t_outlet_2;
        wxPGProperty *section_settings;
        wxEnumProperty *prop_unknown_value;
        wxEnumProperty *prop_flow_type;

    private:
        void InitWithDefaultSubstances(void);

        // ChoiceBox - Property mapping and ChoiceBox values
        // See constructor
        wxArrayString unknown_values;
        std::map<int, wxString> unknown_values_map;
        std::map<int, wxPGProperty*> unknown_props_map;
        wxArrayString flow_directions;
};

#endif // INPUT_GRID_H_INCLUDED
