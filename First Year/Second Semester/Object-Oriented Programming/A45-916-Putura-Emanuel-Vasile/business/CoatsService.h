//
// Created by Emanuel on 21.03.2021.
//

#ifndef COATSSERVICE_H
#define COATSSERVICE_H

#include "../infrastructure/Repository/Repository.h"
#include "../validation/CoatValidator.h"
#include "../presentation/TextTable/TextTable.h"
#include "../tools/BrowserLauncher.h"

#include <string>
#include <vector>

/**
 * CoatsService Class
 */
class CoatsService {
private:
    AbstractRepository<TrenchCoat>& repository;
    AbstractRepository<TrenchCoat>& shopping_basket;
    CoatValidator validator;
    int payment = 0;
public:
    CoatsService(AbstractRepository<TrenchCoat>& repository, AbstractRepository<TrenchCoat>& shopping_basket) : repository(repository), shopping_basket(shopping_basket),
                                                                                    validator(CoatValidator()) {
        auto data = shopping_basket.getData();
        for (const auto& element : data)
            payment += (element.getPrice() * element.getQuantity());
    }

    /**
     * Adds a new trench coat to the repository
     * @param size: the size of the trench coat
     * @param colour: the colour of the trench coat
     * @param price: the price of the trench coat
     * @param quantity: the quantity of the trench coat
     * @param photograph: the photograph of the trench coat
     */
    void add(const std::string& size, const std::string& colour, int price, int quantity, const std::string& photograph);

    /**
     * Updates a TrenchCoat object from the repository
     */
    void update(const std::string& size, const std::string& colour, int price, const std::string& photograph, const std::string& new_size,
                const std::string& new_colour, int new_price, int new_quantity, const std::string& new_photograph);

    /**
     * Removes a trench coat from the repository
     * @param size: the size of the trench coat
     * @param colour: the colour of the trench coat
     * @param price: the price of the trench coat
     * @param photograph: the photograph of the trench coat
     */
    void remove(const std::string& size, const std::string& colour, int price, const std::string& photograph);

    /*
     * Overloading the << (extraction) operator
     */
    friend std::ostream& operator<<(std::ostream& os, CoatsService service);

    /**
     * Adds ten default trench coats to the repository
     */
    void addDefault();

    /*
     * Filters data per size
     * @param size: the size of the trench coat
     * @returns: the filtered data
     */
    std::vector<TrenchCoat> filterDataPerSize(const std::string& size) const;

    /*
     * Gets the length of filtered coats per size
     * @param size: the size of the trench coat
     * @returns: the requested length
     */
    int getCoatsPerSizeLength(const std::string& size) const;

    /*
     * Gets single coat text table, being given an index and a size as filtering parameter
     */
    inline TextTable getSingleCoatPerSizeTextTable(int index, const std::string& size) const {
        return getSingleCoatTextTable(index, filterDataPerSize(size));
    }

    /*
     * Launches the browser to show a coat
     */
    void launchBrowserSizeCoatPhoto(int index, const std::string& size) const;

    /*
     * Adds a coat to the shopping basket
     * @param index: index of the coat to be added
     * @param size: the size of the trench coat
     */
    void addToShoppingBasket(const int& index, const std::string& size);

    /*
     * Gets the text table representation of more trench coats
     */
    TextTable getDataTextTable(const std::vector<TrenchCoat>& data, int length) const;

    /*
     * Gets the text table representation of a single trench coat
     */
    TextTable getSingleCoatTextTable(int index, const std::vector<TrenchCoat>& data) const;

    int getIndex(const std::string& size, const std::string& colour, int price, const std::string& photograph) const;

    /*
     * Gets the shopping basket
     */
    inline TextTable getShoppingBasket() const { return getDataTextTable(shopping_basket.getData(), shopping_basket.getLength()); }

    /**
     * Gets the length of the repository (the number of trench coats in the repository)
     */
    inline int getLength() const { return repository.getLength(); }
    inline int getPayment() const { return payment; }
    inline const std::vector<TrenchCoat>& getData() const { return repository.getData(); }
};

#endif
