#include "dlgsubstance.h"
#include <wx/intl.h>
#include <wx/string.h>

wxBEGIN_EVENT_TABLE(DlgSubstance,wxDialog)
    EVT_BUTTON(wxID_ANY, DlgSubstance::OnButtonClick)
wxEND_EVENT_TABLE()

DlgSubstance::DlgSubstance(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
{
    id_button_ok = wxNewId();
    id_button_cancel = wxNewId();
    has_selected = false;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);

	// Sizers
	box_sizer = new wxBoxSizer(wxVERTICAL);
	box_sizer_h = new wxBoxSizer(wxHORIZONTAL);

	// Buttons
	button_ok = new wxButton(this, id_button_ok, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0);
	button_cancel = new wxButton(this, id_button_cancel, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0);
	box_sizer_h->Add(button_ok, 0, wxALIGN_BOTTOM|wxALIGN_RIGHT|wxALL, 5);
	box_sizer_h->Add(button_cancel, 0, wxALIGN_BOTTOM|wxALIGN_RIGHT|wxALL, 5);

	// Window
	SetSizer(box_sizer);
	box_sizer->Fit(this);
	box_sizer->SetSizeHints(this);
	substance_list = new SubstanceList(this, wxID_ANY,wxDefaultPosition);
	box_sizer->Add(substance_list, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	box_sizer->Add(box_sizer_h, 1, wxALIGN_RIGHT, 5);
	SetSizer(box_sizer);
	box_sizer->Fit(this);
	box_sizer->SetSizeHints(this);
}

DlgSubstance::~DlgSubstance()
{ }

bool DlgSubstance::HasSubstanceSelected(void) const
{
    return has_selected;
}

const Substance& DlgSubstance::GetSelectedSubstance() const
{
    return selected_substance;
}

void DlgSubstance::OnButtonClick(wxCommandEvent &event)
{
    int id = event.GetId();

    // Find selected substance
    long index = -1;
    while ((index = substance_list->GetNextItem(index,
        wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND)
    {
        if(index!=-1)
            break;
    }
    // Change has-selected flag to true on OK-button clicked
    if((id==id_button_ok)&&(index!=-1))
    {
        has_selected = true;
        selected_substance = substance_list->GetSubstance(index);
    }
    this->Destroy();
}
