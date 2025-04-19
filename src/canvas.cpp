#include "../include/canvas.h"


void MyGLCanvas::OnPaint(wxPaintEvent&)
{
    wxPaintDC dc(this);
    SetCurrent(context);


    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    SwapBuffers();
}

void MyGLCanvas::OnResize(wxSizeEvent&)
{
    Refresh();
}
