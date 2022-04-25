#include "castle.h"

Castle::Castle()
{
}

Castle::Castle(const std::string &name, const std::string &location, int sp, int cp) : name(name), location(location), startingPrice(sp), currentPrice(cp)
{
}
