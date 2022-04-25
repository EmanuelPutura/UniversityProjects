//
// Created by Emanuel on 20.06.2021.
//

#ifndef WRITTENEXAM_SMARTPOINTER_H
#define WRITTENEXAM_SMARTPOINTER_H


template <class T>
class SmartPointer {
private:
    T* ptr;
public:
    SmartPointer();
    explicit SmartPointer(T* ptr);

    const T& operator* () const;
    SmartPointer<T>& operator= (const SmartPointer<T>& other);
    bool operator== (const SmartPointer<T>& other);

    ~SmartPointer();
};

template <class T>
SmartPointer<T>::SmartPointer() : ptr(new T) {
}

template <class T>
SmartPointer<T>::SmartPointer(T* ptr) : ptr(ptr) {
}

template <class T>
SmartPointer<T>::~SmartPointer() {
    delete ptr;
}

template<class T>
const T &SmartPointer<T>::operator*() const {
    return *ptr;
}

template<class T>
SmartPointer<T> &SmartPointer<T>::operator=(const SmartPointer<T>& other) {
    ptr = new T;
    *ptr = *other.ptr;
}

template<class T>
bool SmartPointer<T>::operator==(const SmartPointer<T>& other) {
    return *ptr == *other.ptr;
}


#endif //WRITTENEXAM_SMARTPOINTER_H
