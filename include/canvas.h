#ifndef INCLUDE_CANVAS_H
#define INCLUDE_CANVAS_H

#include <wx/wx.h>
#include <wx/glcanvas.h>

class MainFrame;

class MyGLCanvas : public wxGLCanvas 
{
public:
    MyGLCanvas(wxWindow* parent_);
    void setRotation(float angel_);

    ~MyGLCanvas();

private:
    // struct vertex {
    //     float x, y, z;
    //
    // };

    wxWindow* _parent;
    wxGLContext context;
    GLuint buttonTexture = 0;
    int buttonX = 50,
        buttonY = 450,
        buttonWidth     = 96,
        buttonHeight    = 96;
    float _rotation = 0;

    void populateVertex();

    void initialSetup();
    void drawTriangle(const int& x_, const int& y_);
    void drawCircle(const int& cx, const int& cy, const int& r, const int& num_segments = 50);
    void drawRectangle(const int& x_, const int& y_);

    void loadButton(const wxString& path_);
    void drawButton();

    void OnPaint(wxPaintEvent&);
    void OnResize(wxSizeEvent&);
    void OnButtonClick(wxMouseEvent& event);

};

#endif // !INCLUDE_CANVAS_H
