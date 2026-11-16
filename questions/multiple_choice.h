/**
* Grant Aubry
 * Trivia Final
 * 11/6/26
 */
#ifndef MULTIPLE_CHOICE_QUESTION_H
#define MULTIPLE_CHOICE_QUESTION_H

#include "base_question.h"
#include <random>

class multiple_choice : public base_question {
public:
    multiple_choice(std::string cat, std::string text,
                             std::vector<std::string> opts, std::string ans,
                             std::mt19937& rng);
    std::string getType() const override;
};

#endif // MULTIPLE_CHOICE_QUESTION_H
