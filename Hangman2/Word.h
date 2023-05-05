#ifndef WORD_H
#define WORD_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Word {
    private:
        string text;
        string hint;
        string displayText;
    public:
        Word();
        Word(string t, string h);
        ~Word();
        void displayWord();

        string getHint();
        void setHint(string h);

        string getText();
        void setText(string t);

        string getDisplayText();
        void setDisplayTest(string dt);

        int checkGuess(char n, bool& usedHint);


};
#endif