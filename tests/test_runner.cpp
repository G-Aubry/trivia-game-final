/**
- Grant Aubry
- Trivia Final
- 11/11/26
 */

#include "test_questions.h"
#include <iostream>
#include <random>

#include "test_rounds.h"

int main() {
    std::cout << "===========================================\n";
    std::cout << "      TRIVIA ENGINE TEST SUITE RUNNER      \n";
    std::cout << "===========================================\n";

    std::mt19937 rng(1337);

    // 1. Questions and Bank Suite
    runQuestionTests(rng);

    // 2. Future: runRoundTests(rng);
    runRoundTests(rng);
    // 3. Future: runGameModeTests(rng);

    std::cout << "\nAll test suites passed with zero errors!\n";
    return 0;
}
