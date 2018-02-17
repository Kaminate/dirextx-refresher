#pragma once

namespace Tac
{
  class App;
  class Sys
  {
  public:
    Sys(App * core);
    virtual void Update(float dt) = 0;
  protected:
    App * GetApp();
  private:
    App * mApp;
  };
}
