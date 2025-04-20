#include "../include/mainfram.h"


MainFrame::MainFrame(const wxString& title_)
    : wxFrame(nullptr, wxID_ANY, title_) 
{
    canvas = new MyGLCanvas(this);
    // sidePanel = new SidePanel(this);
    // sidePanel->Hide();
}
