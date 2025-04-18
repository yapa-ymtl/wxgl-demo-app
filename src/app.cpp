#include "../include/app.h"
#include "../include/mainfram.h"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    MainFrame* newFrame = new MainFrame("Main Window");
    newFrame->Show();

    return true;
}
