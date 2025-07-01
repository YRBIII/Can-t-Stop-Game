//
// Project Folder: Exceptions Implementation
// File: Exceptions.cpp
//

#include "Exceptions.hpp"

// ------------------------
// BadPlayer Implementation
// ------------------------
BadPlayer::BadPlayer(const string& input) : badInput(input) {}

// Virtual print function
void BadPlayer::print() const {
    basePrint();
}

// Shared error message output
void BadPlayer::basePrint() const {
    cout << "Invalid player input: " << badInput << endl;
}

BadPlayer::~BadPlayer() {}

// ------------------------
// BadName Implementation
// ------------------------
BadName::BadName(const string& input) : BadPlayer(input) {}

// Override print function for BadName
void BadName::print() const {
    cout << "That name is already in use.\n";
    basePrint();
}

// ------------------------
// BadColor Implementation
// ------------------------
BadColor::BadColor(const string& input) : BadPlayer(input) {}

// Override print function
void BadColor::print() const {
    cout << "That color is already taken.\n";
    basePrint();
}

// ------------------------
// BadChoice Implementation
// ------------------------
BadChoice::BadChoice(const string& input) : badInput(input) {}

// Virtual print function
void BadChoice::print() const {
    cout << "Invalid turn choice: " << badInput << endl;
}

BadChoice::~BadChoice() {}

// ------------------------
// DuplicateSlot Implementation
// ------------------------
DuplicateSlot::DuplicateSlot(const string& input) : BadChoice(input) {}

// Override print function
void DuplicateSlot::print() const {
    cout << "You entered the same slot twice.\n";
    printBase();
}

// Shared error message
void DuplicateSlot::printBase() const {
    cout << "Bad input: " << badInput << endl;
}

// ------------------------
// BadSlot Implementation
// ------------------------
BadSlot::BadSlot(const string& input) : BadChoice(input) {}

// Override print function
void BadSlot::print() const {
    cout << "You entered a slot that doesn't exist.\n";
    printBase();
}

// Shared error message
void BadSlot::printBase() const {
    cout << "Bad input: " << badInput << endl;
}
