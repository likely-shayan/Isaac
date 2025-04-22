#ifndef EXCEPTIONS_HPP_
#define EXCEPTIONS_HPP_

#include <exception>
#include <string>

namespace Isaac
{

  class NegativeLengthException : public std::exception
  {
    private:
      std::string message;

    public:
      NegativeLengthException(const char* description) : message(description) {}

      const char* what() const throw() {return message.c_str();}
  };

  class NegativeMassException : public std::exception
  {
    private:
      std::string message;
    
    public:
      NegativeMassException(const char* description) : message(description) {}

      const char* what() const throw() {return message.c_str();}
  };

}; // namespace Isaac

#endif // EXCEPTIONS_HPP