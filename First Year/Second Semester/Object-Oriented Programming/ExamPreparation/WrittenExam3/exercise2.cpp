////
//// Created by Emanuel on 20.06.2021.
////
//
//#include <string>
//#include <vector>
//#include <iostream>
//
//class SaleItem {
//private:
//    int code;
//    double price;
//public:
//    SaleItem(int code, double price) : code(code), price(price) {
//    }
//
//    int getCode() const { return code; }
//    double getPrice() const { return price; }
//};
//
//class Sale {
//private:
//    std::vector<SaleItem> items;
//public:
//    void add(const SaleItem& item) {
//        items.push_back(item);
//    }
//
//    const std::vector<SaleItem>& data() const { return items; }
//};
//
//class Discount {
//public:
//    virtual double calc(const Sale& sale) = 0;
//};
//
//class ItemDiscount : public Discount {
//private:
//    int code;
//    int percentage;
//public:
//    ItemDiscount(int code, int percentage) : code(code), percentage(percentage) {
//    }
//
//    double calc(const Sale& sale) override {
//        double result = 0;
//
//        for (const auto& item : sale.data()) {
//            if (item.getCode() == code) {
//                double discount = item.getPrice() * (double) percentage / 100;
//                result += discount;
//            }
//        }
//        return result;
//    }
//};
//
//class SumDiscount : public Discount {
//private:
//    std::vector<Discount*> discounts;
//public:
//    void add(Discount* discount) {
//        discounts.push_back(discount);
//    }
//
//    double calc(const Sale& sale) override {
//        double result = 0;
//        for (const auto& d : discounts)
//            result += d->calc(sale);
//        return result;
//    }
//};
//
//int main() {
//    SaleItem s1 {2, 100};
//    SaleItem s2 {1, 50};
//    SaleItem s3 {3, 75.5};
//
//    Sale sale;
//    sale.add(s1);
//    sale.add(s2);
//    sale.add(s3);
//
//    auto *d11 = new ItemDiscount {2, 10};
//    auto *d12 = new ItemDiscount {2, 15};
//    auto *d21 = new ItemDiscount {1, 10};
//    auto *d22 = new ItemDiscount {1, 15};
//    auto d31 = new ItemDiscount {3, 10};
//
//    SumDiscount sum_discount;
//    sum_discount.add(d11);
//    sum_discount.add(d12);
//    sum_discount.add(d21);
//    sum_discount.add(d22);
//    sum_discount.add(d31);
//
//    std::cout << "Sum discount is: " << sum_discount.calc(sale) << '\n';
//    return 0;
//}
