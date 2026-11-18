/**
- Grant Aubry

- Trivia Final

- 11/6/26

 */

#include "chaos_round.h"
#include <iomanip>
#include <utility>

constexpr int MIN_CHAOS_REWARD = 50;
constexpr int MAX_CHAOS_REWARD = 250;
constexpr int MIN_CHAOS_PENALTY = 50;
constexpr int MAX_CHAOS_PENALTY = 150;
constexpr int CHAOS_STREAK_BONUS = 10;
constexpr double PERCENT_MULTIPLIER = 100.0;

chaos_round::chaos_round(std::vector<base_question*> qList, std::mt19937& randomEngine)
    : base_round("Chaos", std::move(qList)),
      rng(randomEngine) {}

int chaos_round::calculatePoints(const bool isCorrect, const int streak) {
    if (isCorrect) {
        std::uniform_int_distribution<int> rewardDist(MIN_CHAOS_REWARD, MAX_CHAOS_REWARD);
        return rewardDist(rng) + (streak * CHAOS_STREAK_BONUS);
    }
    std::uniform_int_distribution<int> penaltyDist(MIN_CHAOS_PENALTY, MAX_CHAOS_PENALTY);
    return -penaltyDist(rng);
}

void chaos_round::displayRoundSummary(std::ostream& out) const {
    size_t total = questions.size();
    double accuracy = (total > 0) ? (static_cast<double>(correctCount) / total) * PERCENT_MULTIPLIER : 0.0;
    out << "----------------------------------------\n";
    out << "  ROUND SUMMARY (Chaos)\n";
    out << "  Net Score:   " << roundScore << " pts\n";
    out << "  Accuracy:    " << correctCount << "/" << total
        << " (" << std::fixed << std::setprecision(1) << accuracy << "%)\n";
    out << "  Best Streak: " << bestStreak << "\n";
    out << "----------------------------------------\n";
}

void chaos_round::executeRound(std::istream& in, std::ostream& out, const int startingStreak, const int scoreMultiplier, int* remainingLives) {
    base_round::executeRound(in, out, startingStreak, scoreMultiplier, remainingLives);
    displayRoundSummary(out);
}