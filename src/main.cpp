#pragma warning( disable : 4005 ) // dx stuff

#include "util/TacException.h"
#include "application/TacApp.h"
#include "window/TacWindowsWindow.h"
#include "systems/TacWindowSys.h"
#include "systems/TacGraphicsSys.h"

int WINAPI wWinMain( 
  HINSTANCE hInst, 
  HINSTANCE hPrevInstance, 
  LPWSTR lpCmdLine, 
  int nCmdShow )
{
  hPrevInstance;
  lpCmdLine;

  using namespace Tac;
  try
  {
    std::shared_ptr<App> core(new App());
    App * heart = core.get();

    WindowsWindow * wind = new WindowsWindow(
      "dxrefresher", 
      hInst, 
      nCmdShow, 
      800,
      600);

    std::shared_ptr<Window> SPwind(wind);
    std::shared_ptr<Renderer> renderman(new Renderer(wind));
    std::shared_ptr<Sys> graphicsSystem(new GraphicsSys(heart, renderman));
    std::shared_ptr<Sys> windowSystem(new WindowSys(heart, SPwind));
    core->AddSys(graphicsSystem);
    core->AddSys(windowSystem);

    

    core->Run();
  }
  catch (const Exception & e)
  {
    e.what();
    OutputDebugString(e.what());
    fprintf(stderr, "%p", e.what());
    MessageBox(nullptr, e.what(), nullptr, MB_OK);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}