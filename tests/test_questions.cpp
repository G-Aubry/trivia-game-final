/**
- Grant Aubry
- Trivia Final
- 11/11/26
 */

#include "test_questions.h"
#include "../questions/base_question.h"
#include "../questions/multiple_choice.h"
#include "../questions/true_false.h"
#include "../questions/question_bank.h"
#include <iostream>
#include <cassert>
#include <vector>

static void testMultipleChoice(std::mt19937& rng) {
    std::cout << "  [TEST] Multiple Choice Question...";
    std::vector<std::string> opts = {"1969", "1965", "1968", "1972"};
    multiple_choice mc("History", "Apollo 11 year?", opts, "1969", rng);

    assert(mc.getType() == "MC");
    assert(mc.getCategory() == "History");
    assert(mc.getOptionCount() == 4);

    size_t correctCount = 0;
    for (size_t i = 0; i < mc.getOptionCount(); ++i) {
        if (mc.isCorrect(i)) {
            correctCount++;
        }
    }
    assert(correctCount == 1);
    assert(!mc.isCorrect(99));
    std::cout << " PASSED\n";
}

static void testTrueFalse() {
    std::cout << "  [TEST] True/False Question...";
    true_false tf("Science", "The earth is flat.", "False");

    assert(tf.getType() == "TF");
    assert(tf.getCategory() == "Science");
    assert(tf.getOptionCount() == 2);
    assert(tf.getOptions()[0] == "True");
    assert(tf.getOptions()[1] == "False");
    assert(!tf.isCorrect(0));
    assert(tf.isCorrect(1));
    assert(!tf.isCorrect(2));
    std::cout << " PASSED\n";
}

static void testQuestionBank(std::mt19937& rng) {
    std::cout << "  [TEST] Question Bank Loading & Filtering...";
    question_bank bank;
    const bool loaded = bank.loadFromFile("../tests/test_set.txt", rng);
    assert(loaded);

    assert(bank.getCategories().size() == 5);
    assert(bank.getCategoryQuestionCount("History") == 3);

    auto subset = bank.getQuestionsByCategory("History", 2, rng);
    assert(subset.size() == 2);

    auto randomSample = bank.getRandomQuestions(5, rng);
    assert(randomSample.size() == 5);
    std::cout << " PASSED\n";
}

void runQuestionTests(std::mt19937& rng) {
    std::cout << "\n--- Starting Question & Bank Test Suite ---\n";
    testMultipleChoice(rng);
    testTrueFalse();
    testQuestionBank(rng);
    std::cout << "--- Question & Bank Test Suite Completed Successfully ---\n";
}
