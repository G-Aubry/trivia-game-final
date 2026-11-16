cmake_minimum_required(VERSION 3.16)
project(trivia-game-final LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(TRIVIA_FILES
        questions/base_question.cpp
        questions/base_question.h
        questions/multiple_choice.cpp
        questions/multiple_choice.h
        questions/true_false.cpp
        questions/true_false.h
        questions/question_bank.cpp
        questions/question_bank.h
        rounds/base_round.cpp
        rounds/base_round.h
        rounds/classic_round.cpp
        rounds/classic_round.h
        rounds/chaos_round.cpp
        rounds/chaos_round.h
)
set(TEST_SOURCES
        tests/test_runner.cpp
        tests/test_questions.cpp
        tests/test_questions.h
        tests/test_rounds.cpp
        tests/test_rounds.h
)
add_executable(trivia main.cpp ${TRIVIA_FILES})
add_executable(trivia_tests ${TEST_SOURCES} ${TRIVIA_FILES})