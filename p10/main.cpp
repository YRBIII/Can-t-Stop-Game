//
// Project Folder: Program Entry
// Authors: Anthony Ciavarella and Yung Brinney
// File: main.cpp
//

#include "Game.hpp"

int main() {
    srand(time(nullptr));
    banner();

    char modeChoice;
    cout << "Select Dice Mode:\nF - Fake Dice\nC - CantStop\n> ";
    cin >> modeChoice;
    modeChoice = toupper(modeChoice);

    Game game(modeChoice == 'F');
    game.play();

    bye();
    return 0;
}
