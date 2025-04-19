#ifndef INCLUDE_CANVAS_H
#define INCLUDE_CANVAS_H

#include <wx/wx.h>
#include <wx/glcanvas.h>

class MyGLCanvas : public wxGLCanvas 
{
public:
    MyGLCanvas(wxWindow* parent_)
        : wxGLCanvas(parent_, wxID_ANY, nullptr)
        , context(this) 
    {
        Bind(wxEVT_PAINT, &MyGLCanvas::OnPaint, this);
        Bind(wxEVT_SIZE, &MyGLCanvas::OnResize, this);
    }

private:
    // struct vertex {
    //     float x, y, z;
    //
    // };
    wxGLContext context;

    void populateVertex();

    void initialSetup();
    void drawTriangle(const float& x_, const float& y_);
    void drawCircle(const float& cx, const float& cy, const float& r, const int& num_segments = 50);
    void drawRectangle(const float& x_, const float& y_);

    void OnPaint(wxPaintEvent&);
    void OnResize(wxSizeEvent&);

};

#endif // !INCLUDE_CANVAS_H
