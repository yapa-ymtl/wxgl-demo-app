#include "../include/canvas.h"
#include "../include/mainfram.h"


MyGLCanvas::MyGLCanvas(wxWindow* parent_)
    : wxGLCanvas(parent_, wxID_ANY, nullptr)
    , _parent(parent_)
    , _context(this) 
{
    Bind(wxEVT_PAINT, &MyGLCanvas::OnPaint, this);
    Bind(wxEVT_SIZE, &MyGLCanvas::OnResize, this);
    Bind(wxEVT_LEFT_DOWN, &MyGLCanvas::OnButtonClick, this);
    // Bind(wxEVT_LEFT_DOWN, &MyGLCanvas::OnMouseClick, this);
    _initialSetup();
}

void MyGLCanvas::setRotation(float angel_)
{
    _rotation = angel_; 
    Refresh();
}

void MyGLCanvas::setVisibility(bool visible_)
{
    _showRectangle = visible_;
    Refresh();
}

void MyGLCanvas::InitializeButton(const wxString& buttonPath)
{
    if (!_buttonIntialized) {
        _loadButton(buttonPath);
        _buttonIntialized = true;
    }
}

void MyGLCanvas::_initialSetup() 
{
    SetCurrent(_context);
    
    // One-time OpenGL setup
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void MyGLCanvas::_setupFrame()
{
    wxPaintDC dc(this);
    SetCurrent(_context);

    wxSize size = GetSize();

    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 2D Projection setup
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, size.x, size.y, 0, -1, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Apply rotation transform
    glTranslatef(size.x/2.0f, size.y/2.0f, 0.0f);
    glRotatef(_rotation, 0.0f, 0.0f, 1.0f);
    glTranslatef(-size.x/2.0f, -size.y/2.0f, 0.0f);
}

void MyGLCanvas::_drawTriangle(const int& x_, const int& y_)
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

void MyGLCanvas::_drawCircle(const int& cx_, const int& cy_, const int& r_, const int& num_segments_)
{
    
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    glVertex2f(cx_, cy_);
    for (int i = 0; i <= num_segments_; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments_);
        float x = r_ * cosf(theta);
        float y = r_ * sinf(theta);
        glVertex2f(cx_ + x, cy_ + y);
    }
    glEnd();
}

void MyGLCanvas::_drawRectangle(const int& x_, const int& y_)
{
    if (!_showRectangle) return;
    glColor3f(1.0f, 1.0f, 1.0f); // Green

        glBegin(GL_QUADS);
        glVertex2f(x_, y_); // Top-left
        glVertex2f((x_ + 150), y_); // Top-right
        glVertex2f((x_+150), (y_+100)); // Bottom-right
        glVertex2f(x_, (y_+100)); // Bottom-left
    glEnd();

}

void MyGLCanvas::_loadButton(const wxString& path_)
{
    // Delete existing texture if any
    if (_buttonTexture != 0) {
        glDeleteTextures(1, &_buttonTexture);
        _buttonTexture = 0;
    }

    wxImage image(path_, wxBITMAP_TYPE_PNG);
    if (!image.IsOk()) {
        wxLogError("Failed to load image: %s", path_);
        return;
    }

    if (!image.HasAlpha()) {
        image.InitAlpha();
    }

    int width = image.GetWidth();
    int height = image.GetHeight();
    unsigned char* rgb = image.GetData();
    unsigned char* alpha = image.GetAlpha();

    if (!rgb) {
        wxLogError("Failed to get image data");
        return;
    }

    // Create RGBA buffer
    std::vector<unsigned char> rgba(width * height * 4);
    for (int i = 0; i < width * height; ++i) {
        rgba[i * 4 + 0] = rgb[i * 3 + 0];
        rgba[i * 4 + 1] = rgb[i * 3 + 1];
        rgba[i * 4 + 2] = rgb[i * 3 + 2];
        rgba[i * 4 + 3] = alpha ? alpha[i] : 255;
    }

    // Make sure we're in the correct OpenGL context
    SetCurrent(_context);

    // Generate texture
    glGenTextures(1, &_buttonTexture);
    if (_buttonTexture == 0) {
        wxLogError("Failed to generate texture");
        return;
    }

    // Check for OpenGL errors
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        wxLogError("OpenGL error before texture creation: %d", err);
        return;
    }

    glBindTexture(GL_TEXTURE_2D, _buttonTexture);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, rgba.data());

    // Check if texture was created successfully
    err = glGetError();
    if (err != GL_NO_ERROR) {
        wxLogError("Failed to create texture: OpenGL error %d", err);
        glDeleteTextures(1, &_buttonTexture);
        _buttonTexture = 0;
        return;
    }

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0);

    // Verify texture creation
    GLint width_check = 0;
    glBindTexture(GL_TEXTURE_2D, _buttonTexture);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width_check);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (width_check != width) {
        wxLogError("Texture verification failed. Expected width: %d, Got: %d", width, width_check);
        glDeleteTextures(1, &_buttonTexture);
        _buttonTexture = 0;
        return;
    }

}


void MyGLCanvas::_drawButton()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _buttonTexture);
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
    glTexCoord2f(0, 0); glVertex2i(_buttonX, _buttonY);
    glTexCoord2f(1, 0); glVertex2i(_buttonX + _buttonWidth, _buttonY);
    glTexCoord2f(1, 1); glVertex2i(_buttonX + _buttonWidth, _buttonY + _buttonHeight);
    glTexCoord2f(0, 1); glVertex2i(_buttonX, _buttonY + _buttonHeight);
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
    _setupFrame();

    _drawTriangle(100, 100);
    _drawTriangle(0, 0);
    _drawTriangle(200, 200);

    _drawRectangle(300,300);

    _drawCircle(600, 450, 100);
     
    if (_buttonIntialized) _drawButton();
    SwapBuffers();
}


void MyGLCanvas::OnResize(wxSizeEvent&)
{
    Refresh();
}

void MyGLCanvas::OnButtonClick(wxMouseEvent& event)
{
    int mouseX = event.GetX();
    int mouseY = event.GetY();


    if (mouseX >= _buttonX && mouseX <= (_buttonX + _buttonWidth) &&
        mouseY >= _buttonY && mouseY <= (_buttonY + _buttonHeight)) {
        
        wxFrame* frame = wxDynamicCast(wxGetTopLevelParent(this), wxFrame);
        if (frame) {
            auto myFrame = dynamic_cast<MainFrame*>(frame);
            if (myFrame) {
                myFrame->toggleSidePanel();
            }
        }
    }
}

MyGLCanvas::~MyGLCanvas() 
{
    if (_buttonTexture != 0) glDeleteTextures(1, &_buttonTexture);
}
