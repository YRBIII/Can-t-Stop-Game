//
// Project Folder: Enum Class
// Authors: Anthony Ciavarella and Yung Brinney
// File: Enums.hpp
//

#ifndef ENUMS_HPP
#define ENUMS_HPP

#include "tools.hpp"

enum class EColor { White, Orange, Yellow, Green, Blue, Error };
extern const string colorNames[];
string getColor(EColor color);

enum class ColumnState { Available, Pending, Captured };
extern const string stateNames[];
string getColState(ColumnState state);

// ✅ New Game State Enum
enum class GameState { Begun, Done, Quit };
extern const string stateNames2[];
string getGameState(GameState state);

#endif // ENUMS_HPP
