#include "panel_input.h"

InputPanel::InputPanel(wxWindow* parent, wxWindowID id,
                       const wxPoint& pos,
                       const wxSize& size,
                       long style,
                       const wxString& name)
            : wxPanel(parent, id, pos, size, style, name)
{
	wxBoxSizer* box_sizer;
	box_sizer = new wxBoxSizer(wxHORIZONTAL);
	input_grid = new HEInputGrid(this, wxID_ANY);
	box_sizer->Add(input_grid, 1, wxEXPAND, 5);
	this->SetSizer(box_sizer);
	this->Layout();
}

InputPanel::~InputPanel()
{ }


#ifdef TEST
    void InputPanel::SetTestData(int test_num)
    {
        switch(test_num)
        {
            case 1:
                input_grid->TestCase_1();
                break;
        }
    }
#endif // TEST
