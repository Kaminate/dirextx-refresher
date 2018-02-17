#include "util/TacException.h"
namespace Tac
{

  Exception::Exception( const std::string & str )
    : mStr(str)
  {

  }

  const char * Exception::what() const 
  {
    return mStr.c_str();
  }
  void ThrowExceptionAux(
    const std::string & str, 
    const std::string & line,
    const std::string & file,
    const std::string & function)
  {
    throw Exception(
      "Exception in line " + line 
      + " in function " + function 
      + " in file " + file + ": " + str);
  }


}
