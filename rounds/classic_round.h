/**
- Grant Aubry
- Trivia Final
- 11/13/26
 */

#ifndef CLASSIC_ROUND_H
#define CLASSIC_ROUND_H

#include "base_round.h"
#include <iostream>
#include <string>
#include <vector>

class classic_round : public base_round {
private:
    std::string category;

    void displayRoundSummary(std::ostream& out) const;

protected:
    void executeRound(std::istream& in, std::ostream& out, int startingStreak) override;

public:
    classic_round(std::string cat, std::vector<base_question*> qList);
    explicit classic_round(std::vector<base_question*> qList);
    ~classic_round() override = default;

    std::string getCategory() const;
};

#endif // CLASSIC_ROUND_H
