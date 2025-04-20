#include "../include/sidepanel.h"
#include <wx/log.h>
#include <wx/sizer.h>

wxBEGIN_EVENT_TABLE(SidePanel, wxPanel)
    // EVT_SLIDER(wxID_ANY, SidePanel::OnSliderChange)
wxEND_EVENT_TABLE()

SidePanel::SidePanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY)
    ,slider(new wxSlider(this, wxID_ANY, 0, 0, 100))
    ,checkBox(new wxCheckBox(this, wxID_ANY, "Toggle Shape"))
{
    // Bind(wxEVT_SLIDER, &SidePanel::OnSliderChange, this);
    wxBoxSizer* vSizer = new wxBoxSizer(wxVERTICAL);

    slider->SetMin(0);
    slider->SetMax(360);
    checkBox->SetValue(true);
    vSizer->Add(slider, 0, wxALL | wxEXPAND, 10);
    vSizer->Add(checkBox, 0, wxALL, 10);

    SetSizer(vSizer);
}

void SidePanel::OnSliderChange(wxCommandEvent& event)
{
    rotation = slider->GetValue();
    // wxLogMessage("Rotation set to %d", rotation);
}

SidePanel::~SidePanel()
{
    delete slider;
    delete checkBox;
}
