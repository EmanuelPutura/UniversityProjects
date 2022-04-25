////
//// Created by Emanuel on 20.06.2021.
////
//
//#ifndef WRITTENEXAM_VECTOR_H
//#define WRITTENEXAM_VECTOR_H
//
//#define CAPACITY 10
//
//template<class T>
//class Vector {
//private:
//    T* elements;
//    int length;
//    int capacity;
//public:
//    Vector();
//    ~Vector();
//
//    Vector<T>& add(const T& element);
//    T* getElems() const { return elements; }
//
//    auto begin() const;
//    auto end() const;
//
//    template <class Type>
//    class Iterator {
//    private:
//        Type* elems;
//        int current;
//    public:
//        explicit Iterator<Type>(Type* e) : elems(e), current(0) {
//        }
//
//        Type& operator*() {
//            return elems[current];
//        }
//
//        bool operator!= (const Iterator<Type>& other) {
//            return current != other.current;
//        }
//
//        void operator++ () {
//            current++;
//        }
//
//        void setCurrent(int c) {
//            current = c;
//        }
//
//        int getCurrent() const {
//            return current;
//        }
//    };
//private:
//    void resize();
//};
//
//template<class T>
//Vector<T>::Vector() : elements(new T[CAPACITY]), length(0), capacity(CAPACITY) {
//}
//
//template<class T>
//Vector<T>::~Vector() {
//    delete elements;
//}
//
//template<class T>
//Vector<T> &Vector<T>::add(const T& element) {
//    if (length == capacity)
//        resize();
//
//    elements[length] = element;
//    length++;
//    return *this;
//}
//
//template<class T>
//void Vector<T>::resize() {
//    auto new_elems = new T[capacity * 2];
//
//    for (int i = 0; i < capacity; ++i)
//        new_elems[i] = elements[i];
//    capacity *= 2;
//
//    delete elements;
//    new_elems = elements;
//}
//
//template<class T>
//auto Vector<T>::begin() const {
//    return Iterator<T>(elements);
//}
//
//template<class T>
//auto Vector<T>::end() const {
//    auto it = Iterator<T>(elements);
//    it.setCurrent(length);
//    return it;
//}
//
//#endif //WRITTENEXAM_VECTOR_H
