#ifndef QUESTION_H
#define QUESTION_H

#include <string>



class Question
{
private:
    int id;
    std::string text;
    std::string correct;
    int score;
public:
    Question();
    Question(int id, const std::string& txt, const std::string& correct, int score);

    inline int getID() const { return id; }
    inline const std::string& getText() const { return text; }
    inline const std::string& getCorrect() const { return correct; }
    inline int getScore() const { return score; }
};

#endif // QUESTION_H
