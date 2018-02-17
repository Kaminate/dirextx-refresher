#include "util/TacFileReader.h"
#include "util/TacWindowsError.h"
#include "util/TacException.h"
#include <fstream>

namespace Tac
{
  FileReader::FileReader( const std::string & filename )
  {
    std::ifstream myfile(filename.c_str(), std::ifstream::binary);
    bool success = myfile.is_open();
    if (success)
    {
      myfile.seekg(0, myfile.end);
      unsigned length = (unsigned) myfile.tellg();
      myfile.seekg(0, myfile.beg);
      mSource.resize(length);
      myfile.read(&mSource[0], mSource.size());
      myfile.close();
    }
    else
      ThrowException(GetLastWindowsError());
  }

  const char * FileReader::GetSource() const
  {
    return mSource.c_str();
  }

  size_t FileReader::GetLen() const
  {
    return mSource.length();
  }

}
