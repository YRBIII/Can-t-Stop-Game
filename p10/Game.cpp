//
// Project Folder: Game Implementation
// File: Game.cpp
//

#include "Game.hpp"

Game::Game(bool testMode) : gameBoard(), status(GameState::Begun) {
    gameDice = testMode ? new FakeDice : new CantStopDice;
    getPlayers();
    cout << "Game initialized with players, dice, and a board.\n";
}

Game::~Game() {
    delete gameDice;
    cout << "Game cleaned up.\n";
}

bool Game::isEmpty() const {
    return players.empty();
}

void Game::getPlayers() {
    int playerCount = 0;
    char addMore = 'Y';

    while (playerCount < 4) {
        getNewPlayer();
        playerCount++;

        if (playerCount >= 2) {
            cout << "Add another player? (Y/N): ";
            cin >> addMore;
            if (toupper(addMore) != 'Y') break;
        } else {
            cout << "At least 2 players are required. Please add another player.\n";
        }
    }

    if (playerCount == 4) {
        cout << "Max players reached.\n";
    }
}

void Game::getNewPlayer() {
    string name;
    int colorChoice;

    for (;;) {
        try {
            cout << "\n------ New Player Setup ------" << endl;
            cout << "Enter player name: ";
            cin >> name;

            for (;;) {
                cout << "\nChoose a color:\n";
                for (int k = 1; k <= 4; ++k) {
                    cout << k << " - " << getColor((EColor)k) << endl;
                }
                cout << "Enter choice: ";
                cin >> colorChoice;
                if (colorChoice >= 1 && colorChoice <= 4) break;
                cout << "Invalid choice. Try 1–4.\n";
            }

            checkData(name, (EColor)colorChoice);
            upp newPlayer = make_unique<Player>(name, (EColor)colorChoice);
            players.addCell(move(newPlayer));

            cout << "Player " << name << " added with color " << getColor((EColor)colorChoice) << ".\n";
            break;
        }
        catch (const BadName& e) {
            e.print();
        }
        catch (const BadColor& e) {
            e.print();
        }
        catch (const BadPlayer& e) {
            e.print();
        }
        catch (...) {
            fatal("Unexpected error in getNewPlayer.");
        }
        cout << "Please try again.\n";
    }
}

void Game::checkData(const string& name, EColor color) {
    bool nameUsed = false;
    bool colorUsed = false;

    players.init();  // reset to head of list

    for (int i = 0; i < players.count(); ++i) {
        Player* p = players.peek();
        if (p->getName() == name) {
            nameUsed = true;
        }
        if (p->color() == color) {
            colorUsed = true;
        }
        players.next();
    }

    if (nameUsed && colorUsed) {
        throw BadPlayer(name + " / " + getColor(color));
    } else if (nameUsed) {
        throw BadName(name);
    } else if (colorUsed) {
        throw BadColor(getColor(color));
    }
}

char Game::getValidatedAction() {
    char choice;
    cin >> choice;
    choice = toupper(choice);

    if (choice != 'R' && choice != 'S' && choice != 'Q') {
        throw BadChoice(string(1, choice));
    }
    return choice;
}

void Game::play() {
    if (players.empty()) {
        cout << "No players to play.\n";
        status = GameState::Quit;
        return;
    }

    cout << "\n--- Player List Before Round ---\n";
    cout << players;
    players.init();

    while (status == GameState::Begun && !players.empty()) {
        Player* current = players.peek();
        cout << "\n====== " << current->getName() << "'s Turn ======\n";

        GameState turnResult = oneTurn(current);

        if (turnResult == GameState::Quit) {
            players.remove();
            if (players.empty()) {
                cout << "All players resigned. Game over.\n";
                status = GameState::Quit;
                break;
            }
            continue;
        }
        if (turnResult == GameState::Done) {
            status = GameState::Done;
            break;
        }

        players.next();
    }

    cout << "\n==== Final Game State: " << getGameState(status) << " ====\n";
}

GameState Game::oneTurn(Player* pp) {
    gameBoard.startTurn(pp);
    cout << *pp;

    while (true) {
        char choice = 0;
        try {
            cout << "\nChoose an action:\nR - Roll\nS - Stop\nQ - Resign\n> ";
            choice = getValidatedAction();
        }
        catch (const BadChoice& e) {
            e.print();
            continue;
        }

        if (choice == 'Q') {
            cout << pp->getName() << " resigned.\n";
            gameBoard.bust();
            return GameState::Quit;
        }

        if (choice == 'S') {
            gameBoard.stop();
            for (int col = 2; col <= 12; col++) {
                if (gameBoard.isCaptured(col)) {
                    pp->wonColumn(col);
                }
            }
            if (pp->getCapturedCount() >= 3) {
                cout << pp->getName() << " wins!\n";
                return GameState::Done;
            }
            return GameState::Begun;
        }

        if (choice == 'R') {
            try {
                currentRolls = gameDice->roll();
            } catch (const DuplicateSlot& e) {
                e.print(); continue;
            } catch (const BadSlot& e) {
                e.print(); continue;
            } catch (const BadChoice& e) {
                e.print(); continue;
            } catch (...) {
                fatal("Unknown error during dice roll.");
            }

            const bool move1 = gameBoard.move(currentRolls[0]);
            const bool move2 = gameBoard.move(currentRolls[1]);

            if (!move1 && !move2) {
                cout << "Bust! Both moves failed.\n";
                gameBoard.bust();
                return GameState::Begun;
            }

            cout << "Board after move:\n" << gameBoard;
        }
    }
}