#include "systems/TacGraphicsSys.h"
#include "application/TacApp.h"
namespace Tac
{
  GraphicsSys::GraphicsSys( App * core, std::shared_ptr<Renderer> wind )
    : Sys(core)
    , mRenderer(wind)
  {

  }

  void GraphicsSys::Update( float dt )
  {
    mRenderer->Render();
  }

}