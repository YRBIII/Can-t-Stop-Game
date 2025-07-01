//
// Project Folder: Dice Class
// Authors: Anthony Ciavarella and Yung Brinney
// File: Dice.hpp
//

#ifndef DICE_HPP
#define DICE_HPP

#include "tools.hpp"
#include "Exceptions.hpp"

// File path for fake dice rolls
#define FAKE_DICE_FILE "fake_dice.txt"

// -----------------------------------------------
// Class: Dice (Base Class)
// Represents a basic set of dice
// -----------------------------------------------
class Dice {
protected:
    int nDice;          // Number of dice in the set
    vector<int> diceV;  // Stores values of last roll

public:
    explicit Dice(int n);
    virtual ~Dice();

    virtual const int* roll();     // Rolls dice and returns array of values
    virtual ostream& print(ostream& os) const;  // Prints dice values

    Dice(const Dice&) = delete;            // Delete copy constructor
    Dice& operator=(const Dice&) = delete; // Delete assignment operator
};

// -----------------------------------------------
// Class: CantStopDice (Derived from Dice)
// Adds pairing logic for 4 dice
// -----------------------------------------------
class CantStopDice : public Dice {
protected:
    int pairTotals[2];     // Stores sum of selected dice pairs

public:
    CantStopDice();
    ~CantStopDice() override = default;

    const int* roll() override;    // Prompts user for dice pairing
    ostream& print(ostream& os) const override;  // Prints pair totals
};

// -----------------------------------------------
// Class: FakeDice (Derived from CantStopDice)
// Automates dice values from file for testing
// -----------------------------------------------
class FakeDice : public CantStopDice {
private:
    ifstream fin;       // Input file stream for fake rolls
    string lastCommand; // Last ROLL or STOP command read

public:
    FakeDice();
    ~FakeDice() override = default;

    const int* roll() override;  // Reads dice and command from file
    string getCommand() const;   // Returns last command (ROLL/STOP)
};

// Output helpers
ostream& operator<<(ostream& os, const Dice& dice);

#endif // DICE_HPP
