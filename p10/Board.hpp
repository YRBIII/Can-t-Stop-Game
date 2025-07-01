//
// Project Folder: Board Class
// Authors: Anthony Ciavarella and Yung Brinney
// File: Board.hpp
//

#ifndef BOARD_HPP
#define BOARD_HPP

#include "Column.hpp"
#include "Player.hpp"
#include "tools.hpp"


// ---------------------------------------------------
// Class: Board
// Manages the game board, including columns and
// player interactions.
// ---------------------------------------------------
class Board {
private:
    unique_ptr<Column> backBone[13];   // Array of column pointers
    int towersInUse;        // Number of active towers
    int towerColumns[3];    // Tracks columns with towers
    Player* currentPlayer;  // Pointer to the current player

public:
    Board() : towersInUse(0), currentPlayer(nullptr) {
        for (int k = 2; k < 13; k++) {
            backBone[k] = make_unique<Column>(k);
        }
    }
    ~Board() = default;

    void print(ostream& os) const;   // Prints board state
    void startTurn(Player* player);  // Starts a player's turn
    bool move(int column);           // Moves player in the specified column
    void stop();                     // Handles stopping mechanics
    void bust();                     // Handles bust scenario
    bool isCaptured(int column);
};

// Output operator
inline ostream& operator<<(ostream& os, const Board& board) {
    board.print(os);
    return os;
}

#endif // BOARD_HPP
