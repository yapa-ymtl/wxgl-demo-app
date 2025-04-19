#include "../include/mainfram.h"


MainFrame::MainFrame(const wxString& title_)
    : wxFrame(nullptr, wxID_ANY, title_) 
{
    canvas = new MyGLCanvas(this);
}
