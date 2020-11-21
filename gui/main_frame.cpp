#include "main_frame.h"

// Custom event to notify high-level window on input data updating
// See event.h
//wxDEFINE_EVENT(wxINPUT_UPDATED, EventInputUpdated);

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_SIZE(MainFrame::OnResizeFrame)
    EVT_COMMAND(wxID_ANY, wxINPUT_UPDATED, MainFrame::OnInputDataChanged)
wxEND_EVENT_TABLE()


MainFrame::MainFrame(wxWindow* parent,
                     wxWindowID id,
                     const wxString& title,
                     const wxPoint& pos,
                     const wxSize& size,
                     long style)
            : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);

	input_panel = new InputPanel(this);
	m_mgr.AddPane(input_panel, wxAuiPaneInfo().Left().Caption(_("Input")).CloseButton(false).Dock().Resizable().FloatingSize(wxDefaultSize));

	auinotebook = new wxAuiNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE);
	m_mgr.AddPane(auinotebook, wxAuiPaneInfo().Center().CloseButton(false).Dock().Resizable().FloatingSize(wxDefaultSize));

	// Notebook panes
	drafter_panel = new NotePanelDrafter(this);
	auinotebook->AddPage(drafter_panel, wxT("View"), false, wxNullBitmap);

	m_mgr.Update();
	this->Centre(wxBOTH);
}

MainFrame::~MainFrame()
{
	m_mgr.UnInit();
}


void MainFrame::OnInputDataChanged(wxCommandEvent &event)
{
    drafter_panel->Refresh();
}

void MainFrame::OnResizeFrame(wxSizeEvent &event)
{
    drafter_panel->Refresh();
}
