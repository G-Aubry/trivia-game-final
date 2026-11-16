/**
 * Grant Aubry
 * Trivia Final
 * 11/3/26
 */
#include <string>
#include <iostream>
#include <vector>
#include "questions/multiple_choice.h"
#include "questions/true_false.h"
#include "rounds/chaos_round.h"
using namespace std;

int main() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::vector<std::string> opts = {"1969", "1965", "1968", "1972"};
    multiple_choice mc("History", "Apollo 11 year?", opts, "1969", rng);
    true_false tf("History", "Lincoln was #16?", "True");
    true_false tf2("History", "Lincoln was #17?", "False");
    true_false tf3("Literature", "Dante's Inferno was part of Divine Comedy?", "True");
    true_false tf4("Sport", "Seahawks won SuperBowl 60?", "True");
    vector<base_question> quests;
    chaos_round chaos({&mc, &tf, &tf2, &tf3, &tf4}, rng);
    chaos.playRound(cin, cout);
    return 0;
}
