#include "../include/canvas.h"
#include "../include/mainfram.h"


MyGLCanvas::MyGLCanvas(wxWindow* parent_)
    : wxGLCanvas(parent_, wxID_ANY, nullptr)
    , _parent(parent_)
    , context(this) 
{
    Bind(wxEVT_PAINT, &MyGLCanvas::OnPaint, this);
    Bind(wxEVT_SIZE, &MyGLCanvas::OnResize, this);
    Bind(wxEVT_LEFT_DOWN, &MyGLCanvas::OnButtonClick, this);
    // Bind(wxEVT_LEFT_DOWN, &MyGLCanvas::OnMouseClick, this);
}

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

void MyGLCanvas::drawTriangle(const int& x_, const int& y_)
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

void MyGLCanvas::drawCircle(const int& cx, const int& cy, const int& r, const int& num_segments)
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

void MyGLCanvas::drawRectangle(const int& x_, const int& y_)
{
    // Example: Drawing a green rectangle
    glColor3f(1.0f, 1.0f, 1.0f); // Green

        glBegin(GL_QUADS);
        glVertex2f(x_, y_); // Top-left
        glVertex2f((x_ + 150), y_); // Top-right
        glVertex2f((x_+150), (y_+100)); // Bottom-right
        glVertex2f(x_, (y_+100)); // Bottom-left
    glEnd();

}


void MyGLCanvas::loadButton(const wxString& path_) {
    wxImage image(path_, wxBITMAP_TYPE_PNG);
    if (!image.IsOk()) {
        wxLogError("Failed to load image: %s", path_);
        return;
    }

    // Ensure image has alpha channel
    if (!image.HasAlpha()) {
        image.InitAlpha();
    }

    int width = image.GetWidth();
    int height = image.GetHeight();

    // Get raw RGB and alpha data
    unsigned char* rgb = image.GetData();
    unsigned char* alpha = image.GetAlpha();

    // Combine RGB and Alpha into RGBA buffer
    std::vector<unsigned char> rgba(width * height * 4);
    for (int i = 0; i < width * height; ++i) {
        rgba[i * 4 + 0] = rgb[i * 3 + 0];            // Red
        rgba[i * 4 + 1] = rgb[i * 3 + 1];            // Green
        rgba[i * 4 + 2] = rgb[i * 3 + 2];            // Blue
        rgba[i * 4 + 3] = alpha ? alpha[i] : 255;    // Alpha
    }

    // Create OpenGL texture
    glGenTextures(1, &buttonTexture);
    glBindTexture(GL_TEXTURE_2D, buttonTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, rgba.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    // wxLogMessage("Image loaded and texture created: %dx%d", width, height);
}

void MyGLCanvas::drawButton()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, buttonTexture);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int w, h;
    GetClientSize(&w, &h);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2i(buttonX, buttonY);
    glTexCoord2f(1, 0); glVertex2i(buttonX + buttonWidth, buttonY);
    glTexCoord2f(1, 1); glVertex2i(buttonX + buttonWidth, buttonY + buttonHeight);
    glTexCoord2f(0, 1); glVertex2i(buttonX, buttonY + buttonHeight);
    glEnd();

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}


void MyGLCanvas::OnPaint(wxPaintEvent&)
{
    initialSetup();
    const wxString imagePath = wxGetHomeDir() + "/Projects/upwork/Deeprey/Assesment/demoApp/assets/button3.png";
    loadButton(imagePath);

    drawTriangle(100, 100);
    drawTriangle(0, 0);
    drawTriangle(200, 200);

    drawRectangle(300,300);

    drawCircle(600, 450, 100);
     
    drawButton();
    SwapBuffers();
}


void MyGLCanvas::OnResize(wxSizeEvent&)
{
    Refresh();
}

void MyGLCanvas::OnButtonClick(wxMouseEvent& event) {
    int mouseX = event.GetX();
    int mouseY = event.GetY();

    // int height = GetSize().GetHeight();
    // int flippedY = height - mouseY;

    if (mouseX >= buttonX && mouseX <= (buttonX + buttonWidth) &&
        mouseY >= buttonY && mouseY <= (buttonY + buttonHeight)) {
        
        wxFrame* frame = wxDynamicCast(wxGetTopLevelParent(this), wxFrame);
        if (frame) {
            auto myFrame = dynamic_cast<MainFrame*>(frame);
            if (myFrame) {
                myFrame->toggleSidePanel();
            }
        }
        // Do something here
    }
}

MyGLCanvas::~MyGLCanvas() 
{
    if (buttonTexture != 0) glDeleteTextures(1, &buttonTexture);
}
