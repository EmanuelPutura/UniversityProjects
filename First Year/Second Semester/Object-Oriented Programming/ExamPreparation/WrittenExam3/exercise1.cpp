//#include <iostream>
//#include <vector>
//
//template <class T>
//class ToDo {
//private:
//    std::vector<T> elems;
//public:
//    ToDo& operator+= (const T& e) {
//        elems.push_back(e);
//        return *this;
//    }
//
//    auto begin() const {
//        return elems.rbegin();
//    }
//
//    auto end() const {
//        return elems.rend();
//    }
//
//    void reversePrint(std::ostream& os) {
//        for (auto it = elems.begin(); it != elems.end(); ++it)
//            os << *it << '\n';
//    }
//};
//
//class Activity {
//private:
//    const std::string descr, hour;
//public:
//    Activity(const std::string& d, const std::string& h) : descr(d), hour(h) {
//    }
//
//    friend std::ostream& operator<< (std::ostream& os, const Activity& act);
//};
//
//std::ostream &operator<<(std::ostream &os, const Activity &act) {
//    os << "Activity " << act.descr << " will take place at " << act.hour << ".";
//}
//
//void ToDoList()
//{
//    ToDo<Activity> todo{};
//    Activity tiff{ "go to TIFF movie", "20:00" };
//    todo += tiff;
//    Activity project{ "present project assignment", "09.20" };
//    todo += project;
//
//    // iterates through the activities and prints them as follows:
//    // Activity present project assignment will take place at 09.20.
//    // Activity go to TIFF movie will take place at 20.00.
//    for (auto a : todo)
//        std::cout << a << '\n';
//
//    // Prints the activities as follows:
//    // Activity go to TIFF movie will take place at 20.00.
//    // Activity present project assignment will take place at 09.20.
//    todo.reversePrint(std::cout);
//}
//
//int main() {
//    ToDoList();
//    return 0;
//}
