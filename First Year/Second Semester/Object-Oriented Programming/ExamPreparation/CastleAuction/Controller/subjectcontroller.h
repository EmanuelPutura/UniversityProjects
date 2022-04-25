#ifndef SUBJECTCONTROLLER_H
#define SUBJECTCONTROLLER_H

#include <Domain/observerpattern.h>

#include <Infrastructure/castlesrepository.h>

class SubjectController : public Subject
{
private:
    CastlesRepository repository;
    std::vector<Castle> filtered_data;
public:
    SubjectController();
    ~SubjectController();

    void updateCurrentPrice(int index, int newPrice);
    void addFilteredData(std::string name);
    void removeFilteredData(std::string name);
    void updateCheckBox(std::string castle, bool value);

    inline const std::vector<Castle>& getData() { return filtered_data; }
    inline const std::vector<Castle>& getRepoData() { return repository.getData(); }
    inline int getLength() const { return filtered_data.size(); }
    inline int getRepoLength() const { return repository.getLength(); }
};

#endif // SUBJECTCONTROLLER_H
