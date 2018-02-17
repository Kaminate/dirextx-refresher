#pragma once
#include <memory>
#include <vector>
#include "systems/TacSystem.h"
namespace Tac
{
  class App
  {
  public:
    App();
    void AddSys(std::shared_ptr<Sys> system);
    void Run();
    void Stop();
  private:
    bool mRunning;
    std::vector<std::shared_ptr<Sys> > mSystems;
  };
}