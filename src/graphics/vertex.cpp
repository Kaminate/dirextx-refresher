#include "graphics/vertex.h"
#include <vector>
#include <util/TacException.h>
#include <util/TacDirectXError.h>
namespace Tac
{
  VertexBuffer::VertexBuffer( 
    ID3D11Device * device,
    const std::vector<Vertex> & vertexes)
    : Resource("")
    , mDevice(device)
  {
    D3D11_BUFFER_DESC desc = {0};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.ByteWidth = UINT(vertexes.size() * sizeof(vertexes[0]));
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    desc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA initdata = {0};
    initdata.pSysMem = &vertexes[0];

    HRESULT hr = mDevice->CreateBuffer(&desc, &initdata, &mBuffer);
    if (FAILED(hr))
      ThrowException(GetDirectXError(hr));
  }

  void VertexBuffer::OnReload()
  {

  }

  ID3D11Buffer * VertexBuffer::GetBuffer()
  {
    return mBuffer;
  }

}
