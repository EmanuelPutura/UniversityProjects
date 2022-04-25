#ifndef SOURCEFILE_H
#define SOURCEFILE_H

#include <string>



class SourceFile
{
private:
    std::string name;
    std::string status;
    std::string creator;
    std::string reviewer;
public:
    SourceFile();
    SourceFile(std::string n, std::string s, std::string c, std::string r);

    std::string toString() const;

    inline const std::string& getName() const { return name; }
    inline const std::string& getStatus() const { return status; }
    inline const std::string& getCreator() const { return creator; }
    inline const std::string& getReviewer() const { return reviewer; }
};

#endif // SOURCEFILE_H
