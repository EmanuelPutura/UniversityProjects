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
//class Ex1 {
//public:
//    Ex1() { cout << "Exception1 "; }
//    Ex1(const Ex1& ex) { cout << "Copy_ex1 "; }
//};
//
//class Ex2 : public Ex1 {
//public:
//    Ex2() { cout << "Exception2 "; }
//    Ex2(const Ex2& ex) { cout << "Copy_ex2 "; }
//};
//
//void except(int x) {
//    if (x < 0)
//        throw Ex1{};
//    else if (x == 0)
//        throw Ex2{};
//    cout << "Done ";
//}
//
//int main() {
//    try {
//        cout << "Start ";
//        try {
//            except(0);
//        }
//        catch (Ex1& e) {}
//        except(-2);
//    } catch (Ex1 e) {}
//
//    return 0;
//}