#ifndef CASTLE_H
#define CASTLE_H

#include <string>

class Castle
{
private:
    std::string name, location;
    int startingPrice, currentPrice;
public:
    Castle();
    Castle(const std::string& name, const std::string& location, int sp, int cp);

    inline void setCurrentPrice(int newPrice) { currentPrice = newPrice; }
    inline const std::string& getName() const { return name; }
    inline const std::string& getLocation() const { return location; }
    inline int getStartingPrice() const { return startingPrice; }
    inline int getCurrentPrice() const { return currentPrice; }
};

#endif // CASTLE_H
