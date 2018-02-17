#include "graphics/shader.h"
#include "util/TacFileReader.h"
#include <util/TacException.h>
#include <util/TacDirectXError.h>
#include <d3dcompiler.h>
#include <d3dx11async.h>
#include <wrl/client.h>
namespace Tac
{
  Shader::Shader( ID3D11Device * device, const std::string & filepath )
    : Resource(filepath)
    , mLayoutCreator(device)
    , mVS(nullptr)
    , mDevice(device)
  {
    mLayoutCreator.AddSemantic("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
    mLayoutCreator.AddSemantic("COLOR", DXGI_FORMAT_R32G32B32A32_FLOAT);
    OnReload();
  }

  Shader::~Shader()
  {
    Clear();
    mLayout->Release();
  }

  void Shader::Clear()
  {
    if (mVS)
    {
      mVS->Release();
      mVS = nullptr;
    }
    if (mPS)
    {
      mPS->Release();
      mPS = nullptr;
    }
  }

  void Shader::OnReload()
  {
    Clear();

    ID3DBlob * pVSBlob = nullptr;
    ID3DBlob * pPSBlob = nullptr;

    CompileShaderFromFile(GetFilepath(), "VS", "vs_4_0", &pVSBlob);
    CompileShaderFromFile(GetFilepath(), "PS", "ps_4_0", &pPSBlob);

    HRESULT hr;
    hr = mDevice->CreateVertexShader(
      pVSBlob->GetBufferPointer(),
      pVSBlob->GetBufferSize(),
      nullptr,
      &mVS);

    if (FAILED(hr))
      ThrowException(GetDirectXError(hr));

    hr = mDevice->CreatePixelShader(
      pPSBlob->GetBufferPointer(),
      pPSBlob->GetBufferSize(),
      nullptr,
      &mPS);

    if (FAILED(hr))
      ThrowException(GetDirectXError(hr));

    // create the input layout
    mLayout = mLayoutCreator.Create(pVSBlob);

    pVSBlob->Release();
    pPSBlob->Release();
  }

  void Shader::CompileShaderFromFile(
    const std::string & filename,
    const std::string & entrypoint,
    const std::string & shadermodel,
    ID3DBlob** ppBlobOut )
  {
    HRESULT hr = S_OK;

    DWORD dwShaderFlags 
      = D3DCOMPILE_ENABLE_STRICTNESS
      | D3DCOMPILE_WARNINGS_ARE_ERRORS;

#if defined( DEBUG ) || defined( _DEBUG )
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
    hr = D3DX11CompileFromFile(
      filename.c_str(), 
      NULL, 
      NULL, 
      entrypoint.c_str(), 
      shadermodel.c_str(), 
      dwShaderFlags, 
      0, 
      NULL, 
      ppBlobOut, 
      &pErrorBlob, 
      NULL);
    if (pErrorBlob)
    {
      std::string err((char*)pErrorBlob->GetBufferPointer());
      pErrorBlob->Release();
      ThrowException(err);
    }
    if (FAILED(hr))
      ThrowException(GetDirectXError(hr));
  }

  ID3D11PixelShader * Shader::GetPS()
  {
    return mPS;
  }

  ID3D11VertexShader * Shader::GetVS()
  {
    return mVS;
  }

  ID3D11InputLayout * Shader::GetLayout()
  {
    return mLayout;
  }

  InputLayoutCreator::InputLayoutCreator( ID3D11Device * device ) 
    : mDevice(device)
  {

  }

  void InputLayoutCreator::AddSemantic( 
    const char * stringliteral, 
    DXGI_FORMAT datatype )
  {
    D3D11_INPUT_ELEMENT_DESC descriptor;
    descriptor.SemanticName = stringliteral; // hlsl name
    descriptor.SemanticIndex = 0; // for multiples of the same attribute
    descriptor.Format = datatype;
    descriptor.InputSlot = 0; // per element slot, dunno when to use
    descriptor.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    descriptor.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    descriptor.InstanceDataStepRate = 0; // only used for instancing
    mDescriptors.push_back(descriptor);
  }

  ID3D11InputLayout * InputLayoutCreator::Create( ID3DBlob * vsBlob )
  {
    ID3D11InputLayout * layout;

    HRESULT hr = mDevice->CreateInputLayout(
      &mDescriptors[0],
      (UINT) mDescriptors.size(),
      vsBlob->GetBufferPointer(),
      vsBlob->GetBufferSize(),
      &layout);

    if (FAILED(hr))
      ThrowException(GetDirectXError(hr));

    return layout;
  }

}
