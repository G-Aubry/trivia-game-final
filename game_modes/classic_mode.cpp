/**
- Grant Aubry
- Trivia Final
- 11/18/26
 */

#include "classic_mode.h"
#include "../rounds/classic_round.h"
#include <algorithm>
#include <utility>

constexpr int DEFAULT_MULTIPLIER = 1;
constexpr int FINALE_MULTIPLIER = 2;

classic_mode::classic_mode(const question_bank& qBank, std::mt19937& randomEngine,
                             const size_t rounds, const size_t qPerRound, std::string title)
    : base_game_mode(std::move(title), qBank, randomEngine),
      numRounds(rounds),
      questionsPerRound(qPerRound) {}

std::vector<std::string> classic_mode::selectRoundCategories() const {
    std::vector<std::string> categories = bank.getCategories();
    std::shuffle(categories.begin(), categories.end(), rng);
    if (categories.size() > numRounds) {
        categories.resize(numRounds);
    }
    return categories;
}

void classic_mode::playSingleCategoryRound(const std::string& category, const int multiplier,
                                            std::istream& in, std::ostream& out) {
    auto qList = bank.getQuestionsByCategory(category, questionsPerRound, rng);
    classic_round round(category, std::move(qList));
    round.playRound(in, out, activeStreak, multiplier);
    recordRoundStats(round);
}

void classic_mode::executeGame(std::istream& in, std::ostream& out) {
    std::vector<std::string> chosenCategories = selectRoundCategories();
    size_t totalRounds = chosenCategories.size();
    for (size_t i = 0; i < totalRounds; ++i) {
        bool isFinale = (i + 1 == totalRounds) && (totalRounds > 1);
        int multiplier = isFinale ? FINALE_MULTIPLIER : DEFAULT_MULTIPLIER;
        if (isFinale) {
            out << "\n*** FINAL ROUND: DOUBLE POINTS ACTIVE! ***";
        }
        playSingleCategoryRound(chosenCategories[i], multiplier, in, out);
    }
}