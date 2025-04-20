#include "../include/mainfram.h"

// wxBEGIN_EVENT_TABLE(SidePanel, wxPanel)
//     EVT_SLIDER(wxID_ANY, MainFrame::OnSliderChange)
// wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title_)
    : wxFrame(nullptr, wxID_ANY, title_)
    , canvas(new MyGLCanvas(this))
    , sidePanel(new SidePanel(this))
{
    // canvas = new MyGLCanvas(this);
    // sidePanel = new SidePanel(this);

    wxBoxSizer* hSizer = new wxBoxSizer(wxHORIZONTAL);
    hSizer->Add(canvas, 1, wxEXPAND);
    hSizer->Add(sidePanel, 0, wxEXPAND);

    // wxLogMessage("MianFrame constructor");
    // if (this->canvas == nullptr) wxLogMessage("canvas empty");
    // else wxLogMessage("canvas not empty");

    sidePanel->Hide();

    sidePanel->GetSlider()->Bind(wxEVT_SLIDER, &MainFrame::OnSliderChange, this);
    sidePanel->GetCheckBox()->Bind(wxEVT_CHECKBOX, &MainFrame::OnCheckChange, this);

    SetSizer(hSizer);
    Layout();
}

void MainFrame::toggleSidePanel()
{
    sidePanel->Show(!sidePanel->IsShown());
    // wxLogMessage("toggle layout");
    Layout();
}

void MainFrame::OnSliderChange(wxCommandEvent& event)
{
    if (this->canvas == nullptr) {
        wxLogMessage("canvas empty");
    }
    int rotation = event.GetInt();
    // wxLogMessage("Rotation MainFrame set to %d", event.GetInt());
    canvas->setRotation(static_cast<float>(rotation));
}

void MainFrame::OnCheckChange(wxCommandEvent& event)
{
    bool show = event.IsChecked();
    canvas->setVisibility(show);
}
