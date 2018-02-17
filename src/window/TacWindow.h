#pragma once
namespace Tac
{
  class Window
  {
  public:
    virtual void PeekMessages(bool & shouldQuit) = 0;
  private:
  };
}