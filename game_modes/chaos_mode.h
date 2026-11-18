/**
- Grant Aubry
- Trivia Final
- 11/18/26
 */

#ifndef CHAOS_MODE_H
#define CHAOS_MODE_H

#include "base_game_mode.h"
#include <iostream>
#include <random>
#include <string>
#include <vector>

class chaos_mode : public base_game_mode {
private:
    size_t numRounds;
    size_t questionsPerRound;

    void playChaosRoundSlice(const std::vector<base_question*>& pool, size_t startIdx,
                             size_t count, int multiplier, std::istream& in, std::ostream& out);

protected:
    void executeGame(std::istream& in, std::ostream& out) override;

public:
    chaos_mode(const question_bank& qBank, std::mt19937& randomEngine,
               size_t rounds = 5, size_t qPerRound = 10,
               std::string title = "Chaos Mode");
    ~chaos_mode() override = default;
};

#endif // CHAOS_MODE_H
