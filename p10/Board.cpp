//
// Project Folder: Board implementation
// File: Board.cpp
//

#include "Board.hpp"

// Print function
void Board::print(ostream& os) const {
    os << "\n------ Current Board State ------\n";
    for (int k = 2; k < 13; k++) {
        os << *(backBone[k]) << endl;
    }
}

// Starts a players turn
void Board::startTurn(Player* player) {
    if (!player) {
        cout << "Error: startTurn() received a nullptr Player!" << endl;
        return;
    }
    currentPlayer = player;
    towersInUse = 0;
    fill(begin(towerColumns), end(towerColumns), 0);
}

// Attempt to move a tower to a column
bool Board::move(int columnNum) {
    if (columnNum < 2 || columnNum > 12) {
        return false;
    }

    Column* columnPtr = backBone[columnNum].get();
    if (!columnPtr) {
        return false;
    }

    if (columnPtr->getState() == ColumnState::Captured) {
        return false;
    }

    for (int k = 0; k < towersInUse; k++) {
        if (towerColumns[k] == columnNum) {
            return columnPtr->move();
        }
    }

    if (towersInUse < 3) {
        if (columnPtr->startTower(currentPlayer)) {
            towerColumns[towersInUse++] = columnNum;
            return true;
        }
    }

    return false;
}


// Stop function - finalizes tower positions
void Board::stop() {
    if (!currentPlayer) {
        cout << "Error: stop() called with no active player!" << endl;
        return;
    }

    cout << "Finalizing move and checking captured columns..." << endl;

    for (int k = 0; k < towersInUse; k++) {
        int columnNum = towerColumns[k];
        Column* columnPtr = backBone[columnNum].get();

        if (!columnPtr) {
            cout << "Error: Column " << columnNum << " is null!" << endl;
            continue;
        }

        columnPtr->stop(currentPlayer);
        cout << "Stopped tower in Column " << columnNum << ".\n";

        if (columnPtr->getState() == ColumnState::Captured) {
            cout << "Column " << columnNum << " was captured by " << currentPlayer->getName() << "!" << endl;
            currentPlayer->wonColumn(columnNum);
        }
    }

    cout << "All towers finalized. Board state updated.\n" << endl;

    towersInUse = 0;
}


// Bust function - resets board if the player fails
void Board::bust() {
    for (int k = 0; k < towersInUse; k++) {
        if (towerColumns[k] >= 2 && towerColumns[k] <= 12 && backBone[towerColumns[k]]) {
            backBone[towerColumns[k]]->bust();
        }
    }
    towersInUse = 0;
}

bool Board::isCaptured(int column) {
    if (column < 2 || column > 12 || backBone[column]) return false;
    return backBone[column]->getState() == ColumnState::Captured;
}