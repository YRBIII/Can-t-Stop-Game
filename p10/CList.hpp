//
// Project Folder: CList Class
// Authors: Anthony Ciavarella and Yung Brinney
// File: CList.hpp
//

#ifndef CLIST_HPP
#define CLIST_HPP

#include "Player.hpp"

using upp = unique_ptr<Player>;

class CList;  // Forward declaration

// ----------------------------------------------
// Class: Cell
// Private helper class for storing Players
// in a circular linked list
// ----------------------------------------------
class Cell {
private:
    upp data;            // Unique pointer to Player
    Cell* next;          // Pointer to next cell in the list

    friend class CList;  // Friend declaration

public:
    Cell(upp p, Cell* n = nullptr);
    ~Cell();
};

// ----------------------------------------------
// Class: CList
// Manages a circular linked list of Players
// ----------------------------------------------
class CList {
private:
    int counter;    // Number of players in the list
    Cell* head;     // Pointer to the first cell
    Cell* tail;     // Pointer to the last cell
    Cell* current;  // Pointer to the current player

public:
    CList();
    ~CList();

    int count() const { return counter; }   // Returns number of players
    bool empty() const { return counter == 0; }  // Checks if list is empty
    Player* peek() const { return current ? current->data.get() : nullptr; }  // Returns current player
    void init() {current = head; }  // Sets current to the head

    void addCell(upp p);   // Adds a new player to the list
    Player* next();        // Advances to next player and returns pointer
    void remove();         // Removes current player from the list
    void print(ostream& out) const;  // Prints all players in the list
};

// Overload operator
inline ostream& operator<<(ostream& out, const CList& list) {
    list.print(out);
    return out;
}

#endif // CLIST_HPP
