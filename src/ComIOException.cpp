#include "ComIOException.h"

ComIOException::ComIOException(const std::string& msg)
  : m_msg(msg)
{ }

const char* ComIOException::what() const throw()
{ return ("ComIOException: "+m_msg).c_str(); }
