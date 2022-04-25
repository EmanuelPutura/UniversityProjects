#ifndef PROGRAMMER_H
#define PROGRAMMER_H

#include <string>



class Programmer
{
private:
    std::string name;
    int revised_files;
    int to_revise;
public:
    Programmer();
    Programmer(const std::string& n, int r, int t);

    std::string toString() const;

    inline void incRevisedFiles() { revised_files++; }
    inline void decToRevised() { to_revise--; }

    inline const std::string& getName() const { return name; }
    inline int getRevisedFiles() const { return revised_files; }
    inline int getToRevise() const { return to_revise; }
};

#endif // PROGRAMMER_H
