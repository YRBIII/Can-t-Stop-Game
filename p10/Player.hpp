//
// Project Folder: Player Class
// Authors: Anthony Ciavarella and Yung Brinney
// File: Player.hpp
//

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "tools.hpp"
#include "Enums.hpp"

// -----------------------------------------------
// Class: Player
// Represents a player in the game, tracking name, color
// score and captured pieces.
// -----------------------------------------------
class Player {
private:
    string playerName;                 // Player's name
    EColor playerColor;                // Player's color
    int playerScore = 0;               // Current score
    int scoreboard[3] = {0, 0, 0};     // Stores columns won
    int capturedCount = 0;             // Number of captured columns

public:
    Player(const string& name, EColor color);
    ~Player();

    EColor color() const;             // Returns players color
    int score() const;                // Returns players current score
    string getName() const;           // Returns players name

    const vector<int> getScoreboard() const {
        return vector<int>(scoreboard, scoreboard + capturedCount);
    }
    int getCapturedCount() const { return capturedCount; } // Returns number of columns captured

    bool wonColumn(int colNum); // Adds column win and updates score
    void print(ostream& os) const; // Prints players details

};

// Overloaded output operator
ostream& operator<<(ostream& os, const Player& player);

#endif
