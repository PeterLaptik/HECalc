#ifndef MAIN_FRAME_H_INCLUDED
#define MAIN_FRAME_H_INCLUDED

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/frame.h>
#include <wx/aui/aui.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>

#include "panels/panel_input.h"
#include "panels/panel_drafter.h"
#include "events/events.h"

class MainFrame : public wxFrame
{
    public:
		MainFrame(wxWindow* parent,
                    wxWindowID id = wxID_ANY,
                    const wxString& title = wxEmptyString,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxSize(800, 600),
                    long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL);
		~MainFrame();

		wxAuiManager m_mgr;

	protected:
	    void OnInputDataChanged(wxCommandEvent &event);
	    void OnResizeFrame(wxSizeEvent &event);

	    InputPanel *input_panel;
	    NotePanelDrafter *drafter_panel;
	    wxAuiNotebook *auinotebook;

	private:
        wxDECLARE_EVENT_TABLE();
};

#endif // MAIN_FRAME_H_INCLUDED
