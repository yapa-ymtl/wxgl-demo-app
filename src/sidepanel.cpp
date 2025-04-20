#include "../include/sidepanel.h"
#include <wx/sizer.h>

SidePanel::SidePanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY) {
    wxBoxSizer* vSizer = new wxBoxSizer(wxVERTICAL);

    slider = new wxSlider(this, wxID_ANY, 0, 0, 100);
    checkBox = new wxCheckBox(this, wxID_ANY, "Toggle Shape");

    vSizer->Add(slider, 0, wxALL | wxEXPAND, 10);
    vSizer->Add(checkBox, 0, wxALL, 10);

    SetSizer(vSizer);
}
