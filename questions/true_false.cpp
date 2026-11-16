/**
* Grant Aubry
 * Trivia Final
 * 11/6/26
 */
#include "true_false.h"
#include <utility>

true_false::true_false(
    std::string cat, std::string text, std::string ans)
    : base_question(std::move(cat), std::move(text),
                    {"True", "False"}, std::move(ans)) {}

std::string true_false::getType() const {
    return "TF";
}
