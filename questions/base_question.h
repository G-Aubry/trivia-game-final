/**
* Grant Aubry
 * Trivia Final
 * 11/5/26
 */
#ifndef BASE_QUESTION_H
#define BASE_QUESTION_H

#include <string>
#include <vector>

class base_question {
protected:
    std::string category;
    std::string questionText;
    std::vector<std::string> options;
    std::string correctAnswer;

public:
    base_question(std::string cat, std::string text,
                  std::vector<std::string> opts, std::string ans);
    virtual ~base_question() = default;

    /**
     * Formats the Question and Options
     */
    virtual void displayQuestion() const;
    /**
     * Determines whether the user was right
     * @param chosenIndex index of the user's selection
     * @return whether the user's slection was correct
     */
    virtual bool isCorrect(size_t chosenIndex) const;
    std::string getCategory() const;
    std::string getQuestion() const;
    std::string getAnswer() const;
    const std::vector<std::string>& getOptions() const;
    size_t getOptionCount() const;
    virtual std::string getType() const = 0;
};

#endif // BASE_QUESTION_H