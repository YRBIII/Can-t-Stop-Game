//
// Project Folder: Player Implementation
// File: Player.cpp
//

#include "Player.hpp"

Player::Player(const string &name, EColor color)
    : playerName(name), playerColor(color) {}

Player::~Player() {}

EColor Player::color() const { return playerColor; }            // Returns players assigned colors
int Player::score() const { return playerScore; }               // Returns players current score
string Player::getName() const { return playerName; }   // Returns players name

// Adds a column to the scoreboard and updates the score
bool Player::wonColumn(int colNum) {
    if (capturedCount >= 3) {
        cout << "Player " << playerName << " already captured 3 columns. No more can be captured." << endl;
        return false;
    }

    cout << "Player " << playerName << " captured Column " << colNum << "!" << endl;

    scoreboard[capturedCount] = colNum;
    capturedCount++;
    playerScore = capturedCount;
    return (capturedCount == 3);
}



// Print player details
void Player::print(ostream& os) const {
    os << getName() << " (" << getColor(color())
       << ") | Score: " << score()
       << " | Columns Won: ";

    for (int i = 0; i < capturedCount; i++) {
        os << scoreboard[i];
        if (i < capturedCount - 1) os << ", ";
    }
    if (capturedCount == 0) os << "None";
    os << endl;
}


// Overloaded << operator
ostream& operator<<(ostream& os, const Player& player) {
    player.print(os);
    return os;
}
