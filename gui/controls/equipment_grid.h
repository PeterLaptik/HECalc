#ifndef EQUIPMENT_GRID_H_INCLUDED
#define EQUIPMENT_GRID_H_INCLUDED

#include <wx/propgrid/propgrid.h>

#define TEST

class HeatExchangerShellTube;

enum HeatExchangerType
{
    HE_TUBE_SHELL,
    HE_FLOATING_HEAD
};

class EquipmentGrid: public wxPropertyGrid
{
    public:
        EquipmentGrid(wxWindow *parent, wxWindowID id);
        virtual ~EquipmentGrid();
        wxEnumProperty *he_type;
        wxEnumProperty *calc_strategy;
        // Heat exchanger geometry
        wxPGProperty *prop_pipe_diameter;
        wxPGProperty *prop_pipe_number;
        wxPGProperty *prop_pipe_length;
        wxPGProperty *prop_shell_diameter;
        /*****/
        wxPGProperty *prop_pipe_thickness;
        wxPGProperty *prop_number_of_passes;

        wxPGProperty *prop_separator_free_area;
        wxPGProperty *prop_material;
        wxPGProperty *prop_material_heat_capacity;
        /*******/

        #ifdef TEST
            void TestCase_1(void);
        #endif // TEST

    protected:
        long strategy_id, type_id;
        void OnPropertyChanged(wxCommandEvent &event);
        void UpdateShellTubeHe(HeatExchangerShellTube *he);
        void RefreshStrategyList(void);

    private:
        // List of heat-exchangers types possible to be computed
        wxArrayString m_types;
        // Calculation strategies
        wxArrayString m_strategies;
};

#endif // EQUIPMENT_GRID_H_INCLUDED
