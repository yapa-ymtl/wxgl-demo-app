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
    wxGLContext context;

    void OnPaint(wxPaintEvent&);
    void OnResize(wxSizeEvent&);
};

#endif // !INCLUDE_CANVAS_H
