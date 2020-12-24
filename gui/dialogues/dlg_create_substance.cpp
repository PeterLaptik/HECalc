#include "dlg_create_substance.h"
#include "../../calc/substance.h"
#include <wx/msgdlg.h>

static const int ROW_NAME = 0;
static const int ROW_DENSITY = 1;
static const int ROW_HEAT_CAPACITY = 2;
static const int ROW_HEAT_VAPORIZATION = 3;
static const int ROW_HEAT_CONDENSATION = 4;
static const int ROW_THERMAL_CONDUCTIVITY = 5;
static const int ROW_VISCOSITY = 6;
static const int ROW_NOTES = 7;
// Controls ids
static const int id_button_add = wxNewId();
static const int id_button_cancel = wxNewId();


wxBEGIN_EVENT_TABLE(DlgCreateSubstance,wxDialog)
    EVT_CHOICE(wxID_ANY, DlgCreateSubstance::OnChoice)
    EVT_BUTTON(id_button_add, DlgCreateSubstance::OnAddSubstance)
    EVT_BUTTON(id_button_cancel, DlgCreateSubstance::OnCancel)
wxEND_EVENT_TABLE()


DlgCreateSubstance::DlgCreateSubstance(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	substance_created = false;

	wxBoxSizer* box_sizer_v;
	box_sizer_v = new wxBoxSizer(wxVERTICAL);

	m_grid = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	// Grid
	m_grid->CreateGrid(8, 1);
	m_grid->EnableEditing(true);
	m_grid->EnableGridLines(true);
	m_grid->EnableDragGridSize(false);
	m_grid->SetMargins(0, 0);

	// Columns
	m_grid->EnableDragColMove(false);
	m_grid->EnableDragColSize(true);
	m_grid->SetColLabelSize(30);
	m_grid->SetColLabelValue(0, wxT("value"));
	m_grid->SetColLabelAlignment(wxALIGN_LEFT, wxALIGN_CENTER);

	// Rows
	m_grid->EnableDragRowSize(true);
	m_grid->SetRowLabelSize(280);
	m_grid->SetRowLabelValue(ROW_NAME, wxT("Name"));
	m_grid->SetRowLabelValue(ROW_DENSITY, wxT("Density, kg/cub.m"));
	m_grid->SetRowLabelValue(ROW_HEAT_CAPACITY, wxT("Heat capacity, J/(kg.deg.C)"));
	m_grid->SetRowLabelValue(ROW_HEAT_VAPORIZATION, wxT("Vapotization heat, J/kg"));
	m_grid->SetRowLabelValue(ROW_HEAT_CONDENSATION, wxT("Condensation heat, J/kg"));
	m_grid->SetRowLabelValue(ROW_THERMAL_CONDUCTIVITY, wxT("Thermal conductivity, W/(m.deg.C)"));
	m_grid->SetRowLabelValue(ROW_VISCOSITY, wxT("Viscosity, Pa.s"));
	m_grid->SetRowLabelValue(ROW_NOTES, wxT("Notes"));
	m_grid->SetRowLabelAlignment(wxALIGN_LEFT, wxALIGN_CENTER);

	// Cell Defaults
	m_grid->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);
	box_sizer_v->Add(m_grid, 0, wxALL, 5);

	wxArrayString m_choiceChoices;
	m_choice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceChoices, 0);
	// Initialize choices
	for(int i=0; i<6; i++)
    {
        m_choice->Append(Substance::GetTypeNameFor(static_cast<FluidType>(i)));
    }
	m_choice->SetSelection(0);
	box_sizer_v->Add(m_choice, 0, wxALL|wxEXPAND, 5);

	wxBoxSizer* box_sizer_h;
	box_sizer_h = new wxBoxSizer(wxHORIZONTAL);

	m_button_add = new wxButton(this, id_button_add, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
	box_sizer_h->Add(m_button_add, 0, wxALL, 5);

	m_button_cancel = new wxButton(this, id_button_cancel, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0);

	box_sizer_h->Add(m_button_cancel, 0, wxALL, 5);
	box_sizer_v->Add(box_sizer_h, 1, wxALIGN_RIGHT, 5);

	this->SetSizer(box_sizer_v);
	this->Layout();

	this->Centre(wxBOTH);
	RefreshTable();
}

DlgCreateSubstance::~DlgCreateSubstance()
{ }


void DlgCreateSubstance::RefreshTable()
{
    int choice = m_choice->GetSelection();
    FluidType fluid = static_cast<FluidType>(choice);
    switch(fluid)
    {
        case F_GAS:
        case F_LIQUID:
        case F_WATER:
            m_grid->SetReadOnly(ROW_HEAT_CONDENSATION, 0, true);
            m_grid->SetReadOnly(ROW_HEAT_VAPORIZATION, 0, true);
            m_grid->SetReadOnly(ROW_HEAT_CAPACITY, 0, false);
            break;
        case F_CONDENSING_VAPOUR:
        case F_CONDENSING_VAPOUR_WATER:
            m_grid->SetReadOnly(ROW_HEAT_CONDENSATION, 0, false);
            m_grid->SetReadOnly(ROW_HEAT_VAPORIZATION, 0, true);
            m_grid->SetReadOnly(ROW_HEAT_CAPACITY, 0, true);
            break;
        case F_BOILING_LIQUID:
            m_grid->SetReadOnly(ROW_HEAT_CONDENSATION, 0, true);
            m_grid->SetReadOnly(ROW_HEAT_VAPORIZATION, 0, false);
            m_grid->SetReadOnly(ROW_HEAT_CAPACITY, 0, true);
            break;
    }
}

void DlgCreateSubstance::OnChoice(wxCommandEvent &event)
{
    RefreshTable();
}

void DlgCreateSubstance::OnAddSubstance(wxCommandEvent &event)
{
    Substance result;

    // Clear result values
    result.name = result.notes = "";
    result.density = result.heat_capacity = result.heat_condensation = result.heat_vaporization
    = result.thermal_conductivity = result.viscosity = 0;
    result.type = static_cast<FluidType>(m_choice->GetSelection());

    // Check substance data
    if(m_grid->GetCellValue(ROW_NAME, 0).Trim()=="")
        return ShowMessage(_("The substance name is not defined!"));

    result.name = m_grid->GetCellValue(ROW_NAME, 0);

    // Are the values numeric
    if(!m_grid->GetCellValue(ROW_DENSITY, 0).ToDouble(&result.density))
        return ShowMessage(_("Wrong density value!"));

    if(((result.type==F_GAS)||(result.type==F_LIQUID)||(result.type==F_WATER))
       && (!m_grid->GetCellValue(ROW_HEAT_CAPACITY, 0).ToDouble(&result.heat_capacity)))
       return ShowMessage(_("Wrong heat capacity value!"));

    if(((result.type==F_CONDENSING_VAPOUR)||(result.type==F_CONDENSING_VAPOUR_WATER))
       && (!m_grid->GetCellValue(ROW_HEAT_CONDENSATION, 0).ToDouble(&result.heat_condensation)))
       return ShowMessage(_("Wrong condensation heat value!"));

    if((result.type==F_BOILING_LIQUID)
       && (!m_grid->GetCellValue(ROW_HEAT_VAPORIZATION, 0).ToDouble(&result.heat_vaporization)))
       return ShowMessage(_("Wrong vaporisation heat value!"));

    if(!m_grid->GetCellValue(ROW_THERMAL_CONDUCTIVITY, 0).ToDouble(&result.thermal_conductivity))
        return ShowMessage(_("Wrong thermal conductivity value!"));

    if(!m_grid->GetCellValue(ROW_VISCOSITY, 0).ToDouble(&result.viscosity))
        return ShowMessage(_("Wrong viscosity value!"));

    result.notes = m_grid->GetCellValue(ROW_NOTES, 0);

    if(!CheckResult(result))
        return;

    substance_created = true;
    substance = result;
    this->Destroy();
}

// Checks numeric data: the values are to be higher than zero
// Maximum values are not checked
bool DlgCreateSubstance::CheckResult(const Substance &result)
{
    static wxString ok_msg = wxT("OK");
    wxString msg = ok_msg;

    if(result.density<=0)
        msg = _("Wrong density value!");

    if(((result.type==F_GAS)||(result.type==F_LIQUID)||(result.type==F_WATER))
       && (result.heat_capacity<=0))
       msg = _("Wrong heat capacity value!");

    if(((result.type==F_CONDENSING_VAPOUR)||(result.type==F_CONDENSING_VAPOUR_WATER))
       && (result.heat_condensation<=0))
       msg = _("Wrong condensation heat value!");

    if((result.type==F_BOILING_LIQUID)
       && (result.heat_vaporization<=0))
       msg = _("Wrong vaporisation heat value!");

    if(result.thermal_conductivity<=0)
        msg = _("Wrong thermal conductivity value!");

    if(result.viscosity<=0)
        msg = _("Wrong viscosity value!");

    if(msg!=ok_msg)
    {
        wxMessageBox(msg);
        substance_created = false;
        return false;
    }
    return true;
}

void DlgCreateSubstance::ShowMessage(const wxString &msg)
{
    wxMessageBox(msg);
}

void DlgCreateSubstance::OnCancel(wxCommandEvent &event)
{
    this->Destroy();
}
