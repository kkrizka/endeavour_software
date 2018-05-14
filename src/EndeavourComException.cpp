#include "EndeavourComException.h"

EndeavourComException::EndeavourComException(const std::string& msg)
  : m_msg(msg)
{ }

EndeavourComException::EndeavourComException(const char *format, ...)
{
  char buffer[256];

  va_list args;
  va_start( args, format );
  vsnprintf( buffer, 256, format, args );
  va_end( args );

  m_msg=buffer;
}

const char* EndeavourComException::what() const throw()
{ return ("EndeavourComException: "+m_msg).c_str(); }
