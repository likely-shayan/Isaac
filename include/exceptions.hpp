#include <string>
#include <stdexcept>

namespace Isaac {

  class ZeroDevisionException : public std::exception {
    private:
      std::string message;

    public:
      ZeroDevisionException(const char* msg) : message(msg) {}

      const char* what() const throw() {
        return message.c_str();
      }
  };

} // namespace Isaac