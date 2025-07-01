//
// Project Folder: Column Implementation
// File: Column.cpp
//

#include "Column.hpp"

// Column lengths based on column number (index from 0-12)
const int Column::columnLengths[13] = {0, 0, 3, 5, 7, 9, 11, 13, 11, 9, 7, 5, 3};

// Prints the column's state and marker positions in a structured format
void Column::print(ostream& os) const {
    os << "Column " << num << " (" << getColState(state) << "): ";

    for (int index = 1; index <= len; index++) {
        os << "[";
        for (int j = 0; j < 5; ++j) {
            os << (m[j] == index ? (j == 0 ? 'T' : colorNames[j][0]) : '-');
        }
        os << "]";
    }
    os << "\n";
}

// Start a tower for a given player in the column
bool Column::startTower(Player* player) {
    if (!player) {
        cout << "Error: startTower() received a nullptr Player!" << endl;
        return false;
    }

    cout << "\nStarting tower in Column " << num << " for " << player->getName() << "...\n";

    if (state == ColumnState::Captured) {
        cout << "[DEBUG] Column " << num << " is already Captured. Move denied." << endl;
        return false;
    }

    int p = (int)player->color();

    if (m[0] > 0) {
        cout << "Tower already exists, moving forward." << endl;
        m[p] = m[0];
        m[0]++;

    } else {
        cout << "No tower exists, placing new tower." << endl;
        m[0] = 1;
    }

    if (m[p] == len) {
        cout << "Column " << num << " has been fully occupied. Marking as Captured!" << endl;
        state = ColumnState::Captured;
    } else {


        state = ColumnState::Pending;
    }

    return true;
}

// Moves markers up by one step
bool Column::move() {
    bool moved = false;

    if (state == ColumnState::Captured) return false;

    if (m[0] > 0 && m[0] < len) {
        ++m[0];
        moved = true;
    }

    if (moved) state = ColumnState::Pending;
    return moved;
}

// Stops a player's movement and confirms tile placement
void Column::stop(Player* player) {
    if (!player) {
        cout << "Error: stop() called with a nullptr Player!" << endl;
        return;
    }

    cout << "Stopping column " << num << " for player " << player->getName() << endl;

    int p = (int)player->color();

    m[p] = m[0];
    m[0] = 0;

    if (m[p] == len) {
        cout << "Column " << num << " has been fully occupied. Marking as Captured!" << endl;
        state = ColumnState::Captured;
    } else {
        state = ColumnState::Pending;
    }
}


// Resets the column if a player busts
void Column::bust() {
    if (state == ColumnState::Pending) {
        m[0] = 0;
        state = ColumnState::Available;
    }
}

// Print column to file
void printColumn(ofstream& output, const Column& column) {
    ostringstream oss;
    oss << column;
    output << oss.str() << endl;
}