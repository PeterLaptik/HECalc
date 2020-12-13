#ifndef PANEL_INPUT_H_INCLUDED
#define PANEL_INPUT_H_INCLUDED

#include "../controls/input_grid.h"
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/aui/aui.h>

#define TEST

// Main input panel
// Contains input grid
class InputPanel : public wxPanel
{
    public:
		InputPanel(wxWindow* parent,
                wxWindowID id = wxID_ANY,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxSize(500,300),
                long style = wxTAB_TRAVERSAL,
                const wxString& name = wxEmptyString);

		virtual ~InputPanel();

		#ifdef TEST
            void SetTestData(int test_num);
		#endif // TEST

    protected:
        HEInputGrid *input_grid;

	private:

};

#endif // PANEL_INPUT_H_INCLUDED
