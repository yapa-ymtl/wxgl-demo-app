#include "../include/mainfram.h"


MainFrame::MainFrame(const wxString& title_)
    : wxFrame(nullptr, wxID_ANY, title_) 
{
    canvas = new MyGLCanvas(this);
    sidePanel = new SidePanel(this);

    wxBoxSizer* hSizer = new wxBoxSizer(wxHORIZONTAL);
    hSizer->Add(canvas, 1, wxEXPAND);
    hSizer->Add(sidePanel, 0, wxEXPAND);

    sidePanel->Hide();

    SetSizer(hSizer);
    Layout();
}

void MainFrame::toggleSidePanel()
{
    sidePanel->Show(!sidePanel->IsShown());
    Layout();
}
