#ifndef INCLUDE_SIDEPANEL_H
#define INCLUDE_SIDEPANEL_H

#include <wx/panel.h>
#include <wx/slider.h>
#include <wx/checkbox.h>

class SidePanel : public wxPanel {
public:
    SidePanel(wxWindow* parent);

    wxSlider* GetSlider() const { return slider; }
    wxCheckBox* GetCheckBox() const { return checkBox; }

private:
    wxSlider* slider;
    wxCheckBox* checkBox;
};

#endif // !INCLUDE_SIDEPANEL_H
