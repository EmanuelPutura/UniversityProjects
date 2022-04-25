#ifndef ISERVICE_H
#define ISERVICE_H

#include <string>

#include <domain/TrenchCoat/TrenchCoat.h>

class IService {
public:
    IService();

    virtual void add(const std::string& size, const std::string& colour, int price, int quantity, const std::string& photograph, bool ur_register=true) = 0;
    virtual void update(const std::string& size, const std::string& colour, int price, const std::string& photograph, const std::string& new_size,
                        const std::string& new_colour, int new_price, int new_quantity, const std::string& new_photograph, bool ur_register=true) = 0;
    virtual void remove(const std::string& size, const std::string& colour, int price, const std::string& photograph, bool ur_register=true) = 0;

    virtual void addToShoppingBasket(const int& index, const std::string& size, bool ur_register = true) = 0;
    virtual void removeFromShoppingBasket(TrenchCoat coat, bool ur_register = true) = 0;
};

#endif // ISERVICE_H
