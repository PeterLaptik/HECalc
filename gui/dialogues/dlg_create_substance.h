#ifndef DLG_CREATE_SUBSTANCE_H_INCLUDED
#define DLG_CREATE_SUBSTANCE_H_INCLUDED

#include "../../calc/substance.h"
#include <wx/dialog.h>

class wxGrid;
class wxChoice;
class wxButton;

// Dialogue for new substance creating
class DlgCreateSubstance : public wxDialog
{
    public:
		DlgCreateSubstance( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Create substance"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 399,349 ), long style = wxDEFAULT_DIALOG_STYLE );
		virtual ~DlgCreateSubstance();

		Substance GetCreatedSubstance(void) const
		{
		    return substance;
		}

		bool IsSubstanceCreated(void) const
		{
		    return substance_created;
		}

	protected:
	    void OnChoice(wxCommandEvent &event);
	    void OnAddSubstance(wxCommandEvent &event);  // dummy return value
	    void OnCancel(wxCommandEvent &event);

		wxGrid* m_grid;
		wxChoice* m_choice;
		wxButton* m_button_add;
		wxButton* m_button_cancel;

    private:
        void ShowMessage(const wxString &msg);
        bool CheckResult(const Substance &result);
        void RefreshTable(void);
        void OnClickOk(wxCommandEvent &event);
        void OnClickCancel(wxCommandEvent &event);
        bool substance_created;
        Substance substance;

    DECLARE_EVENT_TABLE()
};

#endif // DLG_CREATE_SUBSTANCE_H_INCLUDED
