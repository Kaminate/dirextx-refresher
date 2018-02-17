#include "graphics/graphics.h"
#include "window/TacWindowsWindow.h"
#include "util/TacException.h"
#include "util/TacDirectXError.h"
#include <string>
namespace Tac
{
  Renderer::Renderer(const WindowsWindow * wind)
  {
    SetupSwapChain(wind);
    SetupRenderTargetView();
    SetupViewport(
      (float)wind->GetWidth(), 
      (float)wind->GetHeight());

    mShader = std::shared_ptr<Shader>(
      new Shader(mDevice, "resources/shaders/shader.fx"));

    mImmediateContext->IASetInputLayout(mShader->GetLayout());

    std::vector<Vertex> vec;
    std::vector<DirectX::XMFLOAT3> pos;
    std::vector<DirectX::XMFLOAT4> col;
    pos.push_back(DirectX::XMFLOAT3 ( 0.0f,  0.5f, 0.5f));
    pos.push_back(DirectX::XMFLOAT3 ( 0.5f, -0.5f, 0.5f));
    pos.push_back(DirectX::XMFLOAT3 (-0.5f, -0.5f, 0.5f));
    col.push_back(DirectX::XMFLOAT4 (1,0,0,1));
    col.push_back(DirectX::XMFLOAT4 (0,1,0,1));
    col.push_back(DirectX::XMFLOAT4 (0,0,1,1));
    for (unsigned i = 0; i < 3; ++i)
      vec.push_back(Vertex(pos[i], col[i]));

    
    mVerts = std::shared_ptr<VertexBuffer>(
      new VertexBuffer(mDevice, vec));

    // set vertex buff
    unsigned stride = sizeof(Vertex);
    unsigned offset = 0;
    ID3D11Buffer * buf = mVerts->GetBuffer();
    mImmediateContext->IASetVertexBuffers(0, 1, &buf, &stride, &offset);

    mImmediateContext->IASetPrimitiveTopology(
      D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  }

  Renderer::~Renderer()
  {
    mSwapChain->Release();
    mBackbufferView->Release();
    mImmediateContext->Release();
    mDevice->Release();
  }

  void Renderer::SetupSwapChain(const WindowsWindow * wind)
  {
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory( &sd, sizeof(sd) );
    sd.BufferCount = 1;
    sd.BufferDesc.Width = wind->GetWidth();
    sd.BufferDesc.Height = wind->GetHeight();
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = wind->GetHwnd();
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;

    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif


    HRESULT hr = D3D11CreateDeviceAndSwapChain( 
      NULL, 
      D3D_DRIVER_TYPE_HARDWARE, 
      NULL,
      createDeviceFlags,
      &featureLevel,
      1,
      D3D11_SDK_VERSION, 
      &sd,
      &mSwapChain, 
      &mDevice,
      nullptr, 
      &mImmediateContext);
    if (FAILED(hr))
      ThrowException(GetDirectXError(hr));
  }

  void Renderer::SetupRenderTargetView()
  {
    HRESULT hr;

    // get the backbuffer of the swap chain...
    ID3D11Texture2D * backbufferTexture;

    hr = mSwapChain->GetBuffer(
      0, 
      __uuidof(ID3D11Texture2D), 
      (LPVOID*)&backbufferTexture);

    if (FAILED(hr))
      ThrowException(GetDirectXError(hr));

    // ...so that we can bind it as a render target
    hr = mDevice->CreateRenderTargetView(
      backbufferTexture, nullptr, &mBackbufferView);

    // destroy texture object used to access the backbuffer
    backbufferTexture->Release();

    // OM stands for the OutputMerger stage of the pipeline
    mImmediateContext->OMSetRenderTargets(
      1, &mBackbufferView, nullptr);
  }

  void Renderer::SetupViewport( float w, float h )
  {
    D3D11_VIEWPORT vp;
    vp.Width = w;
    vp.Height = h;
    vp.MinDepth = 0;
    vp.MaxDepth = 1;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    // RS stands for the Rasterizer Stage of the pipeline
    mImmediateContext->RSSetViewports(1, &vp);
  }

  void Renderer::Render()
  {
    float clearcolor[4] = { 0.0f, 0.125f, 0.6f, 1.0f };
    mImmediateContext->ClearRenderTargetView(mBackbufferView, clearcolor);
    mImmediateContext->VSSetShader(mShader->GetVS(), nullptr, 0);
    mImmediateContext->PSSetShader(mShader->GetPS(), nullptr, 0);
    mImmediateContext->Draw(3,0);
    mSwapChain->Present(0,0);

  }

} // Tac
