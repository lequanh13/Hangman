#include "Word.h"

Word::Word()
{
    text = "default text";
    hint = "default hint";
    displayText = string(text.length(), '_');
}

Word::Word(string t, string h)
{
    setText(t);
    this->hint = h;
}

Word::~Word(){}

void Word::displayWord()
{
    cout << "The word has total " << text.length() << " characters!" << endl;
    cout << getDisplayText() << endl;
}

string Word::getHint()
{
    return this->hint;
}

void Word::setHint(string h)
{
    this->hint = h;
}

string Word::getText()
{
    return this->text;
}

void Word::setText(string t)
{
    this->text = t;
    displayText = string(text.length(), '_');

}

string Word::getDisplayText()
{
    return displayText;
}

int Word::checkGuess(char n, bool& usedHint)
{
    int occurrence = 0;
    for (int  i = 0; i < text.length(); i++) {
        if (text[i] == n) {
            occurrence++;
            displayText[i] = n;
        }
    }
    if (occurrence == 0  && !usedHint){
        usedHint = true;
    }
    return occurrence;
}


