#ifndef MENU_H
#define MENU_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;


class Menu {
private:
    string name;
    string description;
    vector<Menu*> subMenu;
    int action;
public:
    Menu();
    Menu(string name, string desc, int action =-1);
    ~Menu();

    string getName();
    void setName(string n);

    string getDescription();
    void setDescription(string d);

    void displayMenu();
    void addSubMenu(Menu* m);
    Menu* getSubMenu(int index);

    int promptOption(); //ask user to input the option

    int getAction();
    void setAction(int a);
};
#endif 