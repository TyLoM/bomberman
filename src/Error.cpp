//
// Error.cpp for Bomberman in /home/mcnama_d/gitreps/B4-CPP/bomberman/src
//
// Made by Duncan McNAMARA
// Login   <mcnama_d@epitech.net>
//
// Started on  Sat May  9 17:03:48 2015 Duncan McNAMARA
// Last update Tue Jun  9 16:42:31 2015 Quentin Richard
//

#include "Error.hpp"

Error::Error(const std::string &_message) : runtime_error(_message)
{
  message = _message;
}

Error::~Error() throw ()
{}

char const	*Error::what() const throw()
{
  return message.c_str();
}
