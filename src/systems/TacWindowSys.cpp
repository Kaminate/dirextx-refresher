#include "systems/TacWindowSys.h"
#include "application/TacApp.h"
namespace Tac
{
  WindowSys::WindowSys( App * core, std::shared_ptr<Window> wind )
    : Sys(core)
    , mWind(wind)
  {

  }

  void WindowSys::Update( float dt )
  {
    bool shouldquit;
    mWind->PeekMessages(shouldquit);
    if (shouldquit)
      GetApp()->Stop();
  }

}