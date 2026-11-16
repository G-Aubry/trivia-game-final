/**
- Grant Aubry

- Trivia Final

- 11/6/26

 */

#include "classic_round.h"
#include <iomanip>
#include <utility>

constexpr double PERCENT_MULTIPLIER = 100.0;

classic_round::classic_round(std::string cat, std::vector<base_question*> qList)
    : base_round(cat, std::move(qList)),
      category(std::move(cat)) {}

classic_round::classic_round(std::vector<base_question*> qList)
    : classic_round("Random", std::move(qList)) {}

void classic_round::displayRoundSummary(std::ostream& out) const {
    size_t total = questions.size();
    double accuracy = (total > 0) ? (static_cast<double>(correctCount) / total) * PERCENT_MULTIPLIER : 0.0;
    out << "----------------------------------------\n";
    out << "  ROUND SUMMARY (" << category << ")\n";
    out << "  Score:       " << roundScore << " pts\n";
    out << "  Accuracy:    " << correctCount << "/" << total
        << " (" << std::fixed << std::setprecision(1) << accuracy << "%)\n";
    out << "  Best Streak: " << bestStreak << "\n";
    out << "----------------------------------------\n";
}

void classic_round::executeRound(std::istream& in, std::ostream& out, const int startingStreak) {
    base_round::executeRound(in, out, startingStreak);
    displayRoundSummary(out);
}

std::string classic_round::getCategory() const {
    return category;
}
