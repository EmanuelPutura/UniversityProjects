#ifndef ISERVICE_H
#define ISERVICE_H

#include <string>



class IService {
public:
    IService();

    virtual void add(const std::string& size, const std::string& colour, int price, int quantity, const std::string& photograph) = 0;
    virtual void update(const std::string& size, const std::string& colour, int price, const std::string& photograph, const std::string& new_size,
                        const std::string& new_colour, int new_price, int new_quantity, const std::string& new_photograph) = 0;
    virtual void remove(const std::string& size, const std::string& colour, int price, const std::string& photograph) = 0;
};

#endif // ISERVICE_H
