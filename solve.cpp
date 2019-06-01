#include <iostream>
#include "sudoku.h"
using namespace std;

int main() {
    Sudoku game;
    game.puzzle_input();
    switch(game.solve()) {
    case 0:
        cout << '0' << endl;
        break;
    case 1:
        cout << '1' << endl;
        game.print_result();
        break;
    case 2:
        cout << '2'<< endl;
    }
    return 0;
}
