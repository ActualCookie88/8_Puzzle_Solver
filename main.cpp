#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* ////////////////////////////////////////////////////////////////////

HEURISTICS

//////////////////////////////////////////////////////////////////// */

int uniformHeuristic(const vector<vector<int>>& puzzle) {
    return 0;
}

int misplacedHeuristic(const vector<vector<int>>& puzzle) {
    int count = 0;

    return count;
}

int manhattanHeuristic(const vector<vector<int>>& puzzle) {
    
}

/* ////////////////////////////////////////////////////////////////////

HELPERS

//////////////////////////////////////////////////////////////////// */

void displayPuzzle(const vector<vector<int>>& puzzle) {
    cout << "[" << puzzle[0][0] << " " << puzzle[0][1] << " " << puzzle[0][2] << "]" << endl <<
            "[" << puzzle[1][0] << " " << puzzle[1][1] << " " << puzzle[1][2] << "]" << endl <<
            "[" << puzzle[2][0] << " " << puzzle[2][1] << " " << puzzle[2][2] << "]" << endl << endl;
}

void border() {
    cout << endl;
    cout << "//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    cout << endl;
}

int selectOptionHelper(int min, int max) {
    string input;
    int number;
    while(true) {
        cin >> input;
        cout << endl;

        if(input == "CANCEL") {
            return -1;
        }

        try {
            number = stoi(input); // if fails, throws exception to catch
        } catch(...) {
            cout << "INVALID OPTION. TRY AGAIN: ";
            continue;
        }

        if(number >= min && number <= max) {
            return number;
        } else {
            cout << "INVALID OPTION. TRY AGAIN: ";
        }
    }
}

/* ////////////////////////////////////////////////////////////////////

MAIN

//////////////////////////////////////////////////////////////////// */

int main() {
    border();
    cout << "8-Puzzle Solver" << endl << endl;
    
    cout << "SELECT OPTION: " << endl <<
            "(1) Default Puzzle" << endl <<
            "(2) Custom Puzzle" << endl;

    int choice = selectOptionHelper(1, 2);
    vector<vector<int>> puzzle(3, vector<int>(3));

    if(choice == 1) {
        puzzle = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 0, 8}
        };
    }
    else if(choice == 2) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << "Enter tile Number (Row " << i+1 << ", Column " << j+1 << ")" << ": ";
                cin >> puzzle[i][j];
            }
        }
    }
    else {
        cout << "ERROR";
    }

    border();

    cout << "Selected puzzle: " << endl;
    displayPuzzle(puzzle);

    cout << "SELECT ALGORITHM: " << endl <<
            "(1) Uniform Cost Search" << endl <<
            "(2) Misplaced Tile Heuristic (A*)" << endl <<
            "(3) Manhattan Distance Heuristic (A*)" << endl;

    choice = selectOptionHelper(1, 3);

    if(choice == 1) {
        
    }
    else if(choice == 2) {

    }
    else if(choice == 3) {

    }
    else {
        cout << "ERROR";
    }

    return 0;
}

