#include "Game.h"
#include <random>
#include <ctime>
#include <string>

Game::Game()
{
    failCount = hintCount = wordCount = 0;
    failLimit = hintLimit = wordLimit = 0;
    wordBank.clear();
}

Game::~Game()
{
}

int Game::getFailLimit()
{
    return this->failLimit;
}

void Game::setFailLimit(int fl)
{
    if (fl > 0) 
        failLimit = fl;
    else 
        cout << "Incorrect fail limit!" << endl;
}

int Game::getHintLimit()
{
    return this->hintLimit;
}

void Game::setHintLimit(int hl)
{
    if (hl > 0 && hl < wordLimit) 
        hintLimit = hl;
    else 
        cout << "Incorrect hint limit!" << endl;
}

int Game::getWordLimit()
{
    return this->wordLimit;
}

void Game::setWordLimit(int wl)
{
    if (wl > 1 && wl <= wordBank.size()) 
        wordLimit = wl;
    else 
        cout << "Incorrect word limit or empty word bank" << endl;
}

void Game::addWord(Word w)
{
    wordBank.push_back(w);
}

void Game::resetWordBank()
{
    wordBank.clear();
}

void Game::shuffleWordBank()
{
    srand((time(NULL)));
    int count = 0;
    while(true) {
        int index1 = rand() % wordBank.size();
        int index2 = rand() % wordBank.size();
        if (index1 == index2)
            continue;
        Word tmp = wordBank[index1];
        wordBank[index1] = wordBank[index2];
        wordBank[index2] = tmp;   
        count++;
        if (count > 10) break;
    }
    cout << "The Word Bank has been shuffled!" << endl;
}

Word Game::getOneWord(int index)
{
    return wordBank[index];
}

void Game::displayWordBank()
{
    if (!wordBank.empty())
    {
        cout << "-----------------" << endl;
        cout << "Word Bank: " << endl;
        for (int i = 0; i < wordBank.size(); i++) {
        cout << i + 1 << ". " << wordBank[i].getText() << endl;
        }
        cout << "-----------------" << endl;
        
    }
    else
        cout << "Empty word bank!" << endl;
}

void Game::playGame()
{
    shuffleWordBank();
    bool continueGame = true;
    while (continueGame) 
    {
        for (int i = 0; i < getWordLimit(); i++) {
            Word w = getOneWord(i);
            string hint = w.getHint();
            string text = w.getText();
            int failCount = 0;
            int hintCount = 0;
            bool guessed = false;
            usedHint = false;


            while (!guessed && failCount < getFailLimit()) {
                w.displayWord();
                cout << endl;
                cout << "Guess a letter (or type '?' for a hint): ";
                char guess;
                cin >> guess;

                if (guess == '?') {
                    if (hintCount < getHintLimit() && !usedHint) {
                        cout << "Hint: " << w.getHint() << endl;
                        hintCount++; 
                        usedHint = true;
                    }
                    else if (hintCount >= getHintLimit()) {
                        cout << "You have used up all your hints!" << endl;
                    }
                    else {
                        cout << "You have already used the hint for this word!" << endl;
                    }
                    continue;
                }
                int occurrence = w.checkGuess(guess, usedHint);
                if (occurrence == 0) {
                    cout << "Incorrect guess" << endl;
                    failCount++;
                    cout << "You have guessed " << failCount << " time(s) wrong!" << endl;
                    cout << "You only have " << getFailLimit() - failCount << " more guess(es)" << endl << endl;
                }
                else {
                    cout << "Correct guess! The letter " << guess << " appears " << occurrence << " time(s)." << endl;
                    if (w.getDisplayText() == text) {
                        cout << "You guessed the word: " << text << endl;
                        guessed = true;
                    }
                }
                if (!guessed && failCount == getFailLimit()) {
                    cout << "You failed to guess the word. The word was: " << text << endl;
                }
            }
            if (i < getWordLimit() - 1) {
                char playAgain;
                cout << "Would you like to play the next word? (y/n): ";
                cin >> playAgain;
                if (playAgain == 'n' || playAgain == 'N') {
                    continueGame = false;
                    break;
                }
            }
        }
        if (continueGame) {
            char playAgain;
            cout << "You have completed all the words. Would you like to play again? (y/n): ";
            cin >> playAgain;
            if (playAgain == 'n' || playAgain == 'N') {
                continueGame = false;
            }
        }
    }
}
