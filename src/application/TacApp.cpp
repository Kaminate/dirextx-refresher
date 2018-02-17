#include "application/TacApp.h"
namespace Tac
{
  App::App()
    : mRunning(true)
  {

  }

  void App::Run()
  {
    while (mRunning)
    {
      for (auto cursys : mSystems)
      {
        cursys->Update(1/60.0f);
      }
    }
  }

  void App::Stop()
  {
    mRunning = false;
  }

  void App::AddSys( std::shared_ptr<Sys> system )
  {
    mSystems.push_back(system);
  }

} // Tac
