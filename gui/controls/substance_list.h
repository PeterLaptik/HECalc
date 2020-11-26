#ifndef SUBSTANCE_LIST_H_INCLUDED
#define SUBSTANCE_LIST_H_INCLUDED

#include "../../calc/substance.h"
#include <wx/listctrl.h>
#include <vector>

// List of substances read from text file
class SubstanceList: public wxListCtrl
{
    public:
        SubstanceList(wxWindow *parent,
                wxWindowID id = wxID_ANY,
                const wxPoint &pos=wxDefaultPosition,
                const wxSize &size=wxDefaultSize,
                long style=wxLC_REPORT|wxLC_VIRTUAL/*|wxLC_SINGLE_SEL*/,
                const wxValidator &validator=wxDefaultValidator,
                const wxString &name=wxListCtrlNameStr);

        virtual ~SubstanceList();

        Substance GetSubstance(int index) const;

        // Clear list and reread substances from base
        void RefreshList(void);


    protected:


    private:
        void AppendColumns(void);
        void ReadSubstances(void);
        void CreateDefaultBaseFile(const wxString &path);
        wxString OnGetItemText(long item, long column) const;

        std::vector<Substance> m_substances;
};

#endif // SUBSTANCE_LIST_H_INCLUDED
