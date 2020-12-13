#ifndef PANEL_BALANCE_H_INCLUDED
#define PANEL_BALANCE_H_INCLUDED

#include "../../calc/coefficientmatrix.h"
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/choice.h>


class BalancePanel : public wxPanel
{
    public:
		BalancePanel(wxWindow* parent,
                    wxWindowID id = wxID_ANY,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxSize( 371,269 ),
                    long style = wxTAB_TRAVERSAL,
                    const wxString& name = wxEmptyString);

		~BalancePanel();

		void UpdateResultValues(void);


	protected:
	    void OnFLowTypeCHanged(wxCommandEvent &event);
	    void OnCoeffSelectionChanged(wxCommandEvent &event);

		wxStaticText* m_static_text_hf;
		wxTextCtrl* m_text_heat_flow;
		wxStaticText* m_static_text_result;
		wxTextCtrl* m_text_result;
		wxStaticText* m_static_text_subst_1;
		wxTextCtrl* m_text_subst_type_1;
		wxStaticText* m_static_text_subst_2;
		wxTextCtrl* m_text_subst_type_2;
		wxStaticText* m_static_text_t_diff;
		wxTextCtrl* m_text_t_diff;
		wxStaticText* m_static_text_flow;
		wxChoice* m_choice_flow_type;
		wxStaticText* m_static_text_coeff;
		wxChoice* m_choice_coefficient;
		wxStaticText* m_static_text_area;
		wxTextCtrl* m_text_area;
		wxPanel* m_panel4;
		wxPanel* m_panel6;

		wxArrayString m_flow_type;
		wxArrayString m_choice_coefficients;  // Mutable values. Depend on fluid types

    private:
        double last_K;
        CoefficientMatrix m_coeff_matrix;


    wxDECLARE_EVENT_TABLE();
};


#endif // PANEL_BALANCE_H_INCLUDED
