#include "programmer.h"

Programmer::Programmer()
{
}

Programmer::Programmer(const std::string &n, int r, int t) : name(n), revised_files(r), to_revise(t)
{
}

std::string Programmer::toString() const
{
    return name + "," + std::to_string(revised_files) + "," + std::to_string(to_revise);
}
