#ifndef WRITER_H
#define WRITER_H

#include <string>



class Writer
{
private:
    std::string name, expertise;
public:
    Writer();
    Writer(const std::string& n, const std::string& e);

    inline const std::string& getName() const { return name; }
    inline const std::string& getExpertise() const { return expertise; }
};

#endif // WRITER_H
