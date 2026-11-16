/**
- Grant Aubry
- Trivia Final
- 11/11/26
 */

#ifndef BASE_ROUND_H
#define BASE_ROUND_H

#include "../questions/base_question.h"
#include <iostream>
#include <string>
#include <vector>

class base_round {
protected:
    std::string roundTitle;
    std::vector<base_question*> questions;
    int roundScore;
    int currentStreak;
    int bestStreak;
    int correctCount;
    virtual int calculatePoints(bool isCorrect, int streak);
    virtual void displayRoundBanner(std::ostream& out) const;
    virtual void displayQuestionResult(bool isCorrect, int pointsEarned, std::ostream& out) const;
    static size_t promptUserChoice(size_t maxOptions, std::istream& in, std::ostream& out);
    static bool tryParseChoice(const std::string& token, size_t maxOptions, size_t& outIdx);
    virtual void executeRound(std::istream& in, std::ostream& out, int startingStreak);

public:
    base_round(std::string title, std::vector<base_question*> qList);
    virtual ~base_round() = default;
    void playRound(std::istream& in = std::cin, std::ostream& out = std::cout, int startingStreak = 0);
    std::string getRoundTitle() const;
    int getRoundScore() const;
    int getCurrentStreak() const;
    int getBestStreak() const;
    int getCorrectCount() const;
    size_t getQuestionCount() const;
};

#endif // BASE_ROUND_H
