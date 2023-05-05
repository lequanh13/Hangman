#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>
#include "Word.h"
#include "Menu.h"
using namespace std;

class Game {
    private:
        int failCount, hintCount, wordCount;
        int failLimit, hintLimit, wordLimit;
        vector<Word> wordBank;
        bool usedHint;
    public:
        Game();
        ~Game();

        int getFailLimit();
        void setFailLimit(int fl);

        int getHintLimit();
        void setHintLimit(int hl);

        int getWordLimit();
        void setWordLimit(int wl);

        void addWord(Word w);
        void resetWordBank();
        void shuffleWordBank();
        Word getOneWord(int index);

        void displayWordBank();

        void playGame();

};
#endif