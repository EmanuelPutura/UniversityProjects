#include "issue.h"

Issue::Issue() : description(""), status(""), reporter(""), solver("")
{

}

Issue::Issue(const std::string &d, const std::string &s, const std::string &r, const std::string &sv) :
     description(d), status(s), reporter(r), solver(sv)
{

}
