#include "exception.h"


Exception::Exception(const std::string &message) : std::exception(), message(message)
{

}
