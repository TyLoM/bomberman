//
// Error.hpp for Bomberman in /home/mcnama_d/gitreps/B4-CPP/bomberman/inc
//
// Made by Duncan McNAMARA
// Login   <mcnama_d@epitech.net>
//
// Started on  Sat May  9 17:16:34 2015 Duncan McNAMARA
// Last update Fri May 15 17:57:06 2015 Quentin Richard
//

#ifndef ERROR_HPP_
# define ERROR_HPP_

# include <string>
# include <stdexcept>
# include <iostream>

class			Error : public std::runtime_error
{
public:
  Error(const std::string &);
  virtual char const	*what() const throw();
  virtual ~Error() throw();
protected:
  std::string		message;
};


#endif /* !ERROR_HPP_ */
