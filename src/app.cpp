#include "../include/app.h"
#include "../include/mainfram.h"
#include <memory>

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    // std::unique_ptr<MainFrame> newFrame = std::make_unique<MainFrame>("Main Window");
    MainFrame* newFrame = new MainFrame("Main Window");
    newFrame->Show();
    newFrame->SetClientSize(800,600);
    newFrame->Center();

    return true;
}
