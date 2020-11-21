#ifndef EVENTS_H_INCLUDED
#define EVENTS_H_INCLUDED

#include <wx/event.h>

class EventInputUpdated;
wxDECLARE_EVENT(wxINPUT_UPDATED, EventInputUpdated);

// The event occurs when input data is being updated
// The event is used to notify an observer-class (main frame)
class EventInputUpdated: public wxCommandEvent
{
    public:
        EventInputUpdated(wxEventType commandType = wxINPUT_UPDATED, int id = 0)
                    :  wxCommandEvent(commandType, id)
        { }

        EventInputUpdated(const EventInputUpdated& event)
                    :  wxCommandEvent(event)
        {
            SetEventType(wxINPUT_UPDATED);
        }

        wxEvent* Clone() const {return new EventInputUpdated(*this);}

};

#endif // EVENTS_H_INCLUDED
