#include "panel_drafter.h"

NotePanelDrafter::NotePanelDrafter(wxWindow* parent, wxWindowID id,
                       const wxPoint& pos,
                       const wxSize& size,
                       long style,
                       const wxString& name)
            : wxPanel(parent, id, pos, size, style, name)
{
	wxBoxSizer* box_sizer;
	box_sizer = new wxBoxSizer(wxHORIZONTAL);
	drafter = new DrafterPanel(this, wxID_ANY);
	box_sizer->Add(drafter, 1, wxEXPAND, 5);
	this->SetSizer(box_sizer);
	this->Layout();
}

NotePanelDrafter::~NotePanelDrafter()
{ }
