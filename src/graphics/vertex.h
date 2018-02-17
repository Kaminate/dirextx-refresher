#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
namespace Tac
{
  class Vertex
  {
  public:
    Vertex
      ( const DirectX::XMFLOAT3 & pos = DirectX::XMFLOAT3()
      , const DirectX::XMFLOAT4 & col = DirectX::XMFLOAT4()
      )
      : mPos(pos)
      , mCol(col)
    {}
    DirectX::XMFLOAT3 mPos;
    DirectX::XMFLOAT4 mCol;
  };
}

#include "application/TacResource.h"
#include <vector>

namespace Tac
{
  class VertexBuffer : public Resource
  {
  public:
    VertexBuffer(
      ID3D11Device * device, 
      const std::vector<Vertex> & vertexes);
    void OnReload() override;
    ID3D11Buffer * GetBuffer();
  private:
    ID3D11Device * mDevice;
    ID3D11Buffer * mBuffer;
  };

}