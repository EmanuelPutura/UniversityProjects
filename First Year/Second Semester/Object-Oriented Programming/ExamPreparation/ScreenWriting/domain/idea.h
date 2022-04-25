#ifndef IDEA_H
#define IDEA_H

#include <string>



class Idea
{
private:
    std::string description, status, creator;
    int act;
public:
    Idea();
    Idea(const std::string& d, const std::string& s, const std::string& c, int a);

    inline const std::string& getDescription() const { return description; }
    inline const std::string& getStatus() const { return status; }
    inline const std::string& getCreator() const { return creator; }
    inline int getAct() const { return act; }
};

#endif // IDEA_H
