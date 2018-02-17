#include "systems/TacSystem.h"
namespace Tac
{

  Sys::Sys( App * core )
    : mApp(core)
  {

  }

  App * Sys::GetApp()
  {
    return mApp;
  }

}
