//
// Created by Emanuel on 20.06.2021.
//

#include <string>
#include <vector>
#include <assert.h>
#include <string.h>

class StackException : public std::exception {
private:
    std::string message;
public:
    explicit StackException (const std::string& message) : message(message) {
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

template <class T>
class Stack {
private:
    int capacity;
    std::vector<T> elems;
public:
    explicit Stack(int capacity) : capacity(capacity) {
    }

    int getMaxCapacity() {
        return capacity;
    }

    Stack operator+ (const T& op) {
        if (elems.size() == capacity)
            throw StackException("Stack is full!");
        elems.push_back(op);
        return *this;
    }

    T pop() {
        auto last = elems[elems.size() - 1];
        elems.pop_back();
        return last;
    }
};

void testStack()
{
    Stack<std::string> s{ 2 };
    assert(s.getMaxCapacity() == 2);
    try {
        s = s + "examination";
        s = s + "oop";
        s = s + "test";
    } catch (std::exception& e) {
        assert(strcmp(e.what(), "Stack is full!") == 0);
    }
    assert(s.pop() == "oop");
    assert(s.pop() == "examination");
}

int main() {
    testStack();
    return 0;
}