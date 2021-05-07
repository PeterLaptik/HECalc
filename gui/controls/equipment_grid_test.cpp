#include "equipment_grid.h"

void EquipmentGrid::TestCase_1()
{
    prop_pipe_diameter->SetValue(25);
    prop_pipe_thickness->SetValue(2);
    prop_pipe_length->SetValue(2.1);
    prop_pipe_number->SetValue(206);
    prop_number_of_passes->SetValue(4);
    prop_shell_diameter->SetValue(600);
    // Update all
    wxPostEvent(this, wxCommandEvent(wxEVT_PG_CHANGED, this->GetId()));
}
