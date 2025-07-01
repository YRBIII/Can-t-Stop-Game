//
// Project Folder: Dice Implementation
// File: Dice.cpp
//

#include "Dice.hpp"

Dice::Dice(int n) : nDice(n), diceV(n, 0) {}

Dice::~Dice() {}

// Rolls all dice and returns a pointer to the array of values
const int* Dice::roll() {
    for (int k = 0; k < nDice; k++) {
        diceV[k] = rand() % 6 + 1;
    }
    return diceV.data();
}

// Prints dice values
ostream& Dice::print(ostream& os) const {
    for (int val : diceV) {
        os << val << " ";
    }
    return os;
}
// Overloaded << operator for Dice output
ostream& operator<<(ostream& os, const Dice& dice) {
    return dice.print(os);
}


// -------------------------
// CantStopDice Implementation
// -------------------------
CantStopDice::CantStopDice() : Dice(4) {
    pairTotals[0] = pairTotals[1] = 0;
}

// Rolls 4 dice, asks user to select first pair, and calculates both pair sums
const int* CantStopDice::roll() {
    Dice::roll();
    cout << "\nDice Results:\n";
    char labels[] = {'A', 'B', 'C', 'D'};
    for (int k = 0; k < 4; ++k) { cout << labels[k] << ": " << diceV[k] << "  ";}
    cout << "\n";
    string input;
    int first = -1, second = -1;
    cout << "\nChoose two dice for the first pair (e.g., AB, CD): ";
    cin >> input;
    input.erase(remove(input.begin(),
        input.end(), ' '), input.end());
    if (input.length() != 2) { throw BadSlot(input);}
    char a = toupper(input[0]);
    char b = toupper(input[1]);
    first = a - 'A';
    second = b - 'A';
    if (first < 0 || first >= 4 || second < 0 || second >= 4) {
        throw BadSlot(input);}
    if (first == second) { throw DuplicateSlot(input);}
    pairTotals[0] = diceV[first] + diceV[second];
    vector<int> others;
    for (int k = 0; k < 4; ++k) {
        if (k != first && k != second) others.push_back(diceV[k]);}
    pairTotals[1] = others[0] + others[1];
    return pairTotals;
}


// Print pair totals
ostream& CantStopDice::print(ostream& os) const {
    os << "Pair totals: " << pairTotals[0] << ", " << pairTotals[1];
    return os;
}

// -------------------------
// FakeDice Implementation
// -------------------------
FakeDice::FakeDice() {
    fin.open(FAKE_DICE_FILE);
    if (!fin.is_open()) {
        fatal("Cannot open fake dice file.");
    }
}

// Overrides roll(): reads 4 dice values + command from file
const int* FakeDice::roll() {
    int a, b, c, d;
    string cmd;
    if (!(fin >> a >> b >> c >> d >> cmd)) {
        fatal("Ran out of fake dice rolls before game ended.");}
    diceV = {a, b, c, d};
    pairTotals[0] = a + b;
    pairTotals[1] = c + d;
    lastCommand = cmd;
    char labels[] = {'A', 'B', 'C', 'D'};
    cout << "\nDice Results:\n";
    for (int k = 0; k < 4; ++k) {
        cout << labels[k] << ": " << diceV[k] << "  ";
    }
    cout << "Command: " << lastCommand << "\n";
    if (cmd == "BADSLOT") {
        throw BadSlot("ae");
    } else if (cmd == "DUPSLOT") {
        throw DuplicateSlot("aa");
    } else if (cmd == "BADCHOICE") {
        throw BadChoice("x");
    } else if (cmd != "ROLL" && cmd != "STOP") {
        fatal("Invalid command in fake_dice.txt: " + cmd);}
    return pairTotals;
}

// Getter for the last command
string FakeDice::getCommand() const {
    return lastCommand;
}