#include <iostream>
#include "Menu.cpp"
#include "Game.cpp"
#include "Word.cpp"

using namespace std;

enum ACTION_TYPE {
    PLAY_GAME,
    EXIT_GAME,
    HINT_SETTING, 
    FAIL_SETTING,
    WORD_SETTING,
    ADD_WORD,
    RESET,
    DISPLAY_BANK


};
int main () {
    //create 3 words
    Word w[3] = {
        Word("hello", "similar to Hi"),
        Word("apple", "a red fruit"),
        Word("book", "something to read")
    };

    //create a game
    Game* currentGame = new Game();

    // add Book to wordBank
    for (int i = 0; i < 3; i++)
    {
        currentGame->addWord(w[i]);
    }

    currentGame->setWordLimit(3);
    currentGame->setHintLimit(2);
    currentGame->setFailLimit(3);

    //create a menu
    
    //main menu
    Menu *mainMenu = new Menu("Main Menu", "The game main menu");
        Menu *settingMenu = new Menu("Game Setting Menu", "The game setting menu");
        Menu *wordBankMenu = new Menu("Word Bank Menu", "The game Word Bank menu");
        Menu *playMenu = new Menu("Play game", "Start playing the game", PLAY_GAME);
        Menu *exitMenu = new Menu("Exit game", "Exit the game, good bye!", EXIT_GAME);

        mainMenu->addSubMenu(settingMenu);
        mainMenu->addSubMenu(wordBankMenu);
        mainMenu->addSubMenu(playMenu);
        mainMenu->addSubMenu(exitMenu);

    //setting menu
    Menu* setHint = new Menu("Hint Settings", "Set the maximum hints", HINT_SETTING);
    Menu* setFail = new Menu("Fail Settings", "Set the maximum fails", FAIL_SETTING);
    Menu* setWord = new Menu("Word Settings", "Set the number of words", WORD_SETTING);

    settingMenu->addSubMenu(setHint);
    settingMenu->addSubMenu(setFail);
    settingMenu->addSubMenu(setWord);

    //word bank menu
    Menu* addWord = new Menu("Add Word", "Add a new word to the word bank",ADD_WORD);
    Menu* reset = new Menu("Reset Word Bank", "Reset the word bank", RESET);
    Menu* displayWordBank = new Menu("Display Word Bank","Display the current word bank",DISPLAY_BANK);

    wordBankMenu->addSubMenu(addWord);
    wordBankMenu->addSubMenu(reset);
    wordBankMenu->addSubMenu(displayWordBank);
    
    
    Menu* currentMenu = mainMenu;
    while (true) {
        currentMenu->displayMenu();
        int opt = currentMenu->promptOption();
        currentMenu = currentMenu->getSubMenu(opt);

        switch(currentMenu->getAction()){
            case -1:
                break;
            case PLAY_GAME:
                currentMenu = playMenu;
                currentMenu -> displayMenu();
                currentGame -> playGame();
                opt = currentMenu->promptOption();
                currentMenu = currentMenu->getSubMenu(opt);
                break;
            case HINT_SETTING:
                int hintLimit;
                currentMenu = setHint;
                currentMenu->displayMenu();
                cout << "Enter the maximum number of hints: ";
                cin >> hintLimit;
                currentGame->setHintLimit(hintLimit);
                opt = currentMenu->promptOption();
                currentMenu = currentMenu->getSubMenu(opt);
                break;
            case FAIL_SETTING:
                int failLimit;
                cout << "Enter the maximum number of fails: ";
                cin >> failLimit;
                currentGame->setFailLimit(failLimit);
                break;
            case WORD_SETTING:
                int wordLimit;
                cout << "Enter the maximum number of words: ";
                cin >> wordLimit;
                currentGame->setWordLimit(wordLimit);
                break;
            case ADD_WORD:
            {
                cin.ignore();
                string word,hint;
                cout << "Enter new word: ";
                getline(cin, word);
                cout << "Enter a hint for that word: ";
                getline(cin, hint);
                Word w(word, hint);
                currentGame->addWord(w);
                break;
            }
            case DISPLAY_BANK:
                currentMenu = displayWordBank;
                currentMenu->displayMenu();
                currentGame->displayWordBank();
                opt = currentMenu->promptOption();
                currentMenu = currentMenu->getSubMenu(opt);
                break;
            case RESET:
                currentGame->resetWordBank();
                break;
            case EXIT_GAME:
                cout << "Exiting the game" << endl;
                exit(0);
            default:
                cout << "Invalid option selected." << endl;
                break;
        }
    }
    return 0;
}