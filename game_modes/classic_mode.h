/**
- Grant Aubry
- Trivia Final
- 11/18/26
 */

#ifndef STANDARD_MODE_H
#define STANDARD_MODE_H

#include "base_game_mode.h"
#include <iostream>
#include <random>
#include <string>
#include <vector>

class classic_mode : public base_game_mode {
private:
    size_t numRounds;
    size_t questionsPerRound;

    std::vector<std::string> selectRoundCategories() const;
    void playSingleCategoryRound(const std::string& category, int multiplier,
                                 std::istream& in, std::ostream& out);

protected:
    void executeGame(std::istream& in, std::ostream& out) override;

public:
    classic_mode(const question_bank& qBank, std::mt19937& randomEngine,
                  size_t rounds = 5, size_t qPerRound = 10,
                  std::string title = "Classic Mode");
    ~classic_mode() override = default;
};

#endif // STANDARD_MODE_H