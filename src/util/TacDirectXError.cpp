#include "util/TacDirectXError.h"
#include <DxErr.h>




// begin hack
// https://stackoverflow.com/questions/31053670/unresolved-external-symbol-vsnprintf-in-dxerr-lib
#include <Windows.h>
#include <stdio.h>
int ( WINAPIV * __vsnprintf )( char *, size_t, const char*, va_list ) = _vsnprintf;
// end

namespace Tac
{
  std::string GetDirectXError( HRESULT hr )
  {
    std::string err;
    err.append(DXGetErrorString(hr));
    err.append(DXGetErrorDescription(hr));
    return err;
  }
}
