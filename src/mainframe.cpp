#include "../include/mainfram.h"


MainFrame::MainFrame(const wxString& title_)
    : wxFrame(nullptr, wxID_ANY, title_)
    , _canvas(new MyGLCanvas(this))
    , _sidePanel(new SidePanel(this))
{

    wxBoxSizer* hSizer = new wxBoxSizer(wxHORIZONTAL);
    hSizer->Add(_canvas, 1, wxEXPAND);
    hSizer->Add(_sidePanel, 0, wxEXPAND);

    _sidePanel->Hide();

    _sidePanel->getSlider()->Bind(wxEVT_SLIDER, &MainFrame::onSliderChange, this);
    _sidePanel->getCheckBox()->Bind(wxEVT_CHECKBOX, &MainFrame::onCheckChange, this);

    SetSizer(hSizer);
    Layout();
}

void MainFrame::toggleSidePanel()
{
    _sidePanel->Show(!_sidePanel->IsShown());
    // wxLogMessage("toggle layout");
    Layout();
}

void MainFrame::onSliderChange(wxCommandEvent& event_)
{
    if (this->_canvas == nullptr) {
        wxLogMessage("canvas empty");
    }
    int rotation = event_.GetInt();
    // wxLogMessage("Rotation MainFrame set to %d", event.GetInt());
    _canvas->setRotation(static_cast<float>(rotation));
}

void MainFrame::onCheckChange(wxCommandEvent& event_)
{
    bool show = event_.IsChecked();
    _canvas->setVisibility(show);
}
