/**
* Grant Aubry
 * Trivia Final
 * 11/5/26
 */
#include "base_question.h"
#include <iostream>
#include <utility>

base_question::base_question(std::string cat, std::string text,
                             std::vector<std::string> opts, std::string ans)
    : category(std::move(cat)),
      questionText(std::move(text)),
      options(std::move(opts)),
      correctAnswer(std::move(ans)) {}

void base_question::displayQuestion() const {
    std::cout << "[" << category << "]\n";
    std::cout << questionText << "\n";
    for (size_t i = 0; i < options.size(); ++i) {
        char label = static_cast<char>('A' + i);
        std::cout << "  " << label << ") " << options[i] << "\n";
    }
}

bool base_question::isCorrect(size_t chosenIndex) const {
    if (chosenIndex >= options.size()) {
        return false;
    }
    return options[chosenIndex] == correctAnswer;
}

std::string base_question::getCategory() const {
    return category;
}

std::string base_question::getQuestion() const {
    return questionText;
}

std::string base_question::getAnswer() const {
    return correctAnswer;
}

const std::vector<std::string>& base_question::getOptions() const {
    return options;
}

size_t base_question::getOptionCount() const {
    return options.size();
}