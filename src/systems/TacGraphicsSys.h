#pragma once

#include <memory>
#include "graphics/graphics.h"
#include "systems/TacSystem.h"

namespace Tac
{
  class App;
  class GraphicsSys : public Sys
  {
  public:
    GraphicsSys(App * core, std::shared_ptr<Renderer> renderer);
    void Update(float dt) override;
  private:
    std::shared_ptr<Renderer> mRenderer;
  };
}
