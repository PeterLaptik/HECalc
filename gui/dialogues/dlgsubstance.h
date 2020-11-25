#ifndef DLGSUBSTANCE_H
#define DLGSUBSTANCE_H

#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include "../../calc/substance.h"
#include "../controls/substance_list.h"

// Dialogue for substance selecting from substance-list
class DlgSubstance: public wxDialog
{
	public:

		DlgSubstance(wxWindow* parent,
                wxWindowID id=wxID_ANY,
                const wxPoint& pos=wxDefaultPosition,
                const wxSize& size=wxDefaultSize);
		virtual ~DlgSubstance();

		// Getters for result info
		bool HasSubstanceSelected(void) const;
		const Substance& GetSelectedSubstance(void) const;

	protected:
	    void OnButtonClick(wxCommandEvent &event);

	    SubstanceList *substance_list;
	    Substance selected_substance;
	    bool has_selected;

	    wxBoxSizer *box_sizer;
	    wxBoxSizer *box_sizer_h;
	    wxButton *button_ok;
	    wxButton *button_cancel;
	    wxButton *create_substance;

	    int id_button_ok;
	    int id_button_cancel;
	    int id_button_create_substance;
	    int id_box_sizer;
	    int id_box_sizer_h;

	private:
		DECLARE_EVENT_TABLE()
};

#endif
