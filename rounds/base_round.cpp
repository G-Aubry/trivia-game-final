/**
- Grant Aubry
- Trivia Final
- 11/11/26
 */

#include "base_round.h"
#include <limits>
#include <utility>

constexpr int BASE_QUESTION_POINTS = 100;
constexpr int STREAK_BONUS_MULTIPLIER = 10;

base_round::base_round(std::string title, std::vector<base_question*> qList)
    : roundTitle(std::move(title)),
      questions(std::move(qList)),
      roundScore(0),
      currentStreak(0),
      bestStreak(0),
      correctCount(0) {}

int base_round::calculatePoints(const bool isCorrect, const int streak) {
    if (!isCorrect) {
        return 0;
    }
    return BASE_QUESTION_POINTS + (streak * STREAK_BONUS_MULTIPLIER);
}

void base_round::displayRoundBanner(std::ostream& out) const {
    out << "\n========================================\n";
    out << "  ROUND: " << roundTitle << "\n";
    out << "========================================\n";
}

void base_round::displayQuestionResult(const bool isCorrect, const int pointsEarned, std::ostream& out) const {
    if (isCorrect) {
        out << "Correct! +" << pointsEarned << " pts (Streak: " << currentStreak << ")\n\n";
    } else if (pointsEarned < 0) {
        out << "Incorrect! " << pointsEarned << " pts. (Streak: 0)\n\n";
    } else {
        out << "Incorrect! (Streak: 0)\n\n";
    }
}

bool base_round::tryParseChoice(const std::string& token, const size_t maxOptions, size_t& outIdx) {
    if (token.size() != 1) {
        return false;
    }
    auto upper = static_cast<unsigned char>(std::toupper(static_cast<unsigned char>(token[0])));
    outIdx = static_cast<size_t>(upper - 'A');
    return upper >= 'A' && outIdx < maxOptions;
}

size_t base_round::promptUserChoice(const size_t maxOptions, std::istream& in, std::ostream& out) {
    size_t selection = 0;
    std::string token;
    bool valid = false;
    while (!valid && (out << "Enter Your Letter Choice: ") && (in >> token)) {
        valid = tryParseChoice(token, maxOptions, selection);
        if (!valid) {
            out << "Invalid choice. Please enter a single valid option letter.\n";
        }
    }
    return selection;
}
void base_round::playRound(std::istream& in, std::ostream& out, const int startingStreak) {
    executeRound(in, out, startingStreak);
}
void base_round::executeRound(std::istream& in, std::ostream& out, const int startingStreak) {
    currentStreak = startingStreak;
    displayRoundBanner(out);
    for (size_t i = 0; i < questions.size(); ++i) {
        out << "Question " << (i + 1) << " of " << questions.size() << ":\n";
        questions[i]->displayQuestion();
        size_t choice = promptUserChoice(questions[i]->getOptionCount(), in, out);
        bool isCorrect = questions[i]->isCorrect(choice);
        currentStreak = isCorrect ? (currentStreak + 1) : 0;
        bestStreak = std::max(bestStreak, currentStreak);
        correctCount += isCorrect ? 1 : 0;
        int pts = calculatePoints(isCorrect, currentStreak);
        roundScore += pts;
        displayQuestionResult(isCorrect, pts, out);
    }
}

std::string base_round::getRoundTitle() const {
    return roundTitle;
}

int base_round::getRoundScore() const {
    return roundScore;
}

int base_round::getCurrentStreak() const {
    return currentStreak;
}

int base_round::getBestStreak() const {
    return bestStreak;
}

int base_round::getCorrectCount() const {
    return correctCount;
}

size_t base_round::getQuestionCount() const {
    return questions.size();
}