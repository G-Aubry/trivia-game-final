/**
* Grant Aubry
 * Trivia Final
 * 11/6/26
 */
#ifndef TRUE_FALSE_QUESTION_H
#define TRUE_FALSE_QUESTION_H

#include "base_question.h"

class true_false : public base_question {
public:
    true_false(std::string cat, std::string text, std::string ans);
    std::string getType() const override;
};

#endif // TRUE_FALSE_QUESTION_H
