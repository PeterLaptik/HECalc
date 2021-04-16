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
#include <wx/menu.h>

#include "panels/panel_input.h"
#include "panels/panel_results.h"
#include "panels/panel_balance.h"
#include "events/events.h"

// Main frame
// Contains input panel and notebook with result panels
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
	    // Menu commands

	    // Test commands
	    void ShowAllNotebookPanels(wxCommandEvent &event);
	    void InitTestData(wxCommandEvent &event);

	    // Panel for input data
	    InputPanel *input_panel;
	    // Result notebook
	    wxAuiNotebook *auinotebook;
	    // Notebook panel for balance results
	    BalancePanel *balance_panel;
	    // Notebook panel to output results
	    ResultPanel *results_panel;

	    // Menu
	    wxMenuBar *menu;
	    wxMenu *menu_file;
	    wxMenu *menu_help;
        wxMenu *menu_view;

        // Menu ids
        static int ID_TEST_CASE_1;

	private:
        wxDECLARE_EVENT_TABLE();
};

#endif // MAIN_FRAME_H_INCLUDED
