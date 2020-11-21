#ifndef DRAFTERPANEL_H
#define DRAFTERPANEL_H

#include <wx/panel.h>
#include <wx/dcclient.h>
#include <wx/toplevel.h>

// Panel for output drafting of heat exchanging scheme
class DrafterPanel: public wxPanel
{
	public:

		DrafterPanel(wxWindow* parent,
                    wxWindowID id = wxID_ANY,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize,
                    long style = wxTAB_TRAVERSAL,
                    const wxString& name = "jjj");

		virtual ~DrafterPanel();

		// Get appropriate colors for hot and cold flows
		wxColor GetUpperColour(void);
		wxColor GetBottomColour(void);
		wxBrush GetUpperBrush(void);
		wxBrush GetBottomBrush(void);
		// Listener interface
		virtual void RefreshCurrentData(void) {this->Refresh();}

	protected:

	private:
	    void OnPaint(wxPaintEvent &event);
	    void DrawArrow(const wxPaintDC &dc, int x1, int x2, int y1, int y2);
	    // Check hotter flow for appropriate colours assigning
	    inline bool IsUpperFlowHotter(void);

		//DECLARE_EVENT_TABLE()
};

#endif
