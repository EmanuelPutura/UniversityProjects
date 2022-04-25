////
//// Created by Emanuel on 20.06.2021.
////
//
//#include <vector>
//#include <string>
//#include <stdexcept>
//#include <assert.h>
//#include <string.h>
//#include <algorithm>
//#include <iostream>
//
//
//template <class C1, class C2>
//class List {
//private:
//    std::vector<std::pair<C1, C2>> elems;
//public:
//
//    /*
//     * descr: Sorts the list by its first component. Assumes the two components of a list element have the < operator
//     *      overloaded.
//     * throws: runtime_error if the list if empty
//     */
//    void sortByFirstComponent() {
//        if (elems.empty())
//            throw std::runtime_error("List is empty!");
//
//        std::sort(elems.begin(), elems.end(), [](const auto& e1, const auto& e2) {
//            return e1.first < e2.first;
//        });
//    }
//
//    void sortBySecondComponent() {
//        std::sort(elems.begin(), elems.end(), [](const auto& e1, const auto& e2){
//            return e1.second < e2.second;
//        });
//    }
//
//    void printReverse(std::ostream& os) const {
//        for (int i = elems.size() - 1; i >= 0; --i) {
//            os << elems[i].first.toString() << " -> " << elems[i].second;
//            if (i == 0)
//                os << '\n';
//            else os << "; ";
//        }
//    }
//
//    void add(const C1& c1, const C2& c2) {
//        elems.push_back({c1, c2});
//    }
//};
//
//class Car {
//private:
//    std::string type;
//    int number;
//public:
//    Car() : type(""), number(0) {
//    }
//
//    Car(const std::string& t, int n) : type(t), number(n) {
//    }
//
//    std::string toString() const {
//        return type + " " + std::to_string(number);
//    }
//
//    bool operator< (const Car& other) const {
//        return number < other.number;
//    }
//
//    const std::string& getType() const { return type; }
//    int getNumber() const { return number; }
//};
//
//void function1() {
//    List<Car, int> list1;
//    try {
//        list1.sortByFirstComponent();
//        assert(false);
//    }
//    catch (std::runtime_error& e) { assert(strcmp(e.what(), "List is empty!") == 0);	}
//
//    list1.add(Car{ "Audi", 20 }, 8);
//    list1.add(Car{ "Volkswagen", 10 }, 9);
//    list1.add(Car{ "Bentley", 300 }, 10);
//
//    list1.sortByFirstComponent();
//    list1.printReverse(std::cout); // prints: Bentley 300 -> 10; Audi 20 -> 8; Volkswagen 10 -> 9
//    list1.sortBySecondComponent();
//    list1.printReverse(std::cout); // prints: Bentley 300 -> 10; Volkswagen 10 -> 9; Audi 20 -> 8;
//}
//
//int main() {
//    function1();
//    return 0;
//}
