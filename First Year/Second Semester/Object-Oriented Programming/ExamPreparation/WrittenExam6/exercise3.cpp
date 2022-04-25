////
//// Created by Emanuel on 21.06.2021.
////
//
//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <string>
//
//using namespace std;
//
//int main() {
//    vector<int> v {1, 2, 3, 4, 5};
//    vector<int>::iterator it = std::find(v.begin(), v.end(), 4);
//    v.insert(it, 8);
//
//    for (auto a : v)
//        std::cout << a << ' ';
//    std::cout << '\n';
//
//    it = v.begin() + 2;
//    *it = 10;
//
//    for (auto a : v)
//        std::cout << a << ' ';
//    std::cout << '\n';
//
//    vector<int> x;
//
//    std::copy_if(v.begin(), v.end(), back_inserter(x), [](int a) {
//        return a % 2 == 0;
//    });
//
//    for (auto a : x)
//        cout << a << " ";
//    return 0;
//}