#pragma once
#include "application/TacResource.h"
#include <d3d11.h>
#include <vector>
namespace Tac
{
  class InputLayoutCreator
  {
  public:
    InputLayoutCreator(ID3D11Device * device);
    void AddSemantic(
      const char * stringliteral, 
      DXGI_FORMAT datatype);

    ID3D11InputLayout * Create(ID3DBlob * vsBlob);

  private:
    ID3D11Device * mDevice;
    std::vector<D3D11_INPUT_ELEMENT_DESC> mDescriptors;
  };

  class Shader : public Resource
  {
  public:
    Shader(ID3D11Device * device, const std::string & filepath);
    ~Shader();
    void Clear();
    virtual void OnReload() override;
    ID3D11PixelShader * GetPS();
    ID3D11VertexShader * GetVS();
    ID3D11InputLayout * GetLayout();
    
  private:
    void CompileShaderFromFile( 
      const std::string & filename,
      const std::string & entrypoint,
      const std::string & shadermodel,
      ID3DBlob** ppBlobOut );

    ID3D11Device * mDevice;
    ID3D11VertexShader * mVS;
    ID3D11PixelShader * mPS;
    ID3D11InputLayout * mLayout;
    InputLayoutCreator mLayoutCreator;
  };
}