#ifndef INCLUDE_CANVAS_H
#define INCLUDE_CANVAS_H

#include <wx/wx.h>
#include <wx/glcanvas.h>

class MainFrame;

class MyGLCanvas : public wxGLCanvas 
{
public:
    explicit MyGLCanvas(wxWindow* parent_);

    void setRotation(float angel_);
    void setVisibility(bool visible_);
    void InitializeButton(const wxString& buttonPath);

    ~MyGLCanvas() override;

private:
    wxWindow* _parent;
    wxGLContext _context;
    GLuint _buttonTexture = 0;
    bool _buttonIntialized = false;

    int _buttonX = 50,
        _buttonY = 450,
        _buttonWidth     = 96,
        _buttonHeight    = 96;

    float _rotation = 0;
    bool _showRectangle = true;

    // void populateVertex();
    void _initialSetup();
    void _setupFrame();
    void _buttonInitialSetup();
    void _drawTriangle(const int& x_, const int& y_);
    void _drawCircle(const int& cx_, const int& cy_, const int& r_, const int& num_segments_ = 50);
    void _drawRectangle(const int& x_, const int& y_);

    void _loadButton(const wxString& path_);
    void _drawButton();

    void OnPaint(wxPaintEvent&);
    void OnResize(wxSizeEvent&);
    void OnButtonClick(wxMouseEvent& event);

    // DECLARE_EVENT_TABLE();

};

#endif // !INCLUDE_CANVAS_H
