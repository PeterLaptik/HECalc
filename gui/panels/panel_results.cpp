#include "panel_results.h"
#include "../controls/equipment_grid.h"
#include "wx/richtext/richtextctrl.h"
#include "../../calc/output_data.h"
#include "../../calc/heatexchanger.h"

ResultPanel::ResultPanel(wxWindow* parent, wxWindowID id,
                       const wxPoint& pos,
                       const wxSize& size,
                       long style,
                       const wxString& name)
            : wxPanel(parent, id, pos, size, style, name)
{
	wxBoxSizer* box_sizer;
	box_sizer = new wxBoxSizer(wxHORIZONTAL);
	output = new wxRichTextCtrl(this);
	box_sizer->Add(output, 1, wxEXPAND, 5);
	equipment_grid = new EquipmentGrid(this, wxID_ANY);
	box_sizer->Add(equipment_grid, 1, wxEXPAND, 5);
	this->SetSizer(box_sizer);
	this->Layout();
}

ResultPanel::~ResultPanel()
{ }

void ResultPanel::UpdateResults()
{
    wxString line;
    OutputData& results = OutputData::GetInstance();
    HeatExchanger *he = results.GetEquipmentUnit();
    he->Calculate();

    output->Clear();
    output->AppendText(_("Results:"));
    line<<"Re(innner) = "<<he->GetReInner();
    output->AddParagraph(line);
    line.Clear();
    line<<"Pr(innner) = "<<he->GetPrInner();
    output->AddParagraph(line);
}

#ifdef TEST
    void ResultPanel::SetTestData(int test_num)
    {
        switch(test_num)
        {
            case 1:
                equipment_grid->TestCase_1();
                break;
        }
    }
#endif // TEST
