#ifndef WXAPP_H_INCLUDED
#define WXAPP_H_INCLUDED

#include <wx/app.h>

class HEApp: public wxApp
{
    public:
        virtual bool OnInit(void);
};

#endif // WXAPP_H_INCLUDED
