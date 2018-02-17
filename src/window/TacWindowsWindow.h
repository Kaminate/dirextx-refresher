#pragma once
#include "window/TacWindow.h"
#include <windows.h>
#include <string>
namespace Tac
{
  class WindowsWindow : public Window
  {
  public:
    
    WindowsWindow(
      const std::string & windowTitle,
      HINSTANCE hInstance, 
      int nCmdShow, 
      int w, 
      int h);
    ~WindowsWindow();
    void PeekMessages(bool & shouldQuit) override;
    static LRESULT CALLBACK WindowsProc(
      HWND hWnd, 
      UINT message, 
      WPARAM wParam, 
      LPARAM lParam );
    HWND GetHwnd()const;
    int GetWidth()const;
    int GetHeight()const;
  private:
    void RegisterClass(
      const std::string & className, 
      HINSTANCE hInstance);
    void CreateWind(
      const std::string & windowTitle,
      const std::string & windowClass,
      int width, 
      int height);
    HINSTANCE mHInst;
    HWND mHWnd;
    int mWidth;
    int mHeight;
  };
}