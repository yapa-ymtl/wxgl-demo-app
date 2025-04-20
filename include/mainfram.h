#ifndef INCLUDE_MAINFRAME_H
#define INCLUDE_MAINFRAME_H

#include "canvas.h"
#include "sidepanel.h"
#include <wx/wx.h>
#include <wx/glcanvas.h>

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title_);
    
    void toggleSidePanel();
    void onSliderChange(wxCommandEvent& event_);
    void onCheckChange(wxCommandEvent& event_);

private:
    float _rotation = 0;
    MyGLCanvas* _canvas = nullptr;
    SidePanel* _sidePanel = nullptr;

    // DECLARE_EVENT_TABLE()
};

#endif // !INCLUDE_MAINFRAME_H
