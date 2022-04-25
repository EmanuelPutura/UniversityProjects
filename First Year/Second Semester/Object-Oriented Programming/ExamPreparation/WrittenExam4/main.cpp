#include <crtdbg.h>
#include <iostream>
#include <exception>

using namespace std;

#define CAPACITY 1

class Exception : public exception {
private:
    std::string message;
public:
    explicit Exception(const std::string& m) : exception(), message(m) {
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

template <class T>
class SmartPointer {
private:
    T* ptr;
public:
    SmartPointer() : ptr(new T) {
    }

    SmartPointer(const SmartPointer<T>& other) : ptr (new T) {
        *ptr = *other.ptr;
    }

    explicit SmartPointer(T* ptr) : ptr(ptr) {
    }

    const T& operator* () const {
        return *ptr;
    }

    SmartPointer<T>& operator= (const SmartPointer<T>& other) {
        *ptr = *other.ptr;
        return *this;
    }

    bool operator== (const SmartPointer<T>& other) {
        return *ptr == *other.ptr;
    }

    ~SmartPointer() {
        delete ptr;
    }
};

template <class T>
class Vector {
private:
    T* elems;
    int length;
    int capacity;
public:
    Vector() : elems(new T[CAPACITY]), capacity(CAPACITY), length(0) {
    }

    Vector(const Vector<T>& other) : elems(new T[other.capacity]) {
        for (int i = 0; i < other.length; ++i)
            elems[i] = other.elems[i];
        length = other.length;
        capacity = other.capacity;
    }

    ~Vector() {
        delete[] elems;
    }

    Vector<T>& operator= (const Vector<T>& other) {
        delete[] elems;
        elems = new T[other.capacity];

        for (int i = 0; i < other.length; ++i)
            elems[i] = other.elems[i];

        capacity = other.capacity;
        length = other.length;
        return *this;
    }

    Vector<T>& add(const T& el) {
        if (length == capacity)
            resize();

        elems[length] = el;
        length++;
        return *this;
    }

    Vector<T> operator- (const T& el) {
        Vector<T> copy = *this;

        bool found = false;
        for (int i = 0; i < length; ++i) {
            if (elems[i] == el) {
                for (int j = i; j < length - 1; ++j) {
                    elems[j] = elems[j + 1];
                }

                length--;
                found = true;
                break;
            }
        }

        if (!found)
            throw Exception("Element does not exist!");

        Vector<T> result = *this;
        *this = copy;
        return result;
    }

    T* begin() const {
        return elems;
    }

    T* end() const {
       return elems + length;
    }

private:
    void resize() {
        auto new_elems = new T[2 * capacity];

        for (int i = 0; i < capacity; ++i)
            new_elems[i] = elems[i];
        capacity *= 2;

        delete[] elems;
        elems = new_elems;
    }
};

void function() {
    SmartPointer<int> i1 { new int {1} };
    SmartPointer<int> i2 { new int {2} };
    SmartPointer<int> i3 { new int {3} };

    Vector<SmartPointer<int>> v1{};
    v1.add(i1).add(i2).add(i3);
    for (auto e : v1)
        cout << *e << ", "; // Prints 1, 2, 3

    SmartPointer<string> s1 { new string {"A"} };
    SmartPointer<string> s2 = s1;
    SmartPointer<string> s3 { new string {"C"} };

    Vector<SmartPointer<string>> v2{};
    v2.add(s2).add(s1);
    std::cout << '\n';

    try {
        v2 = v2 - s2;
        v2 = v2 - s3;
    }
    catch (exception& ex) {
        cout << ex.what(); // Prints: Element does not exist!
    }
}

int main() {
    function();

//    int r = _CrtDumpMemoryLeaks();
//    printf("\nMemory Leaks: %d\n", r);

    return 0;
}
