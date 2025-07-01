//
// Project Folder: CList Implementation
// File: CList.cpp
//

#include "CList.hpp"

Cell::Cell(upp p, Cell* n) : data(move(p)), next(n) {}

Cell::~Cell() {}

CList::CList() : counter(0), head(nullptr), tail(nullptr), current(nullptr) {}

CList::~CList() {
    if (!head) return;

    current = head->next;
    while (current != head) {
        Cell* temp = current;
        current = current->next;
        delete temp;
    }

    delete head;
    head = tail = current = nullptr;
    counter = 0;
}

// Adds a new cell (with Player) to the circular list
void CList::addCell(upp p) {
    Cell* newCell = new Cell(move(p));

    if (!head) {
        head = tail = newCell;
        newCell->next = newCell;
    } else {
        newCell->next = head;
        tail->next = newCell;
        tail = newCell;
    }
    counter++;
}

// Advances the current pointer and returns the current Player
Player* CList::next() {
    if (!current) return nullptr;

    Player* result = current->data.get();
    current = current->next;
    return result;
}

// Removes the current Cell from the list and updates pointers
void CList::remove() {
    if (!head || !current) return;

    Cell* prev = head;
    while (prev->next != current && prev->next != head) {
        prev = prev->next;
    }

    if (current == head) head = head->next;
    if (current == tail) tail = prev;

    prev->next = current->next;

    Cell* temp = current;
    current = current->next;

    delete temp;
    counter--;

    if (counter == 0) {
        head = tail = current = nullptr;
    }
}

// Prints the players in the list, or "Empty List" if none exists
void CList::print(ostream& out) const {
    if (!head) {
        out << "Empty List\n";
        return;
    }

    Cell* temp = head;
    do {
        out << *(temp->data) << "\n";
        temp = temp->next;
    } while (temp != head);
}