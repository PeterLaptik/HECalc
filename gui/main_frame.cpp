#include "main_frame.h"

#define TEST

// Default size of the panel in proportion of screen
static const float FRAME_SCREEN_PROPORTION = 0.8;

// Default proportion for the input panel
static const float FRAME_INPUT_PROPORTION = 0.3;

// Assign menu ids
int MainFrame::ID_TEST_CASE_1 = wxNewId();


wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_SIZE(MainFrame::OnResizeFrame)
    EVT_COMMAND(wxID_ANY, wxINPUT_UPDATED, MainFrame::OnInputDataChanged)
    EVT_MENU(wxID_ANY, MainFrame::InitTestData)
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
	m_mgr.AddPane(input_panel, wxAuiPaneInfo().Left().Caption(_("Input")).CloseButton(false)
               .Dock().Resizable().FloatingSize(wxDefaultSize)
               .MinSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_X)*FRAME_SCREEN_PROPORTION*FRAME_INPUT_PROPORTION, -1));

	auinotebook = new wxAuiNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	m_mgr.AddPane(auinotebook, wxAuiPaneInfo().Center().CloseButton(false).Dock().Resizable().FloatingSize(wxDefaultSize));

	// Notebook panes
	balance_panel = new BalancePanel(this);
	auinotebook->AddPage(balance_panel, wxT("Balance"), false, wxNullBitmap);

	drafter_panel = new NotePanelDrafter(this);
	auinotebook->AddPage(drafter_panel, wxT("View"), false, wxNullBitmap);

    // Create menus
    menu = new wxMenuBar();
    menu_file = new wxMenu();
    menu_view = new wxMenu();
    menu_help = new wxMenu();
    // Insert items
    menu->Append(menu_view, _("Test"));
    menu_view->Append(ID_TEST_CASE_1, _("Test 1"));
	SetMenuBar(menu);

	m_mgr.Update();
	this->SetSize(wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_X)*FRAME_SCREEN_PROPORTION,
                      wxSystemSettings::GetMetric(wxSYS_SCREEN_Y)*FRAME_SCREEN_PROPORTION));
	this->Centre(wxBOTH);
	// Restore aui-child minimum size value
	m_mgr.GetPane(input_panel).MinSize(-1, -1);
}

MainFrame::~MainFrame()
{
	m_mgr.UnInit();
}


void MainFrame::OnInputDataChanged(wxCommandEvent &event)
{
    drafter_panel->Refresh();
    balance_panel->Refresh();
    balance_panel->UpdateResultValues();
}

void MainFrame::OnResizeFrame(wxSizeEvent &event)
{
    drafter_panel->Refresh();
    balance_panel->Refresh();
}

void MainFrame::ShowAllNotebookPanels(wxCommandEvent &event)
{
    drafter_panel->Show();
}

// Assign test data for input panel
#ifdef TEST
void MainFrame::InitTestData(wxCommandEvent &event)
{
    int id = event.GetId();
    if(id==ID_TEST_CASE_1)
        input_panel->SetTestData(1);

}
#endif // TEST
