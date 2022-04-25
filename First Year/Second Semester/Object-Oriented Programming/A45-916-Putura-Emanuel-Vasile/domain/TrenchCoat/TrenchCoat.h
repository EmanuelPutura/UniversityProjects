//
// Created by Emanuel on 21.03.2021.
//

#ifndef TRENCHCOAT_H
#define TRENCHCOAT_H

#include <string>

/**
 * TrenchCoat Class
 */
class TrenchCoat {
private:
    std::string colour, photograph, size;
    int price, quantity;
public:
    explicit TrenchCoat(const std::string& size = "", const std::string& colour = "", int price = 0, int quantity = 0, const std::string& photograph = "") :
        size(size), colour(colour), price(price), quantity(quantity), photograph(photograph) {}

    /**
     * Friend function overloading the << operator
     */
    friend std::ostream& operator<<(std::ostream& os, const TrenchCoat& coat);

    /**
     * Friend function overloading the >> operator
     */
     friend std::istream& operator>>(std::istream& is, TrenchCoat& coat);

    /*
     * Friend function overloading the == operator
     * Equality between two TrenchCoat objects occurs if and only if they have the same size, colour, price and photograph
     * @return: true if the two TrenchCoat objects are equal, false else
     */
    friend bool operator== (const TrenchCoat& t1, const TrenchCoat& t2);

    /**
     * Getters and setters
     */
    inline int getPrice() const { return price; }
    inline int getQuantity() const { return quantity; }
    inline const std::string& getSize() const { return size; }
    inline const std::string& getColour() const { return colour; }
    inline const std::string& getPhotograph() const { return photograph; }

    inline void setQuantity(const int& other) { quantity = other; }
};

#endif
