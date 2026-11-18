/**
 * Grant Aubry
 * Trivia Final
 * 11/3/26
 */

#include "game_modes/base_game_mode.h"
#include "game_modes/chaos_mode.h"
#include "game_modes/classic_mode.h"
#include "questions/question_bank.h"
#include <iostream>
#include <memory>
#include <random>
#include <string>

constexpr int EXIT_CHOICE = 5;

static bool loadQuestionDatabase(question_bank& bank, std::mt19937& rng) {
    return bank.loadFromFile("../question_contents/questions.txt", rng);
}

static void displayMainMenu() {
    std::cout << "\n============================================\n";
    std::cout << "              TERMINAL TRIVIA              \n";
    std::cout << "============================================\n";
    std::cout << "  1. Classic Mode  (5 Rounds x 10 Questions)\n";
    std::cout << "  2. Quick Classic (3 Rounds x 5 Questions)\n";
    std::cout << "  3. Chaos Mode    (5 Rounds x 10 Questions)\n";
    std::cout << "  4. Quick Chaos   (3 Rounds x 5 Questions)\n";
    std::cout << "  5. Exit\n";
    std::cout << "Select an option (1-5): ";
}

static int promptMenuChoice() {
    int choice = 0;
    std::string token;
    while (choice < 1 || choice > EXIT_CHOICE) {
        displayMainMenu();
        if (!(std::cin >> token)) {
            return EXIT_CHOICE;
        }
        if (token.size() == 1 && token[0] >= '1' && token[0] <= '5') {
            choice = token[0] - '0';
        } else {
            std::cout << "Invalid selection. Please enter a number from 1 to 5.\n";
        }
    }
    return choice;
}

static std::unique_ptr<base_game_mode> createSelectedMode(const int choice, const question_bank& bank, std::mt19937& rng) {
    if (choice == 1) {
        return std::make_unique<classic_mode>(bank, rng);
    }
    if (choice == 2) {
        return std::make_unique<classic_mode>(bank, rng, 3, 5, "Quick Classic");
    }
    if (choice == 3) {
        return std::make_unique<chaos_mode>(bank, rng);
    }
    return std::make_unique<chaos_mode>(bank, rng, 3, 5, "Quick Chaos");
}

int main() {
    std::random_device rd;
    std::mt19937 rng(rd());
    question_bank bank;
    if (!loadQuestionDatabase(bank, rng)) {
        std::cerr << "Error: Could not locate question bank file.\n";
        return 1;
    }
    int choice = 0;
    while ((choice = promptMenuChoice()) != EXIT_CHOICE) {
        auto mode = createSelectedMode(choice, bank, rng);
        mode->startGame();
    }
    std::cout << "\nTerminal Trivia Terminated!\n";
    return 0;
}
