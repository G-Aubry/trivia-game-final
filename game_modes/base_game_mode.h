/**
- Grant Aubry
- Trivia Final
- 11/16/26
 */

#ifndef BASE_GAME_MODE_H
#define BASE_GAME_MODE_H

#include "../questions/question_bank.h"
#include "../rounds/base_round.h"
#include <iostream>
#include <random>
#include <string>

class base_game_mode {
protected:
    std::string modeTitle;
    const question_bank& bank;
    std::mt19937& rng;
    int totalScore;
    int activeStreak;
    int overallBestStreak;
    int totalCorrect;
    int totalQuestionsAnswered;

    void recordRoundStats(const base_round& round);
    virtual void displayModeBanner(std::ostream& out) const;
    virtual void displayFinalSummary(std::ostream& out) const;
    virtual void executeGame(std::istream& in, std::ostream& out) = 0;

public:
    base_game_mode(std::string title, const question_bank& qBank, std::mt19937& randomEngine);
    virtual ~base_game_mode() = default;
    void startGame(std::istream& in = std::cin, std::ostream& out = std::cout);
    std::string getModeTitle() const;
    int getTotalScore() const;
    int getActiveStreak() const;
    int getOverallBestStreak() const;
    int getTotalCorrect() const;
    int getTotalQuestionsAnswered() const;
};

#endif // BASE_GAME_MODE_H
