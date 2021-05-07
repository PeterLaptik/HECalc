#include "equipment_grid.h"
#include "../../calc/output_data.h"
#include "../../calc/heatexchanger_st.h"
#include "../events/events.h"
#include <wx/msgdlg.h>

EquipmentGrid::EquipmentGrid(wxWindow *parent, wxWindowID id)
    : wxPropertyGrid(parent, id, wxDefaultPosition, wxDefaultSize, wxPG_SPLITTER_AUTO_CENTER)
{
    this->Append(new wxPropertyCategory(_("Type")));
    m_types.Add(_("Shell tube heat exchanger"));
    m_types.Add(_("Floating head heat exchanger"));
    he_type = dynamic_cast<wxEnumProperty*>(this->Append(new wxEnumProperty(_("Heat exchanger type"), wxPG_LABEL, m_types)));
    calc_strategy = dynamic_cast<wxEnumProperty*>(this->Append(new wxEnumProperty(_("Calculation type"), wxPG_LABEL, m_strategies)));
    this->Append(new wxPropertyCategory(_("Geometry")));
    prop_pipe_diameter = this->Append(new wxFloatProperty(_("Pipe outer diameter, mm")));
    prop_pipe_thickness = this->Append(new wxFloatProperty(_("Pipe thickness, mm")));
    prop_pipe_length = this->Append(new wxFloatProperty(_("Pipe length, m")));
    prop_pipe_number = this->Append(new wxIntProperty(_("Number of pipes")));
    prop_number_of_passes =  this->Append(new wxIntProperty(_("Number of passes")));
    prop_shell_diameter = this->Append(new wxFloatProperty(_("Shell inner diameter, mm")));
    RefreshStrategyList();
    // Bind event
    Connect(wxID_ANY, wxEVT_PG_CHANGED,(wxObjectEventFunction)&EquipmentGrid::OnPropertyChanged);
}

EquipmentGrid::~EquipmentGrid()
{ }

void EquipmentGrid::OnPropertyChanged(wxCommandEvent &event)
{
    HeatExchanger *he = OutputData::GetInstance().GetEquipmentUnit();

    if(dynamic_cast<HeatExchangerShellTube*>(he))
        UpdateShellTubeHe(dynamic_cast<HeatExchangerShellTube*>(he));

    he->AssignStrategy(calc_strategy->GetValueAsString().ToStdString());

    // Notify parent frames about updated equipment data
    wxPostEvent(this, EventInputUpdated(wxINPUT_UPDATED, this->GetId()));
}

void EquipmentGrid::RefreshStrategyList()
{
    m_strategies.Clear();
    HeatExchanger *he = OutputData::GetInstance().GetEquipmentUnit();
    const std::map<std::string,HeatCalc*> s_list = he->GetStrategies();
    for(std::map<std::string,HeatCalc*>::const_iterator it=s_list.begin(); it!=s_list.end(); ++it)
        calc_strategy->AddChoice((*it).first);
    calc_strategy->SetChoiceSelection(0);

    if(s_list.size()<1)
        return;

    //wxMessageBox("lll"/*calc_strategy->GetDisplayedString()*/);
}

void EquipmentGrid::UpdateShellTubeHe(HeatExchangerShellTube *he)
{
    long value;
    he->pipe_outer_diameter = static_cast<double>(prop_pipe_diameter->GetValue())/1000;
    he->pipe_thickness = static_cast<double>(prop_pipe_thickness->GetValue())/1000;
    value = prop_pipe_number->GetValue();
    he->pipe_number = static_cast<int>(value);
    he->shell_inner_diameter = static_cast<double>(prop_shell_diameter->GetValue())/1000;
    value = prop_number_of_passes->GetValue();
    he->passes_number = static_cast<int>(value);
    he->pipe_length = static_cast<double>(prop_pipe_length->GetValue());
}
