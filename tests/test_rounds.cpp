/**
- Grant Aubry
- Trivia Final
- 11/13/26
 */

#include "test_rounds.h"
#include "../questions/true_false.h"
#include "../rounds/classic_round.h"
#include "../rounds/chaos_round.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

static void testClassicScoringAndInput() {
    std::cout << "  [TEST] Classic Round Scoring & Input Validation...";
    true_false q1("Science", "Water boils at 100C.", "True");   // Answer: A
    true_false q2("Science", "The sun is cold.", "False");      // Answer: B
    true_false q3("Science", "Humans need oxygen.", "True");    // Answer: A
    classic_round round("Science", {&q1, &q2, &q3});

    // Inputs: valid 'a', invalid 'Apple' & 'Z' before valid 'b', then lowercase 'a'
    std::istringstream fakeIn("a\nApple\nZ\nb\na\n");
    std::ostringstream fakeOut;
    round.playRound(fakeIn, fakeOut);

    // Points: (100 + 10) + (100 + 20) + (100 + 30) = 360
    assert(round.getCategory() == "Science");
    assert(round.getRoundScore() == 360);
    assert(round.getBestStreak() == 3);
    assert(round.getCorrectCount() == 3);
    std::cout << " PASSED\n";
}

static void testCarryOverStreakAndRandomClassic() {
    std::cout << "  [TEST] Cross-Round Streak & Random Classic...";
    true_false q1("History", "1969 was the moon landing.", "True"); // Answer: A
    true_false q2("History", "Rome is in France.", "False");        // Answer: B
    classic_round round({&q1, &q2});

    std::istringstream fakeIn("A\nA\n"); // Correct (streak 4), then Wrong (reset)
    std::ostringstream fakeOut;
    round.playRound(fakeIn, fakeOut, 3); // Carry over active streak of 3

    // Q1 scores 100 + (4 * 10) = 140; Q2 scores 0
    assert(round.getCategory() == "Random");
    assert(round.getRoundScore() == 140);
    assert(round.getBestStreak() == 4);
    assert(round.getCurrentStreak() == 0);
    std::cout << " PASSED\n";
}

static void testChaosRoundNegativeAndRandom(std::mt19937& rng) {
    std::cout << "  [TEST] Chaos Round Random Points & Negative Score...";
    true_false q1("Sports", "A touchdown is 6 points.", "True"); // Answer: A
    true_false q2("Sports", "A marathon is 5 miles.", "False");   // Answer: B
    chaos_round round({&q1, &q2}, rng);

    std::istringstream fakeIn("B\nA\n"); // Both wrong -> two random penalties
    std::ostringstream fakeOut;
    round.playRound(fakeIn, fakeOut);

    assert(round.getRoundScore() <= -100 && round.getRoundScore() >= -300);
    assert(round.getCorrectCount() == 0);
    assert(round.getCurrentStreak() == 0);
    std::cout << " PASSED\n";
}

void runRoundTests(std::mt19937& rng) {
    std::cout << "\n--- Starting Round Test Suite ---\n";
    testClassicScoringAndInput();
    testCarryOverStreakAndRandomClassic();
    testChaosRoundNegativeAndRandom(rng);
    std::cout << "--- Round Test Suite Completed Successfully ---\n";
}
