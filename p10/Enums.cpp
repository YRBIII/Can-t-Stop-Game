//
// Project Folder: Enums Implementation
// File: Enums.cpp
//

#include "Enums.hpp"

const string colorNames[] = {
    "White",
    "Orange",
    "Yellow",
    "Green",
    "Blue",
    "Error"
};

const string stateNames[] = {
    "Available", "Pending", "Captured"
};

const string stateNames2[] = {
    "Begun", "Done", "Quit"
};

string getColor(EColor color) {
    return colorNames[(int)color];
}

string getColState(ColumnState state) {
    return stateNames[(int)state];
}

string getGameState(GameState state) {
    return stateNames2[(int)state];
}
