#ifndef INPUT_GRID_PROPS_H_INCLUDED
#define INPUT_GRID_PROPS_H_INCLUDED

#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/property.h>
#include "../../calc/substance.h"
#include "../dialogues/dlgsubstance.h"

// The property contains selected substance
// Property value matches to substance name
class wxPropertySubstance: public wxPGProperty
{
    public:
        // Default constructor
        wxPropertySubstance() { }

        // All arguments of this ctor must have a default value -
        // use wxPG_LABEL for label and name
        wxPropertySubstance(wxWindow *parent,
                    const wxString& label = wxPG_LABEL,
                    const wxString& name = wxPG_LABEL,
                    const wxString& value = wxEmptyString)
                : wxPGProperty(label, name), m_id(wxNewId()), parent_grid(parent)
        {
            m_value = value;
        }

        virtual ~wxPropertySubstance() { }

        const wxPGEditor* DoGetEditorClass() const
        {
            // Determines editor used by property.
            // You can replace 'TextCtrl' below with any of these
            // builtin-in property editor identifiers: Choice, ComboBox,
            // TextCtrlAndButton, ChoiceAndButton, CheckBox, SpinCtrl,
            // DatePickerCtrl.
            return wxPGEditor_TextCtrlAndButton;
        }

        virtual wxString ValueToString(wxVariant& value,
                                        int arg_flags) const
        {
            return substance.name;
        }

        virtual bool StringToValue(wxVariant& variant, const wxString& text, int arg_flags)
        {
            substance.name = text;
            return true;
        }

        // Handles button-click event
        // Calls dialogue to choose a substance
        bool OnEvent(wxPropertyGrid *prop_grid, wxWindow *wnd_primary, wxEvent &event)
        {
            if(event.GetEventType()!=wxEVT_BUTTON)
                return false;

            DlgSubstance *dlg = new DlgSubstance(parent_grid);
            dlg->ShowModal();

            if(dlg->HasSubstanceSelected())
                substance = dlg->GetSelectedSubstance();

            delete dlg;

            // Event to handle outside (in parent grid)
            wxPostEvent(parent_grid, wxCommandEvent(wxEVT_PG_CHANGED, m_id));
            return true;
        }

        const Substance& GetSubstance(void) const
        {
            return substance;
        }

        int GetId(void) const
        {
            return m_id;
        }

    protected:

    private:
        int m_id;
        Substance substance;
        wxWindow *parent_grid;

};


#endif // INPUT_GRID_PROPS_H_INCLUDED
