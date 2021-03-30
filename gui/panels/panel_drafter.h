#ifndef PANEL_DRAFTER_H_INCLUDED
#define PANEL_DRAFTER_H_INCLUDED

#include <wx/panel.h>
#include <wx/sizer.h>

#define TEST

class DrafterPanel;
class EquipmentGrid;
class wxRichTextCtrl;

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

		void UpdateResults(void);

		#ifdef TEST
            void SetTestData(int test_num);
		#endif // TEST

    protected:
        wxRichTextCtrl *output;
        EquipmentGrid *equipment_grid;

	private:

};

#endif // PANEL_DRAFTER_H_INCLUDED
