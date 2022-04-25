#include "idea.h"

Idea::Idea()
{

}

Idea::Idea(const std::string &d, const std::string &s, const std::string &c, int a) :
    description(d), status(s), creator(c), act(a)
{

}
