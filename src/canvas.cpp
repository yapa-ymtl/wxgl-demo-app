#include "../include/canvas.h"

void MyGLCanvas::initialSetup()
{
    wxPaintDC dc(this);
    SetCurrent(context);


    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 2D Projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, GetSize().x, GetSize().y, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void MyGLCanvas::drawTriangle(const float& x_, const float& y_)
{
    // Triangle
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(x_, y_);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f((x_ + 50), (y_ + 100));
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f((x_ + 100), y_);
    glEnd();
}

void MyGLCanvas::drawCircle(const float& cx, const float& cy, const float& r, const int& num_segments)
{
    
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void MyGLCanvas::drawRectangle(const float& x_, const float& y_)
{
    // Example: Drawing a green rectangle
    glColor3f(0.0f, 1.0f, 0.0f); // Green

        glBegin(GL_QUADS);
        glVertex2f(x_, y_); // Top-left
        glVertex2f((x_ + 150), y_); // Top-right
        glVertex2f((x_+150), (y_+100)); // Bottom-right
        glVertex2f(x_, (y_+100)); // Bottom-left
    glEnd();

}

void MyGLCanvas::OnPaint(wxPaintEvent&)
{
    initialSetup();

    drawTriangle(100, 100);
    drawTriangle(0, 0);
    drawTriangle(200, 200);

    drawRectangle(300,300);

    drawCircle(600, 450, 100);
    SwapBuffers();
}


void MyGLCanvas::OnResize(wxSizeEvent&)
{
    Refresh();
}
