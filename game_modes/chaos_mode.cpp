/**
- Grant Aubry
- Trivia Final
- 11/18/26
 */

#include "chaos_mode.h"
#include "../rounds/chaos_round.h"
#include <algorithm>
#include <utility>

constexpr int ROUND_MULTIPLIER_STEP = 2;

chaos_mode::chaos_mode(const question_bank& qBank, std::mt19937& randomEngine,
                       const size_t rounds, const size_t qPerRound, std::string title)
    : base_game_mode(std::move(title), qBank, randomEngine),
      numRounds(rounds),
      questionsPerRound(qPerRound) {}

void chaos_mode::playChaosRoundSlice(const std::vector<base_question*>& pool, const size_t startIdx,
                                     const size_t count, const int multiplier,
                                     std::istream& in, std::ostream& out) {
    auto first = pool.begin() + static_cast<std::ptrdiff_t>(startIdx);
    auto last = first + static_cast<std::ptrdiff_t>(count);
    std::vector<base_question*> slice(first, last);
    chaos_round round(std::move(slice), rng);
    round.playRound(in, out, activeStreak, multiplier);
    recordRoundStats(round);
}

void chaos_mode::executeGame(std::istream& in, std::ostream& out) {
    std::vector<base_question*> pool = bank.getRandomQuestions(numRounds * questionsPerRound, rng);
    size_t actualRounds = (questionsPerRound > 0) ? (pool.size() / questionsPerRound) : 0;
    for (size_t i = 0; i < actualRounds; ++i) {
        int multiplier = 1 + static_cast<int>(i / ROUND_MULTIPLIER_STEP);
        out << "\n>>> CHAOS ROUND " << (i + 1) << " OF " << actualRounds
            << " (" << multiplier << "x SCORE MULTIPLIER) <<<\n";
        playChaosRoundSlice(pool, i * questionsPerRound, questionsPerRound, multiplier, in, out);
    }
}