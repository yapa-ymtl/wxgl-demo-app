#ifndef INCLUDE_SIDEPANEL_H
#define INCLUDE_SIDEPANEL_H

#include <wx/panel.h>
#include <wx/slider.h>
#include <wx/checkbox.h>

class SidePanel : public wxPanel {
public:
    SidePanel(wxWindow* parent_);

    wxSlider* getSlider() const { return _slider; }
    wxCheckBox* getCheckBox() const { return _checkBox; }

    virtual ~SidePanel();
private:
    wxSlider* _slider;
    wxCheckBox* _checkBox;
    int rotation = 0;

    void _onSliderChange(wxCommandEvent& event_);
wxDECLARE_EVENT_TABLE();
};

#endif // !INCLUDE_SIDEPANEL_H
