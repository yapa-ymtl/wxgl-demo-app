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

    virtual ~SidePanel();
private:
    wxSlider* slider;
    wxCheckBox* checkBox;
    int rotation = 0;

    void OnSliderChange(wxCommandEvent& event);
wxDECLARE_EVENT_TABLE();
};

#endif // !INCLUDE_SIDEPANEL_H
