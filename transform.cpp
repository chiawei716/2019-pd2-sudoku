#include <iostream>
#include "sudoku.h"
using namespace std;
int main() {
    Sudoku target;
    int command;
    int x, y;

    target.puzzle_input();
    while(cin >> command) {

        if(command == 0)break;
        else if(command == 1) {
            cin >> x >> y;
            target.swapNum(x, y);
        } else if(command == 2) {
            cin >> x >> y;
            target.swapRow(x, y);
        } else if(command == 3) {
            cin >> x >> y;
            target.swapCol(x, y);
        } else if(command == 4) {
            cin >> x;
            target.rotate(x);
        } else if(command == 5) {
            cin >> x;
            target.flip(x);
        }
    }

    target.print_result();

    return 0;
}
