#include "question.h"

Question::Question()
{
}

Question::Question(int id, const std::string &txt, const std::string &correct, int score) :
            id(id), text(txt), correct(correct), score(score)
{

}
