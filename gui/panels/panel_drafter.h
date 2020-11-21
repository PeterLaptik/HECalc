#ifndef PANEL_DRAFTER_H_INCLUDED
#define PANEL_DRAFTER_H_INCLUDED

#include "../controls/drafter.h"
#include <wx/panel.h>
#include <wx/sizer.h>

// Notebook panel for keeping drafter
class NotePanelDrafter : public wxPanel
{
    public:
		NotePanelDrafter(wxWindow* parent,
                wxWindowID id = wxID_ANY,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxSize(500,300),
                long style = wxTAB_TRAVERSAL,
                const wxString& name = wxEmptyString);

		virtual ~NotePanelDrafter();

    protected:
        DrafterPanel *drafter;

	private:

};

#endif // PANEL_DRAFTER_H_INCLUDED
