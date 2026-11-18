/**
* Grant Aubry
 * Trivia Final
 * 11/6/26
 */

#ifndef QUESTION_BANK_H
#define QUESTION_BANK_H

#include "base_question.h"
#include <memory>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * Contains the Questions to be used in the game
 */
class question_bank {
private:
 std::unordered_map<std::string, std::vector<std::unique_ptr<base_question>>> categorizedQuestions;
 static void trimString(std::string& str);
 static std::vector<std::string> tokenizeLine(const std::string& line);

 static std::unique_ptr<base_question> parseLine(const std::vector<std::string>& tokens, std::mt19937& rng);
 static std::unique_ptr<base_question> createMC(const std::vector<std::string>& tokens, std::mt19937& rng);
 static std::unique_ptr<base_question> createTF(const std::vector<std::string>& tokens);
 void addParsedQuestion(const std::string& line, std::mt19937& rng);

public:
 question_bank() = default;

 /**
  * Reads Questions from files
  * @param filename file containing questions
  * @param rng used to randomize the question order
  * @return whether the file was successfully read
  */
 bool loadFromFile(const std::string& filename, std::mt19937& rng);

 /**
  * Returns questions based on the specified category
  * @param category of questions to extract
  * @param count of questions to be extracted
  * @param rng ensures order is randomized
  * @return a vector containing the questions
  */
 std::vector<base_question*> getQuestionsByCategory(const std::string& category, size_t count, std::mt19937& rng) const;

 /**
  * Extracts a random selection of questions
  * @param count of questions to return
  * @param rng ensures questions are randomized
  * @return vector containing the questions
  */
 std::vector<base_question*> getRandomQuestions(size_t count, std::mt19937& rng) const;

 size_t getCategoryQuestionCount(const std::string& category) const;
 size_t getTotalQuestionCount() const;
 std::vector<std::string> getCategories() const;
};

#endif // QUESTION_BANK_H
