#include <wx/log.h>
#include <wx/sizer.h>

#include "../include/sidepanel.h"

wxBEGIN_EVENT_TABLE(SidePanel, wxPanel)
    // EVT_SLIDER(wxID_ANY, SidePanel::_onSliderChange)
wxEND_EVENT_TABLE()

SidePanel::SidePanel(wxWindow* parent_)
    : wxPanel(parent_, wxID_ANY)
    ,_slider(new wxSlider(this, wxID_ANY, 0, 0, 100))
    ,_checkBox(new wxCheckBox(this, wxID_ANY, "Show Rectangle"))
{
    // Bind(wxEVT_SLIDER, &SidePanel::_onSliderChange, this);
    wxBoxSizer* vSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* sliderLabel = new wxStaticText(this, wxID_ANY, "Rotate Objects");
    _slider->SetMin(0);
    _slider->SetMax(360);
    _checkBox->SetValue(true);
    vSizer->Add(sliderLabel, 0, wxLEFT | wxRIGHT | wxTOP, 10);
    vSizer->Add(_slider, 0, wxALL | wxEXPAND, 10);
    vSizer->Add(_checkBox, 0, wxALL, 10);

    SetSizer(vSizer);
}

void SidePanel::_onSliderChange(wxCommandEvent& event_)
{
    rotation = _slider->GetValue();
}

SidePanel::~SidePanel()
{
    delete _slider;
    delete _checkBox;
}
