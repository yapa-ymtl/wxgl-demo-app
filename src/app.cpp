#include "../include/app.h"
#include "../include/mainfram.h"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    MainFrame* newFrame = new MainFrame("Main Window");
    newFrame->Show();
    newFrame->SetClientSize(800,600);
    newFrame->Center();

    return true;
}
