//
// Created by Emanuel on 21.03.2021.
//

#include "CoatsService.h"
#include "../exceptions/ServiceException/ServiceException.h"

#include <iostream>

#include <domain/FunctionsData/AddFunctionCall.h>

void CoatsService::add(const std::string& size, const std::string& colour, int price, int quantity, const std::string& photograph) {
    TrenchCoat coat(size, colour, price, quantity, photograph);
    if (!validator.validate(coat))
        throw ServiceException(validator.getErrors());
    try {
        repository.add(coat);
    }
    catch(const RepositoryException& exception) {
        throw ServiceException(exception.getMessage());
    }
}

void CoatsService::update(const std::string& size, const std::string& colour, int price, const std::string& photograph, const std::string& new_size,
                         const std::string& new_colour, int new_price, int new_quantity, const std::string& new_photograph) {
    int index = getIndex(size, colour, price, photograph);
    TrenchCoat new_element = TrenchCoat(new_size, new_colour, new_price, new_quantity, new_photograph);
    try {
        repository.update(repository[index], new_element);
    }
    catch(const RepositoryException& exception) {
        throw ServiceException(exception.getMessage());
    }
}

void CoatsService::remove(const std::string& size, const std::string& colour, int price, const std::string& photograph) {
    int index = getIndex(size, colour, price, photograph);
    try {
        repository.remove(repository[index]);
    }
    catch(const RepositoryException& exception) {
        throw ServiceException(exception.getMessage());
    }
}

std::ostream &operator<<(std::ostream& os, CoatsService service) {
    for (const auto& coat : service.repository.getData())
        os << coat << '\n';
    return os;
}

void CoatsService::addDefault() {
    std::string sizes[] = {"3XS", "XXS", "XS", "S", "M", "L", "XL", "XXL", "3XL", "4XL"};
    std::string colours[] = {"red", "orange", "yellow", "green", "blue", "black", "purple", "black", "white", "gray"};
    std::string photographs[] = {"https://www2.hm.com/en_asia3/productpage.0716384002.html",
                                 "https://ro.pinterest.com/pin/288863763575915988/",
                                 "https://ro.pinterest.com/pin/192528952790123664/",
                                 "https://www.fjackets.com/buy/Mission-Impossible-5-Rebecca-Ferguson-Coat.html",
                                 "https://lookastic.com/men/blue-trenchcoat/shop/brand-trench-coat-329153",
                                 "https://mt.burberry.com/mens-trench-coats/black/",
                                 "https://www.julienslive.com/m/lot-details/index/catalog/279/lot/108413",
                                 "https://www.coachoutlet.com/products/trench-coat/F33778.html",
                                 "https://www.aliexpress.com/item/32395372904.html",
                                 "https://www.hockerty.com/en/men/grey-trench-coat/"};
    int prices[] = {200, 300, 1000, 500, 700, 100, 300, 400, 200, 1000};
    int quantites[] = {20, 30, 50, 100, 40, 50, 20, 5, 1, 100};

    try {
        for (size_t i = 0; i < 10; ++i)
            add(sizes[i], colours[i], prices[i], quantites[i], photographs[i]);
    }
    catch (const ServiceException& exception) {
        if (exception.getMessage() == "The file cannot be opened.\n")
            throw ServiceException("The file cannot be opened.\n");
    }
}

std::vector<TrenchCoat> CoatsService::filterDataPerSize(const std::string& size) const {
    std::vector<TrenchCoat> coats;
    auto data = repository.getData();
    std::copy_if(data.begin(), data.end(), std::back_inserter(coats), [&size](const auto& el){ return el.getSize() == size || size == ""; });
    return coats;
}

int CoatsService::getCoatsPerSizeLength(const std::string &size) const {
    auto data = repository.getData();
    return std::count_if(data.begin(), data.end(), [&size](const auto& el){ return el.getSize() == size || size == ""; });
}

void CoatsService::launchBrowserSizeCoatPhoto(int index, const std::string &size) const {
    auto data = filterDataPerSize(size);
    Launcher().launch(data[index].getPhotograph());
}

void CoatsService::addToShoppingBasket(const int& index, const std::string& size) {
    auto data = filterDataPerSize(size);

    if (data[index].getQuantity() == 1)
        repository.remove(data[index]);
    payment += data[index].getPrice();

    int position = -1;
    try {
        position = repository.getIndex(data[index]);
        TrenchCoat update_coat {repository[position].getSize(), repository[position].getColour(), repository[position].getPrice(),
                         repository[position].getQuantity() - 1, repository[position].getPhotograph()};
        repository.update(repository[position], update_coat);
    }
    catch(const RepositoryException& exception) {
    }

    try {
        position = shopping_basket.getIndex(data[index]);
        TrenchCoat update_coat {shopping_basket[position].getSize(), shopping_basket[position].getColour(), shopping_basket[position].getPrice(),
                                shopping_basket[position].getQuantity() + 1, shopping_basket[position].getPhotograph()};
        shopping_basket.update(shopping_basket[position], update_coat);
    }
    catch(const RepositoryException& exception) {
        data[index].setQuantity(1);
        shopping_basket.add(data[index]);
    }
}

int CoatsService::getIndex(const std::string& size, const std::string& colour, int price, const std::string& photograph) const {
    TrenchCoat coat {size, colour, price, 0, photograph};
    try {
        return repository.getIndex(coat);
    }
    catch(const RepositoryException& exception) {
        throw ServiceException(exception.getMessage());
    }
}
