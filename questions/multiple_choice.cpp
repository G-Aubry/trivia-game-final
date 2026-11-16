/**
* Grant Aubry
 * Trivia Final
 * 11/6/26
 */
#include "multiple_choice.h"
#include <algorithm>
#include <utility>

multiple_choice::multiple_choice(
    std::string cat, std::string text,
    std::vector<std::string> opts, std::string ans,
    std::mt19937& rng)
    : base_question(std::move(cat), std::move(text),
                    std::move(opts), std::move(ans)) {
    if (options.size() > 1) {
        std::shuffle(options.begin(), options.end(), rng);
    }
}

std::string multiple_choice::getType() const {
    return "MC";
}
