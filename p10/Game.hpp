//
// Project Folder: Game Class
// Authors: Anthony Ciavarella and Yung Brinney
// File: Game.hpp
//

#ifndef GAME_HPP
#define GAME_HPP

#include "tools.hpp"
#include "Enums.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include "Dice.hpp"
#include "CList.hpp"
#include "Exceptions.hpp"

class Game {
private:
    Board gameBoard;
    CList players;
    Dice* gameDice;
    const int* currentRolls = nullptr;
    GameState status;

    void getPlayers();
    GameState oneTurn(Player* p);
    void getNewPlayer();
    void checkData(const string& name, EColor color); // ✅ FIX: declare it here
    char getValidatedAction();

public:
    Game(bool testMode);
    ~Game();

    void play();
    bool isEmpty() const;
};

#endif // GAME_HPP
