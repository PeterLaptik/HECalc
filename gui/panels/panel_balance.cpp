#include "panel_balance.h"

BalancePanel::BalancePanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxPanel(parent, id, pos, size, style, name)
{
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer(wxHORIZONTAL);

	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer(6, 2, 0, 0);
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

	m_static_text_coeff = new wxStaticText(this, wxID_ANY, wxT("Heat transfer coefficient"), wxDefaultPosition, wxDefaultSize, 0);
	m_static_text_coeff->Wrap(-1);
	fgSizer3->Add(m_static_text_coeff, 0, wxALL, 5);

	wxArrayString m_choice_coefficientChoices;
	m_choice_coefficient = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_coefficientChoices, 0);
	m_choice_coefficient->SetSelection(0);
	fgSizer3->Add(m_choice_coefficient, 0, wxALL, 5);

	m_static_text_ares = new wxStaticText(this, wxID_ANY, wxT("Required area"), wxDefaultPosition, wxDefaultSize, 0);
	m_static_text_ares->Wrap(-1);
	fgSizer3->Add(m_static_text_ares, 0, wxALL, 5);

	m_text_area = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxBORDER_SIMPLE);
	fgSizer3->Add(m_text_area, 0, wxALL, 5);


	bSizer8->Add(fgSizer3, 1, wxEXPAND|wxLEFT|wxTOP, 16);

	m_panel4 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL);
	bSizer8->Add(m_panel4, 1, wxEXPAND | wxALL, 5);


	bSizer7->Add(bSizer8, 1, wxEXPAND, 5);

	m_panel6 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxTAB_TRAVERSAL);
	bSizer7->Add(m_panel6, 1, wxEXPAND | wxALL, 5);


	this->SetSizer(bSizer7);
	this->Layout();
}

BalancePanel::~BalancePanel()
{
}
