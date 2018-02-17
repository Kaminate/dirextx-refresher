#pragma once
#include <d3dx11.h>
#include <memory>
#include "graphics/shader.h"
#include "graphics/vertex.h"

namespace Tac
{
  class WindowsWindow;
  
  class Renderer
  {
  public:
    Renderer(const WindowsWindow * wind);
    ~Renderer();
    
    void Render();

  private:
    void SetupSwapChain(const WindowsWindow * wind);
    void SetupRenderTargetView();
    void SetupViewport(float w, float h);

    IDXGISwapChain * mSwapChain;
    ID3D11Device * mDevice;
    ID3D11DeviceContext * mImmediateContext;
    ID3D11RenderTargetView * mBackbufferView;

    std::shared_ptr<Shader> mShader;
    std::shared_ptr<VertexBuffer> mVerts;
  };

}
