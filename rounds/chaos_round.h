/**
- Grant Aubry
- Trivia Final
- 11/13/26

 */

#ifndef CHAOS_ROUND_H
#define CHAOS_ROUND_H

#include "base_round.h"
#include <iostream>
#include <random>
#include <vector>

class chaos_round : public base_round {
private:
    std::mt19937& rng;
    void displayRoundSummary(std::ostream& out) const;
protected:
    int calculatePoints(bool isCorrect, int streak) override;
    void executeRound(std::istream& in, std::ostream& out, int startingStreak) override;
public:
    chaos_round(std::vector<base_question*> qList, std::mt19937& randomEngine);
    ~chaos_round() override = default;
};

#endif // CHAOS_ROUND_H
