//
// Project Folder: Column Class
// Authors: Anthony Ciavarella and Yung Brinney
// File: Column.hpp
//

#ifndef COLUMN_HPP
#define COLUMN_HPP

#include "Enums.hpp"
#include "Player.hpp"
#include "tools.hpp"

// -----------------------------------------------
// Class: Column
// Represents a column, tracking state and marker positions.
// -----------------------------------------------
class Column {
private:
    static const int columnLengths[13];   // Column lengths indexed by number
    int num;                              // Column number
    const int len;                        // Column length
    ColumnState state;                    // Current state
    int m[5];                             // Player/tower marker positions

public:
    Column(int num)
        : num(num), len(columnLengths[num]), state(ColumnState::Available), m{0, 0, 0, 0, 0} {}
    ~Column() = default;

    ColumnState getState() const { return state; }   // Get column state

    void print(ostream& os) const;   // Print column details
    bool startTower(Player* player); // Start tower in column
    bool move();                     // Move marker
    void stop(Player* player);       // Stop player in the column
    void bust();                     // Handle bust scenario

    static int getColLen(int colNum) { return columnLengths[colNum]; } // Get column length
};

// Overload operator
inline ostream& operator<<(ostream& os, const Column& column) {
    column.print(os);
    return os;
}

void printColumn(ofstream& output, const Column& column); // Print column to file

#endif
