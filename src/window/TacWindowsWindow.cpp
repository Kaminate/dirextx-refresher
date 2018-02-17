#include "window/TacWindowsWindow.h"
#include "resources/resource.h"
#include "util/TacWindowsError.h"
#include "util/TacException.h"
#include <iostream>
#include <tchar.h>
namespace Tac
{
  LRESULT CALLBACK WindowsWindow::WindowsProc(
    HWND hWnd, 
    UINT message, 
    WPARAM wParam, 
    LPARAM lParam )
  {
    PAINTSTRUCT ps;
    HDC hdc;

    switch( message )
    {
    case WM_PAINT:
      hdc = BeginPaint( hWnd, &ps );
      EndPaint( hWnd, &ps );
      break;

    case WM_DESTROY:
      PostQuitMessage( 0 );
      break;

    default:
      return DefWindowProc( hWnd, message, wParam, lParam );
    }

    return 0;
  }

  WindowsWindow::WindowsWindow(
    const std::string & windowTitle,
    HINSTANCE hInstance, 
    int nCmdShow, 
    int w, 
    int h)
    : mWidth(w)
    , mHeight(h)
    , mHInst(hInstance)
  {
    std::string className("OurWindowClass");
    RegisterClass(className, hInstance);
    CreateWind(windowTitle, className, w, h);
    ShowWindow( mHWnd, nCmdShow );
  }

  WindowsWindow::~WindowsWindow()
  {
    DestroyWindow(mHWnd);
  }

  void WindowsWindow::PeekMessages(bool & shouldQuit)
  {
    // Main message loop
    MSG msg = {0};
    while (PeekMessage(&msg, nullptr, 0,0,PM_REMOVE))
    {
      TranslateMessage( &msg );
      DispatchMessage( &msg );
    }
    shouldQuit = msg.message == WM_QUIT ? true : false;
  }

  HWND WindowsWindow::GetHwnd()const
  {
    return mHWnd;
  }

  int WindowsWindow::GetWidth() const
  {
    return mWidth;
  }

  int WindowsWindow::GetHeight()const
  {
    return mHeight;
  }

  void WindowsWindow::RegisterClass( 
    const std::string & className, 
    HINSTANCE hInstance)
  {
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof( WNDCLASSEX );
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WindowsProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;

    HICON icon = LoadIcon( hInstance, ( LPCTSTR )IDI_ICON1);
    if (!icon)
      ThrowException(GetLastWindowsError());

    wcex.hIcon = icon;
    wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
    wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = className.c_str();
    wcex.hIconSm = icon;
    if( !RegisterClassEx( &wcex ) )
      ThrowException("Failed to register window class");
  }

  void WindowsWindow::CreateWind( 
    const std::string & windowTitle, 
    const std::string & windowClass, 
    int width, 
    int height )
  {
    // Create window
    RECT rc = { 0, 0, mWidth, mHeight};
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
    DWORD style;
    int stylesize = sizeof(style);
    bool borderless = false;
    style = borderless ? WS_POPUP : WS_OVERLAPPEDWINDOW;
    mHWnd = CreateWindow(
      windowClass.c_str(), //classname
      windowTitle.c_str(), //windowname
      style, // dwstyle
      200, 200, // x, y
      rc.right - rc.left, // w
      rc.bottom - rc.top, // h
      NULL, // hwndparent
      NULL, // hmenu
      mHInst,
      NULL ); // lpparam

    if( !mHWnd)
      ThrowException(GetLastWindowsError());
  }

}
