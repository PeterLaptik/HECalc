#include "wxapp.h"
#include "gui/main_frame.h"

wxIMPLEMENT_APP(HEApp);

bool HEApp::OnInit()
{
    MainFrame *frame = new MainFrame(0);
    frame->Show(true);
    return true;
}
