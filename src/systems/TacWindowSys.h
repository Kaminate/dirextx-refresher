#pragma once

#include "window/TacWindow.h"
#include "systems/TacSystem.h"
#include <memory>

namespace Tac
{
  class App;
  class WindowSys : public Sys
  {
  public:
    WindowSys(App * core, std::shared_ptr<Window> wind);
    void Update(float dt) override;
  private:
    std::shared_ptr<Window> mWind;
  };
}
