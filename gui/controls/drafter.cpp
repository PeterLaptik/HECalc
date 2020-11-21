#include "drafter.h"
#include <wx/dc.h>
#include <wx/intl.h>
#include <wx/string.h>
#include "../../calc/input_data.h"

const wxString UNIT_TEMP = " deg. C";
const wxString UNIT_FLOW = " kg/sec";


DrafterPanel::DrafterPanel(wxWindow* parent,
                           wxWindowID id,
                           const wxPoint& pos,
                           const wxSize& size,
                           long style,
                           const wxString& name)
{
	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("id"));
	Connect(wxEVT_PAINT, wxPaintEventHandler(DrafterPanel::OnPaint));
}

DrafterPanel::~DrafterPanel()
{ }


void DrafterPanel::OnPaint(wxPaintEvent& event)
{
    const float RECT_COEFF = 0.3;
    const float LINE_COEFF = 0.1;
    const int ARROW_WIDTH = 15;
    const int ARROW_HEIGHT = 5;
    const int SHIFT_PROPORTION = 4;

    InputData &data = InputData::GetInstance();
    int width, height;
    int x, y;
    wxPoint array_points[3];
    wxPen pen_main(*wxBLACK, 2);
    wxPen pen_upper(GetUpperColour());
    wxPen pen_bottom(GetBottomColour());
    wxPen pen_upper_dash(GetUpperColour(), 1, wxPENSTYLE_SHORT_DASH);
    wxPen pen_bottom_dash(GetBottomColour(), 1, wxPENSTYLE_SHORT_DASH);

    wxPaintDC dc(this);
    width = this->GetSize().x;
    height = this->GetSize().y;
    dc.Clear();

    // Draw rectangle
    x = width*RECT_COEFF;
    y = height*RECT_COEFF;
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.SetPen(pen_main);
    dc.DrawRectangle(x, y, width - 2*x, height - 2*y);

    // Draw red line (upper line)
    dc.SetPen(pen_upper);
    x = width*LINE_COEFF;
    y = height*LINE_COEFF;
    dc.DrawLine(x, height*RECT_COEFF + ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION),
                width*RECT_COEFF, height*RECT_COEFF + ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION));

    // Draw red arrow (upper line)
    dc.SetBrush(GetUpperBrush());
    array_points[0].x = width*LINE_COEFF;
    array_points[0].y = height*RECT_COEFF + ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION);
    array_points[1].x = array_points[2].x = width*LINE_COEFF + ARROW_WIDTH;
    array_points[1].y = height*RECT_COEFF + ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION) + ARROW_HEIGHT;
    array_points[2].x = width*LINE_COEFF + ARROW_WIDTH;
    array_points[2].y = height*RECT_COEFF + ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION) - ARROW_HEIGHT;
    dc.DrawPolygon(WXSIZEOF(array_points), array_points);

    // Draw red line (upper line)
    dc.DrawLine(width - x, height*RECT_COEFF + ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION),
                width - width*RECT_COEFF, height*RECT_COEFF + ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION));

    // Draw red arrow (upper)
    array_points[0].x = width - width*RECT_COEFF;
    array_points[0].y = height*RECT_COEFF + ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION);
    array_points[1].x = array_points[2].x = width - width*RECT_COEFF + ARROW_WIDTH;
    array_points[1].y = height*RECT_COEFF + ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION) + ARROW_HEIGHT;
    array_points[2].x = width - width*RECT_COEFF + ARROW_WIDTH;
    array_points[2].y = height*RECT_COEFF + ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION) - ARROW_HEIGHT;
    dc.DrawPolygon(WXSIZEOF(array_points), array_points);

    // Draw inner red line (upper)
    dc.SetPen(pen_upper_dash);
    dc.DrawLine(width - x, height*RECT_COEFF + ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION),
                width*RECT_COEFF, height*RECT_COEFF + ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION));

    // Draw blue line (bottom)
    dc.SetPen(pen_bottom);
    dc.DrawLine(x, height - height*RECT_COEFF - ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION),
                width*RECT_COEFF, height - height*RECT_COEFF - ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION));

    // Draw blue arrow (bottom)
    // with respect to chosen flows directions
    dc.SetBrush(GetBottomBrush());

    if(data.direction==FLOW_COUNTER_CURRENT)
    {
        array_points[0].x = width*RECT_COEFF;
        array_points[0].y = height - height*RECT_COEFF - ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION);
        array_points[1].x = array_points[2].x = width*RECT_COEFF - ARROW_WIDTH;
        array_points[1].y = height - height*RECT_COEFF - ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION) + ARROW_HEIGHT;
        array_points[2].x = width*RECT_COEFF - ARROW_WIDTH;
        array_points[2].y = height - height*RECT_COEFF - ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION) - ARROW_HEIGHT;
        dc.DrawPolygon(WXSIZEOF(array_points), array_points);
    }
    else
    {
        array_points[0].x = width*LINE_COEFF;
        array_points[0].y = height - height*RECT_COEFF - ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION);
        array_points[1].x = array_points[2].x = width*LINE_COEFF + ARROW_WIDTH;
        array_points[1].y = height - height*RECT_COEFF - ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION) + ARROW_HEIGHT;
        array_points[2].x = width*LINE_COEFF + ARROW_WIDTH;
        array_points[2].y = height - height*RECT_COEFF - ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION) - ARROW_HEIGHT;
        dc.DrawPolygon(WXSIZEOF(array_points), array_points);
    }


    // Draw blue line (bottom)
    dc.DrawLine(width - x, height - height*RECT_COEFF - ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION),
                width - width*RECT_COEFF, height - height*RECT_COEFF - ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION));

    // Draw blue arrow (bottom)
    // with respect to chosen flows directions
    if(data.direction==FLOW_COUNTER_CURRENT)
    {
        array_points[0].x = width - width*LINE_COEFF;
        array_points[0].y = height - height*RECT_COEFF - ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION);
        array_points[1].x = array_points[2].x = width - width*LINE_COEFF - ARROW_WIDTH;
        array_points[1].y = height - height*RECT_COEFF - ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION) + ARROW_HEIGHT;
        array_points[2].x = width - width*LINE_COEFF - ARROW_WIDTH;
        array_points[2].y = height - height*RECT_COEFF - ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION) - ARROW_HEIGHT;
        dc.DrawPolygon(WXSIZEOF(array_points), array_points);
    }
    else
    {
        array_points[0].x = width - width*RECT_COEFF;
        array_points[0].y = height - height*RECT_COEFF - ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION);
        array_points[1].x = array_points[2].x = width - width*RECT_COEFF + ARROW_WIDTH;
        array_points[1].y = height - height*RECT_COEFF - ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION) + ARROW_HEIGHT;
        array_points[2].x = width - width*RECT_COEFF + ARROW_WIDTH;
        array_points[2].y = height - height*RECT_COEFF - ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION) - ARROW_HEIGHT;
        dc.DrawPolygon(WXSIZEOF(array_points), array_points);
    }


    // Draw inner blue line (bottom)
    dc.SetPen(pen_bottom_dash);
    dc.DrawLine(width - x, height - height*RECT_COEFF - ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION),
                width*RECT_COEFF, height - height*RECT_COEFF - ((height - height*RECT_COEFF*2)/SHIFT_PROPORTION));

    // Write text
    // Temperatures
    dc.SetTextForeground(*wxBLACK);
    wxString text;
    text = wxT("T1e=");
    if(data.flow_1.GetUnknownValue()==UNKN_T_OUT)
        text<<"?";
    else
        text<<data.flow_1.GetOutletTemperature()<<UNIT_TEMP;

    dc.DrawText(text, width*LINE_COEFF,
                height*RECT_COEFF - dc.GetCharHeight() - ARROW_HEIGHT);

    text = wxT("T1s=");
    if(data.flow_1.GetUnknownValue()==UNKN_T_IN)
        text<<"?";
    else
        text<<data.flow_1.GetInletTemperature()<<UNIT_TEMP;

    dc.DrawText(text, width - width*LINE_COEFF - dc.GetCharWidth()*text.size(),
                height*RECT_COEFF - dc.GetCharHeight() - ARROW_HEIGHT);


    // Drafting temperature output according to flow directions
    // Exchange blue line arrows if it is needed
    if(data.direction==FLOW_COUNTER_CURRENT)
    {
        text = wxT("T2e=");
        if(data.flow_2.GetUnknownValue()==UNKN_T_OUT)
            text<<"?";
        else
            text<<data.flow_2.GetOutletTemperature()<<UNIT_TEMP;

        dc.DrawText(text, width - width*LINE_COEFF - dc.GetCharWidth()*text.size(),
                    height - height*RECT_COEFF + ARROW_HEIGHT);

        text = wxT("T2s=");
        if(data.flow_2.GetUnknownValue()==UNKN_T_IN)
            text<<"?";
        else
            text<<data.flow_2.GetInletTemperature()<<UNIT_TEMP;

        dc.DrawText(text, width*LINE_COEFF,
                    height - height*RECT_COEFF + ARROW_HEIGHT);
    }
    else
    {
        text = wxT("T2s=");
        if(data.flow_2.GetUnknownValue()==UNKN_T_IN)
            text<<"?";
        else
            text<<data.flow_2.GetInletTemperature()<<UNIT_TEMP;

        dc.DrawText(text, width - width*LINE_COEFF - dc.GetCharWidth()*text.size(),
                    height - height*RECT_COEFF + ARROW_HEIGHT);

        text = wxT("T2e=");
        if(data.flow_2.GetUnknownValue()==UNKN_T_OUT)
            text<<"?";
        else
            text<<data.flow_2.GetOutletTemperature()<<UNIT_TEMP;

        dc.DrawText(text, width*LINE_COEFF,
                    height - height*RECT_COEFF + ARROW_HEIGHT);
    }


    // Mass flows
    text = wxT("G1=");
    if(data.flow_1.GetUnknownValue()==UNKN_RATE)
        text<<"?";
    else
        text<<data.flow_1.GetFlowRate()<<UNIT_FLOW;

    dc.SetTextForeground(GetUpperColour());
    dc.DrawText(text, width/2 - dc.GetCharWidth()*text.size()/2, height*RECT_COEFF - 2*dc.GetCharHeight() - ARROW_HEIGHT);

    text = wxT("G2=");
    if(data.flow_2.GetUnknownValue()==UNKN_RATE)
        text<<"?";
    else
        text<<data.flow_2.GetFlowRate()<<UNIT_FLOW;

    dc.SetTextForeground(GetBottomColour());
    dc.DrawText(text, width/2 - dc.GetCharWidth()*text.size()/2, height - height*RECT_COEFF + dc.GetCharHeight() + ARROW_HEIGHT);
}

// Returns red if the upper line is hotter than the bottom one.
// Otherwise returns blue
wxColor DrafterPanel::GetUpperColour()
{
    if(IsUpperFlowHotter())
        return *wxRED;
    else
        return *wxBLUE;
}

// Returns red if the bottom line is hotter than the upper line.
// Otherwise returns red
wxColor DrafterPanel::GetBottomColour()
{
    if(IsUpperFlowHotter())
        return *wxBLUE;
    else
        return *wxRED;
}

// See comments above
wxBrush DrafterPanel::GetUpperBrush()
{
    if(IsUpperFlowHotter())
        return *wxRED_BRUSH;
    else
        return *wxBLUE_BRUSH;
}

// See comments above
wxBrush DrafterPanel::GetBottomBrush()
{
    if(IsUpperFlowHotter())
        return *wxBLUE_BRUSH;
    else
        return *wxRED_BRUSH;
}

// Returns is inlet temperature of the upper flow on the draft is hotter then the bottom one
// The method is used for choosing right flows colours
bool DrafterPanel::IsUpperFlowHotter()
{
    InputData &data = InputData::GetInstance();
    return data.flow_1.GetInletTemperature() > data.flow_2.GetInletTemperature();
}
