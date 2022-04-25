#ifndef ISSUE_H
#define ISSUE_H

#include <string>


class Issue
{
private:
    std::string description, status, reporter, solver;
public:
    Issue();
    Issue(const std::string& d, const std::string& s, const std::string& r, const std::string& sv);

    inline const std::string& getDescription() const { return description; }
    inline const std::string& getStatus() const { return status; }
    inline const std::string& getReporter() const { return reporter; }
    inline const std::string& getSolver() const { return solver; }
};

#endif // ISSUE_H
