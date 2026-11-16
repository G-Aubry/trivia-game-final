/**
* Grant Aubry
 * Trivia Final
 * 11/6/26
 */

#include "question_bank.h"
#include "multiple_choice.h"
#include "true_false.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <utility>

constexpr size_t MIN_TF_TOKENS = 4;
constexpr size_t MIN_MC_TOKENS = 5;
constexpr size_t CATEGORY_INDEX = 0;
constexpr size_t TYPE_INDEX = 1;
constexpr size_t QUESTION_INDEX = 2;
constexpr size_t ANSWER_INDEX = 3;

void question_bank::trimString(std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");
    if (first == std::string::npos) {
        str.clear();
    } else {
        str = str.substr(first, last - first + 1);
    }
}

std::vector<std::string> question_bank::tokenizeLine(const std::string& line) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, '|')) {
        trimString(token);
        tokens.push_back(token);
    }
    return tokens;
}

std::unique_ptr<base_question> question_bank::createMC(const std::vector<std::string>& tokens, std::mt19937& rng) {
    std::vector<std::string> opts(tokens.begin() + ANSWER_INDEX, tokens.end());
    return std::make_unique<multiple_choice>(
        tokens[CATEGORY_INDEX], tokens[QUESTION_INDEX], opts, tokens[ANSWER_INDEX], rng);
}

std::unique_ptr<base_question> question_bank::createTF(const std::vector<std::string>& tokens) {
    return std::make_unique<true_false>(
        tokens[CATEGORY_INDEX], tokens[QUESTION_INDEX], tokens[ANSWER_INDEX]);
}

std::unique_ptr<base_question> question_bank::parseLine(
    const std::vector<std::string>& tokens, std::mt19937& rng) {
    if (tokens.size() >= MIN_MC_TOKENS && tokens[TYPE_INDEX] == "MC") {
        return createMC(tokens, rng);
    }
    if (tokens.size() >= MIN_TF_TOKENS && tokens[TYPE_INDEX] == "TF") {
        return createTF(tokens);
    }
    return nullptr;
}

void question_bank::addParsedQuestion(const std::string& line, std::mt19937& rng) {
    const std::vector<std::string> tokens = tokenizeLine(line);
    auto q = parseLine(tokens, rng);
    if (q != nullptr) {
        std::string cat = q->getCategory();
        categorizedQuestions[cat].push_back(std::move(q));
    }
}

bool question_bank::loadFromFile(const std::string& filename, std::mt19937& rng) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            addParsedQuestion(line, rng);
        }
    }
    return true;
}

std::vector<base_question*> question_bank::getQuestionsByCategory(
    const std::string& category, const size_t count, std::mt19937& rng) const {
    std::vector<base_question*> result;
    auto iter = categorizedQuestions.find(category);
    if (iter != categorizedQuestions.end()) {
        std::vector<size_t> indices(iter->second.size());
        for (size_t i = 0; i < indices.size(); ++i) {
            indices[i] = i;
        }
        std::shuffle(indices.begin(), indices.end(), rng);
        const size_t limit = std::min(count, indices.size());
        for (size_t i = 0; i < limit; ++i) {
            result.push_back(iter->second[indices[i]].get());
        }
    }
    return result;
}

std::vector<base_question*> question_bank::getRandomQuestions(const size_t count, std::mt19937& rng) const {
    std::vector<base_question*> allQuestions;
    for (auto& pair : categorizedQuestions) {
        for (auto& qPtr : pair.second) {
            allQuestions.push_back(qPtr.get());
        }
    }
    std::shuffle(allQuestions.begin(), allQuestions.end(), rng);
    if (allQuestions.size() > count) {
        allQuestions.resize(count);
    }
    return allQuestions;
}

size_t question_bank::getCategoryQuestionCount(const std::string& category) const {
    auto iter = categorizedQuestions.find(category);
    if (iter != categorizedQuestions.end()) {
        return iter->second.size();
    }
    return 0;
}

std::vector<std::string> question_bank::getCategories() const {
    std::vector<std::string> categories;
    for (const auto& pair : categorizedQuestions) {
        categories.push_back(pair.first);
    }
    return categories;
}
