//
// Created by Emanuel on 20.06.2021.
//

#ifndef WRITTENEXAM_SMARTPOINTER_H
#define WRITTENEXAM_SMARTPOINTER_H


template<class T>
class SmartPointer {
private:
    T* data;
public:
    SmartPointer();
    explicit SmartPointer(T* data);

    ~SmartPointer();
};

template<class T>
SmartPointer<T>::SmartPointer() : data(new T) {
}

template<class T>
SmartPointer<T>::SmartPointer(T *data) : data(data) {
}

template<class T>
SmartPointer<T>::~SmartPointer() {
    delete data;
}


#endif //WRITTENEXAM_SMARTPOINTER_H
