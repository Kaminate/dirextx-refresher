#include "application/TacResource.h"
#include "util/TacException.h"
#include "util/TacWindowsError.h"
#include <windows.h>
#include <fileapi.h>
namespace Tac
{
  Resource::Resource( const std::string & filepath )
    : mFilepath(filepath)
  {
    mLastWrite = GetCurWrite();
  }

  // todo: move this funtion out
  void Resource::Reload()
  {
    FILETIME curWrite = GetCurWrite();
    if (IsOutdated(curWrite))
    {
      mLastWrite = curWrite;
      OnReload();
    }
  }

  const std::string & Resource::GetFilepath() const
  {
    return mFilepath;
  }

  FILETIME Resource::GetCurWrite()const
  {
    // hack
    if (mFilepath.empty())
      return mLastWrite;

    FILETIME create;
    FILETIME access;
    FILETIME write;
    HANDLE file;
    file = CreateFile(
      mFilepath.c_str(),
      GENERIC_READ,
      FILE_SHARE_READ,
      nullptr,
      OPEN_EXISTING,
      0,
      nullptr);

    if (file == INVALID_HANDLE_VALUE)
      ThrowException(GetLastWindowsError());

    bool failure = 0 == ::GetFileTime(file, &create, &access, &write);
    if (failure)
      ThrowException(GetLastWindowsError());

    CloseHandle(file);
    return write;
  }

  const FILETIME & Resource::GetLastWrite() const
  {
    return mLastWrite;
  }

  bool Resource::IsOutdated( const FILETIME & curWrite )const
  {
    return -1 == CompareFileTime(&mLastWrite, &curWrite);
  }

} // Tac
