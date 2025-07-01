//
// Project Folder: Exceptions CLass
// Authors: Anthony Ciavarella and Yung Brinney
// File: Exceptions.hpp
//
#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include "tools.hpp"

// ---------------------------------------------------
// Class: BadPlayer (Base Class)
// Thrown when both name and color are invalid.
// ---------------------------------------------------
class BadPlayer {
public:
    string badInput;                // Stores invalid player input
    BadPlayer(const string& input);
    virtual void print() const;     // Displays error message
    void basePrint() const;         // Print for all derived classes
    virtual ~BadPlayer();
};

// ---------------------------------------------------
// Class: BadName (Derived from BadPlayer)
// Thrown when only the name is invalid.
// ---------------------------------------------------
class BadName : public BadPlayer {
public:
    BadName(const string& input);
    void print() const override;  // Prints name error
};

// ---------------------------------------------------
// Class: BadColor (Derived from BadPlayer)
// Thrown when only the color is invalid.
// ---------------------------------------------------
class BadColor : public BadPlayer {
public:
    BadColor(const string& input);
    void print() const override;  // Prints color error
};

// ---------------------------------------------------
// Class: BadChoice (Base Class)
// Thrown when an invalid R/S/Q choice is made.
// ---------------------------------------------------
class BadChoice {
public:
    string badInput;                // Stores invalid choice
    BadChoice(const string& input);
    virtual void print() const;     // Displays choice error
    virtual ~BadChoice();
};

// ---------------------------------------------------
// Class: DuplicateSlot (Derived from BadChoice)
// Thrown when same dice slot is chosen twice.
// ---------------------------------------------------
class DuplicateSlot : public BadChoice {
public:
    DuplicateSlot(const string& input);
    void print() const override;        // Prints invalid slot error
    void printBase() const;             // Common message print
};

class BadSlot : public BadChoice {
public:
    BadSlot(const string& input);
    void print() const override;  // Prints invalid slot error
    void printBase() const;       // Common message print
};

#endif // EXCEPTIONS_HPP
