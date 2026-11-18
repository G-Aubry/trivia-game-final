/**
- Grant Aubry
- Trivia Final
- 11/11/26
 */

#include "base_round.h"
#include <algorithm>
#include <cctype>
#include <utility>

constexpr int BASE_QUESTION_POINTS = 100;
constexpr int STREAK_BONUS_MULTIPLIER = 10;

base_round::base_round(std::string title, std::vector<base_question*> qList)
    : roundTitle{std::move(title)}, questions{std::move(qList)}, roundScore{0}, currentStreak{0},
      bestStreak{0}, correctCount{0}, questionsAttempted{0} {}

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

void base_round::displayQuestionResult(const bool isCorrect, const int pointsEarned,
                                       const int* remainingLives, std::ostream& out) const {
    if (isCorrect) {
        out << "Correct! +" << pointsEarned << " pts (Streak: " << currentStreak << ")\n";
    } else if (pointsEarned < 0) {
        out << "Incorrect! " << pointsEarned << " pts. (Streak: 0)\n";
    } else {
        out << "Incorrect! (Streak: 0)\n";
    }
    if (remainingLives != nullptr) {
        out << "Lives Remaining: " << *remainingLives << "\n";
    }
    out << "\n";
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

void base_round::playRound(std::istream& in, std::ostream& out, const int startingStreak, const int scoreMultiplier, int* remainingLives) {
    executeRound(in, out, startingStreak, scoreMultiplier, remainingLives);
}

void base_round::processQuestion(const size_t index, std::istream& in, std::ostream& out, const int scoreMultiplier, int* remainingLives) {
    out << "Question " << (index + 1) << " of " << questions.size() << ":";
    questions[index]->displayQuestion();
    bool isCorrect = questions[index]->isCorrect(promptUserChoice(questions[index]->getOptionCount(), in, out));
    ++questionsAttempted;
    currentStreak = isCorrect ? (currentStreak + 1) : 0;
    bestStreak = std::max(bestStreak, currentStreak);
    correctCount += isCorrect ? 1 : 0;
    if (!isCorrect && remainingLives != nullptr) {
        --(*remainingLives);
    }
    int pts = calculatePoints(isCorrect, currentStreak) * (isCorrect ? scoreMultiplier : 1);
    roundScore += pts;
    displayQuestionResult(isCorrect, pts, remainingLives, out);
}

void base_round::executeRound(std::istream& in, std::ostream& out, const int startingStreak, const int scoreMultiplier, int* remainingLives) {
    currentStreak = startingStreak;
    displayRoundBanner(out);
    for (size_t i = 0; i < questions.size() && (remainingLives == nullptr || *remainingLives > 0); ++i) {
        processQuestion(i, in, out, scoreMultiplier, remainingLives);
    }
}

int base_round::getQuestionsAttempted() const {
    return questionsAttempted;
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
