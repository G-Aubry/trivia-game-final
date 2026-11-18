/**
- Grant Aubry
- Trivia Final
- 11/16/26
 */

#include "base_game_mode.h"
#include <algorithm>
#include <iomanip>
#include <utility>

constexpr double PERCENT_MULTIPLIER = 100.0;

base_game_mode::base_game_mode(std::string title, const question_bank& qBank, std::mt19937& randomEngine)
    : modeTitle(std::move(title)),
      bank(qBank),
      rng(randomEngine),
      totalScore(0),
      activeStreak(0),
      overallBestStreak(0),
      totalCorrect(0),
      totalQuestionsAnswered(0) {}

void base_game_mode::recordRoundStats(const base_round& round) {
    totalScore += round.getRoundScore();
    activeStreak = round.getCurrentStreak();
    overallBestStreak = std::max(overallBestStreak, round.getBestStreak());
    totalCorrect += round.getCorrectCount();
    totalQuestionsAnswered += static_cast<int>(round.getQuestionCount());
}

void base_game_mode::displayModeBanner(std::ostream& out) const {
    out << "\n============================================\n";
    out << "  TERMINAL TRIVIA // " << modeTitle << "\n";
    out << "============================================\n";
}

void base_game_mode::displayFinalSummary(std::ostream& out) const {
    double accuracy = (totalQuestionsAnswered > 0)
        ? (static_cast<double>(totalCorrect) / totalQuestionsAnswered) * PERCENT_MULTIPLIER
        : 0.0;
    out << "\n============================================\n";
    out << "  FINAL STATS: " << modeTitle << "\n";
    out << "  Total Score:   " << totalScore << " pts\n";
    out << "  Accuracy:      " << totalCorrect << "/" << totalQuestionsAnswered
        << " (" << std::fixed << std::setprecision(1) << accuracy << "%)\n";
    out << "  Best Streak:   " << overallBestStreak << "\n";
    out << "============================================\n";
}

void base_game_mode::startGame(std::istream& in, std::ostream& out) {
    displayModeBanner(out);
    executeGame(in, out);
    displayFinalSummary(out);
}

std::string base_game_mode::getModeTitle() const {
    return modeTitle;
}

int base_game_mode::getTotalScore() const {
    return totalScore;
}

int base_game_mode::getActiveStreak() const {
    return activeStreak;
}

int base_game_mode::getOverallBestStreak() const {
    return overallBestStreak;
}

int base_game_mode::getTotalCorrect() const {
    return totalCorrect;
}

int base_game_mode::getTotalQuestionsAnswered() const {
    return totalQuestionsAnswered;
}
