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
    void OnSliderChange(wxCommandEvent& event);
    void OnCheckChange(wxCommandEvent& event);
private:
    float _rotation = 0;
    MyGLCanvas* canvas = nullptr;
    SidePanel* sidePanel = nullptr;

    // DECLARE_EVENT_TABLE()
};

#endif // !INCLUDE_MAINFRAME_H
