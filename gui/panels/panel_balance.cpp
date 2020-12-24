#include "panel_balance.h"
#include "../controls/drafter.h"
#include "../../calc/heat_balance.h"
#include "../../calc/input_data.h"
#include <wx/msgdlg.h>

static const int CHOICE_FLOW_ID = wxNewId();
static const int CHOICE_K_ID = wxNewId();
static const int HT_COEFF_DEVIDED_PARTS = 4; // Parts number for heat transfer coefficient margin dividing

wxBEGIN_EVENT_TABLE(BalancePanel, wxPanel)
    EVT_COMMAND(CHOICE_FLOW_ID, wxEVT_COMMAND_CHOICE_SELECTED, BalancePanel::OnFLowTypeCHanged)
    EVT_COMMAND(CHOICE_K_ID, wxEVT_COMMAND_CHOICE_SELECTED, BalancePanel::OnCoeffSelectionChanged)
wxEND_EVENT_TABLE()


BalancePanel::BalancePanel(wxWindow* parent,
                           wxWindowID id,
                           const wxPoint& pos,
                           const wxSize& size,
                           long style,
                           const wxString& name)
                : wxPanel(parent, id, pos, size, style, name)
{
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer(wxHORIZONTAL);

	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer(8, 2, 0, 0);
	fgSizer3->SetFlexibleDirection(wxBOTH);
	fgSizer3->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_static_text_hf = new wxStaticText(this, wxID_ANY, wxT("Heat capacity"), wxDefaultPosition, wxDefaultSize, 0);
	m_static_text_hf->Wrap(-1);
	fgSizer3->Add(m_static_text_hf, 0, wxALL, 5);

	m_text_heat_flow = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxBORDER_SIMPLE);
	fgSizer3->Add(m_text_heat_flow, 0, wxALL, 5);

	m_static_text_result = new wxStaticText(this, wxID_ANY, wxT("Result"), wxDefaultPosition, wxDefaultSize, 0);
	m_static_text_result->Wrap(-1);
	fgSizer3->Add(m_static_text_result, 0, wxALL, 5);

	m_text_result = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxBORDER_SIMPLE);
	fgSizer3->Add(m_text_result, 0, wxALL, 5);

	m_static_text_t_diff = new wxStaticText(this, wxID_ANY, wxT("Mean temperature difference"), wxDefaultPosition, wxDefaultSize, 0);
	m_static_text_t_diff->Wrap(-1);
	fgSizer3->Add(m_static_text_t_diff, 0, wxALL, 5);

	m_text_t_diff = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxBORDER_SIMPLE);
	fgSizer3->Add(m_text_t_diff, 0, wxALL, 5);

	m_static_text_subst_1 = new wxStaticText(this, wxID_ANY, wxT("Substance #1 type:"), wxDefaultPosition, wxDefaultSize, 0);
	m_static_text_subst_1->Wrap(-1);
	fgSizer3->Add(m_static_text_subst_1, 0, wxALL, 5);

	m_text_subst_type_1 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxBORDER_SIMPLE);
	fgSizer3->Add(m_text_subst_type_1, 0, wxALL, 5);

	m_static_text_subst_2 = new wxStaticText(this, wxID_ANY, wxT("Substance #2 type"), wxDefaultPosition, wxDefaultSize, 0);
	m_static_text_subst_2->Wrap(-1);
	fgSizer3->Add(m_static_text_subst_2, 0, wxALL, 5);

	m_text_subst_type_2 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxBORDER_SIMPLE);
	fgSizer3->Add(m_text_subst_type_2, 0, wxALL, 5);

	m_static_text_flow = new wxStaticText(this, wxID_ANY, wxT("Flow type"), wxDefaultPosition, wxDefaultSize, 0);
	m_static_text_flow->Wrap(-1);
	fgSizer3->Add(m_static_text_flow, 0, wxALL, 5);

	m_flow_type.Add("forced");
	m_flow_type.Add("non-forced");
	m_choice_flow_type = new wxChoice(this, CHOICE_FLOW_ID, wxDefaultPosition, wxDefaultSize, m_flow_type, 0);
	m_choice_flow_type->SetSelection(0);
	fgSizer3->Add(m_choice_flow_type, 0, wxALL, 5);

	m_static_text_coeff = new wxStaticText(this, wxID_ANY, wxT("Prelim. heat transfer coefficient"), wxDefaultPosition, wxDefaultSize, 0);
	m_static_text_coeff->Wrap(-1);
	fgSizer3->Add(m_static_text_coeff, 0, wxALL, 5);

	m_choice_coefficient = new wxChoice(this, CHOICE_K_ID, wxDefaultPosition, wxDefaultSize, m_choice_coefficients, 0);
	m_choice_coefficient->SetSelection(0);
	fgSizer3->Add(m_choice_coefficient, 0, wxALL, 5);

	m_static_text_area = new wxStaticText(this, wxID_ANY, wxT("Required area"), wxDefaultPosition, wxDefaultSize, 0);
	m_static_text_area->Wrap(-1);
	fgSizer3->Add(m_static_text_area, 0, wxALL, 5);

	m_text_area = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxBORDER_SIMPLE);
	fgSizer3->Add(m_text_area, 0, wxALL, 5);

	bSizer8->Add(fgSizer3, 1, wxEXPAND|wxLEFT|wxTOP, 16);
	m_panel4 = new DrafterPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL);
	bSizer8->Add(m_panel4, 1, wxEXPAND | wxALL, 5);

	bSizer7->Add(bSizer8, 0, wxEXPAND, 5);
	m_panel6 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL);
	bSizer7->Add(m_panel6, 1, wxEXPAND | wxALL, 5);

	last_K = -1;
	this->SetSizer(bSizer7);
	this->Layout();
}

BalancePanel::~BalancePanel()
{ }

// Recalculate and refresh heat balance values
void BalancePanel::UpdateResultValues()
{
    InputData &data = InputData::GetInstance();
    HeatBalance &balance = HeatBalance::GetInstance();
    balance.Calculate();

    // Heat flow
    m_text_heat_flow->Clear();
    m_text_heat_flow->SetValue(wxString::Format("%.1f", balance.GetHeatFlow()));
    m_text_heat_flow->AppendText(_(" J"));

    // Unknown value
    FlowUnknownValue unknown = data.flow_1.GetUnknownValue();
    m_text_result->Clear();
    if(unknown!=UNKN_NONE)
    {
        if(unknown==UNKN_T_IN)
        {
            m_text_result->SetValue(wxString::Format("%.1f", data.flow_1.GetInletTemperature()));
            m_text_result->AppendText(_(" deg.C"));
        }
        else if(unknown==UNKN_T_OUT)
        {
            m_text_result->SetValue(wxString::Format("%.1f", data.flow_1.GetOutletTemperature()));
            m_text_result->AppendText(_(" deg.C"));
        }
        else if(unknown==UNKN_RATE)
        {
            m_text_result->SetValue(wxString::Format("%.1f", data.flow_1.GetFlowRate()));
            m_text_result->AppendText(_(" kg/sec"));
        }
        else
        {
            m_text_result->SetValue("err1");
        }
    }
    else
    {
        unknown = data.flow_2.GetUnknownValue();
        if(unknown==UNKN_T_IN)
        {
            m_text_result->SetValue(wxString::Format("%.1f", data.flow_2.GetInletTemperature()));
            m_text_result->AppendText(_(" deg.C"));
        }
        else if(unknown==UNKN_T_OUT)
        {
            m_text_result->SetValue(wxString::Format("%.1f", data.flow_2.GetOutletTemperature()));
            m_text_result->AppendText(_(" deg.C"));
        }
        else if(unknown==UNKN_RATE)
        {
            m_text_result->SetValue(wxString::Format("%.1f", data.flow_2.GetFlowRate()));
            m_text_result->AppendText(_(" kg/sec"));
        }
        else
        {
            m_text_result->SetValue("err2");
        }
    }

    m_text_t_diff->Clear();
    m_text_t_diff->SetValue(wxString::Format("%.1f", balance.GetTemperatureDifference()));

    // Substance type
    m_text_subst_type_1->Clear();
    m_text_subst_type_1->SetValue(Substance::GetTypeNameFor(data.flow_1.GetSubstance().type));
    m_text_subst_type_2->Clear();
    m_text_subst_type_2->SetValue(Substance::GetTypeNameFor(data.flow_2.GetSubstance().type));

    // Preliminary heat transfer coefficient selection
    m_coeff_matrix.SetIsForcedFlow(m_choice_flow_type->GetSelection()==0);
    m_coeff_matrix.SetSubstance(data.flow_1.GetSubstance(), data.flow_2.GetSubstance());
    m_choice_coefficient->Clear();
    double k_min = m_coeff_matrix.GetHeatTransferCoefficientMin();
    double k_max = m_coeff_matrix.GetHeatTransferCoefficientMax();
    double delta = (k_max-k_min)/HT_COEFF_DEVIDED_PARTS;
    wxString str_value;
    while(k_min<=k_max)
    {
        str_value.Clear();
        str_value<<k_min;
        m_choice_coefficient->Append(str_value);
        k_min += delta;
    }

    double real_value;
    m_choice_coefficient->SetSelection(0);  // default value
    for(int i=0; i<m_choice_coefficient->GetCount(); i++)
    {
        if(!m_choice_coefficient->GetString(i).ToDouble(&real_value))
            continue;
        // Keep last value
        if(last_K==real_value)
        {
            m_choice_coefficient->SetSelection(i);
            break;
        }
    }
    // Assign preliminary heat transfer coefficient if not assigned for first time coefficient changed
    if(m_choice_coefficient->GetString(m_choice_coefficient->GetSelection()).ToDouble(&real_value))
        balance.SetPrelimHeatTransferCoefficient(real_value);
    // Required heat transfer area
    balance.CalculateRequiredArea();
    m_text_area->Clear();
    m_text_area->AppendText(wxString::Format("%.1f", balance.GetRequiredArea()));
}

void BalancePanel::OnFLowTypeCHanged(wxCommandEvent &event)
{
    UpdateResultValues();
}

void BalancePanel::OnCoeffSelectionChanged(wxCommandEvent &event)
{
    double real_value;
    HeatBalance &balance = HeatBalance::GetInstance();
    int selection = m_choice_coefficient->GetSelection();
    if(m_choice_coefficient->GetString(selection).ToDouble(&real_value))
    {
        last_K = real_value;
        balance.SetPrelimHeatTransferCoefficient(real_value);
    }
    UpdateResultValues();
}



