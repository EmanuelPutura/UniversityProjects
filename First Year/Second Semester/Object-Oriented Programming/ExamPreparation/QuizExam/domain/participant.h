#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <string>



class Participant
{
private:
    std::string name;
    int score;
public:
    Participant();
    explicit Participant(const std::string& name, int score = 0);

    inline const std::string& getName() const { return name; }
    inline int getScore() const { return score; }
};

#endif // PARTICIPANT_H
