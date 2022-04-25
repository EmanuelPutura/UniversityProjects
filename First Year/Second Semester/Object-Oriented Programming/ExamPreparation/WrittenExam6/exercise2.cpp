////
//// Created by Emanuel on 21.06.2021.
////
//
//#include <iostream>
//#include <string>
//#include <vector>
//#include <crtdbg.h>
//
//class Action {
//private:
//public:
//    virtual void execute() const = 0;
//    virtual ~Action() = default;
//};
//
//class CreateAction : public Action {
//    void execute() const override {
//        std::cout << " Create file";
//    }
//
//    ~CreateAction() = default;
//};
//
//class ExitAction : public Action {
//    void execute() const override {
//        std::cout << " Exit application";
//    }
//
//    ~ExitAction() = default;
//};
//
//class MenuItem {
//protected:
//    std::string text;
//    Action* action = nullptr;
//
//    MenuItem(const std::string& text) : text(text) {
//    }
//public:
//    MenuItem(const std::string& text, Action* action) : text(text), action(action) {
//    }
//
//    virtual ~MenuItem() {
//        if (action != nullptr)
//            delete action;
//    }
//
//    virtual void print() const {
//        std::cout << text;
//    }
//
//    void clicked() {
//        print();
//        if (action != nullptr)
//            action->execute();
//    }
//};
//
//class Menu : public MenuItem {
//private:
//    std::vector<MenuItem*> items;
//public:
//    Menu(const std::string& text) : MenuItem(text) {
//    }
//
//    ~Menu() {
//        for (const auto& item : items)
//            delete item;
//    }
//
//    Menu(const std::string& text, Action* action) : MenuItem(text, action) {
//    }
//
//    void add(MenuItem* menu) {
//        items.push_back(menu);
//    }
//
//    void print() const override {
//        MenuItem::print();
//        for (const auto& item : items) {
//            std::cout << ' ';
//            item->print();
//        }
//    }
//};
//
//class MenuBar {
//private:
//    std::vector<Menu*> menus;
//public:
//    ~MenuBar() {
//        for (const auto& menu : menus)
//            delete menu;
//    }
//
//    void add(Menu* menu) {
//        menus.push_back(menu);
//    }
//
//    void print() const {
//        for (const auto& menu : menus) {
//            menu->print();
//        }
//    }
//};
//
//void function() {
//    auto *text = new Menu {"Text", new CreateAction};
//    auto *cpp = new Menu {"C++", new CreateAction};
//
//    auto *new_menu = new Menu {"New"};
//    auto *exit = new Menu {"Exit", new ExitAction};
//
//    new_menu->add(text);
//    new_menu->add(cpp);
//
//    auto *file = new Menu{"File"};
//    auto *about = new Menu{"About"};
//
//    file->add(new_menu);
//    file->add(exit);
//
//    MenuBar menubar;
//    menubar.add(file);
//    menubar.add(about);
//
//    file->clicked();
//    std::cout << '\n';
//    new_menu->clicked();
//    std::cout << '\n';
//    cpp->clicked();
//    std::cout << '\n';
//    exit->clicked();
//}
//
//int main() {
//    function();
//
//    int r = _CrtDumpMemoryLeaks();
//    printf("\nMemory Leaks: %d\n", r);
//
//    return 0;
//}
