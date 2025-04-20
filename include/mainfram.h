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

private:
    MyGLCanvas* canvas;
    SidePanel* sidePanel;

};

#endif // !INCLUDE_MAINFRAME_H
