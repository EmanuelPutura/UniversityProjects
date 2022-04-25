//#include <iostream>
//#include <string>
//#include <cassert>
//#include <vector>
//
//using namespace std;
//
//class Complex {
//private:
//    int real;
//    int imag;
//public:
//    Complex() : real(0), imag(0) {
//    }
//
//    Complex(int r, int i) : real(r), imag(i) {
//    }
//
//    int getReal() const {
//        return real;
//    }
//
//    int getImaginary() const {
//        return imag;
//    }
//
//    friend bool operator== (const Complex& c1, const Complex& c2) {
//        return c1.real == c2.real && c1.imag == c2.imag;
//    }
//
//    Complex operator/ (int div) {
//        if (div == 0)
//            throw std::runtime_error("Division by zero!");
//
//        Complex res {real / div, imag / div};
//        return res;
//    }
//
//    friend std::ostream& operator<< (std::ostream& os, const Complex& c) {
//        os << c.real << '+' << c.imag << 'i';
//        return os;
//    }
//};
//
//template <class T>
//class Vector {
//private:
//    T* elems;
//    int length;
//    int capacity;
//public:
//    explicit Vector(const std::vector<T>& v) : capacity(v.size() * 2), length(v.size()), elems(new T[v.size() * 2]) {
//        for (int i = 0; i < length; ++i)
//            elems[i] = v[i];
//    }
//
//    void printAll(std::ostream& os) const {
//        for (int i = 0; i < length; ++i)
//            os << elems[i] << ", ";
//    }
//
//private:
//    void resize() {
//        auto news = new T[capacity * 2];
//        for (int i = 0; i < capacity; ++i)
//            news = elems[i];
//        delete elems;
//
//        capacity *= 2;
//        elems = news;
//    }
//};
//
//void complex() {
//    Complex a{}, b{1, 2}, c{6, 4}, d{b};
//
//    assert(a.getReal() == 0 && a.getImaginary() == 0);
//    assert(c.getImaginary() == 4);
//    assert(b == d);
//
//    Complex res1 = c / 2;
//    cout << res1 << "\n"; // prints: 3+2i
//
//    try {
//        Complex res2 = b / 0;
//    }
//    catch (runtime_error& e) {
//        assert(strcmp(e.what(), "Division by zero!") == 0);
//    }
//
//    Vector<string> v1 {std::vector<string>{"hello", "bye"}};
//    v1.printAll(std::cout); // prints: hello, bye,
//
//    Vector<Complex> v2 {std::vector<Complex> {a, b, c, d}};
//    v2.printAll(std::cout); // prints: 0+0i, 1+2i, 6+4i, 1+2i,
//}
//
//int main() {
//    complex();
//    return 0;
//}
