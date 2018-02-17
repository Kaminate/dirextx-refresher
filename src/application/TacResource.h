#pragma once
#include <string>
#include <wtypesbase.h>
namespace Tac
{
  class ResourceManager
  {

  };

  class Resource
  {
  public:
    Resource(const std::string & filepath);
    void Reload();
    virtual void OnReload() = 0;
    const std::string & GetFilepath() const;
    const FILETIME & GetLastWrite() const;
    FILETIME GetCurWrite() const;
    bool IsOutdated(const FILETIME & curWrite) const;

  private:
    std::string mFilepath;
    FILETIME mLastWrite;
  };
}