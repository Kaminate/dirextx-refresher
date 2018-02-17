#pragma once

#include <exception>
#include <string>

namespace Tac
{
  class Exception : public std::exception
  {
  public:
    virtual const char * what() const override;
  private:
    friend void ThrowExceptionAux(
      const std::string & str,
      const std::string & line,
      const std::string & file,
      const std::string & function);
    Exception(const std::string & str);
    std::string mStr;
  };
  void ThrowExceptionAux(
    const std::string & str, 
    const std::string & line,
    const std::string & file,
    const std::string & function);

#define ThrowException(str) \
  ThrowExceptionAux( \
  str,  \
  std::to_string(__LINE__), \
  __FILE__, \
  __FUNCTION__);

} // Tac
