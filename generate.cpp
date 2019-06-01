#include <iostream>
#include "sudoku.h"
#include <ctime>
#include <cstdlib>
using namespace std;

int main() {
    //======question database======

    int Q1[9][9] = {
        {3,0,7,1,0,0,0,0,0},
        {0,5,9,0,0,3,1,0,0},
        {0,4,0,9,7,0,2,0,0},
        {0,0,0,0,9,7,0,0,0},
        {4,0,2,0,0,0,9,0,8},
        {0,0,0,3,2,0,0,0,0},
        {0,0,6,0,3,9,0,8,0},
        {0,0,4,5,0,0,3,6,0},
        {0,0,0,0,0,2,5,0,1}
    };

    int Q2[9][9] = {
        {5,0,0,0,2,7,0,0,0},
        {0,0,1,0,0,0,3,6,0},
        {9,0,0,6,0,0,0,0,5},
        {0,0,4,7,0,0,8,3,0},
        {0,0,0,0,3,0,0,0,0},
        {0,6,9,0,0,8,1,0,0},
        {2,0,0,0,0,9,0,0,7},
        {0,1,7,0,0,0,2,0,0},
        {0,0,0,4,7,0,0,0,3}
    };

    int Q3[9][9] = {
        {6,0,0,8,7,0,0,1,0},
        {7,3,0,0,0,0,9,0,0},
        {0,0,0,0,0,5,4,0,0},
        {0,0,0,6,0,4,1,8,0},
        {0,0,0,0,3,0,0,0,0},
        {0,5,1,2,0,7,0,0,0},
        {0,0,7,5,0,0,0,0,0},
        {0,0,6,0,0,0,0,3,5},
        {0,8,0,0,2,1,0,0,4}
    };

    //======question database======


    srand(time(NULL));
    vector< vector<int> > Out(9, vector<int>(9));

    //Take random one in the database as the base of the new question.
    switch(rand()%3) {
    case 0:
        for(int i=0; i<9; i++) {
            for(int j=0; j<9; j++) {
                (Out.at(i)).at(j) = Q1[i][j];
            }
        }
        break;
    case 1:
        for(int i=0; i<9; i++) {
            for(int j=0; j<9; j++) {
                (Out.at(i)).at(j) = Q2[i][j];
            }
        }
        break;
    case 2:
        for(int i=0; i<9; i++) {
            for(int j=0; j<9; j++) {
                (Out.at(i)).at(j) = Q3[i][j];
            }
        }
        break;
    }

    Sudoku Output(Out);

    //Transform randomly for 20 times.
    for(int i=0; i<20; i++) {
        switch(rand()%5+1) {

        case 1:
            Output.swapNum(rand()%9+1, rand()%9+1);
            break;

        case 2:
            Output.swapRow(rand()%3, rand()%3);
            break;

        case 3:
            Output.swapCol(rand()%3, rand()%3);
            break;

        case 4:
            Output.rotate(rand()%4);
            break;

        case 5:
            Output.flip(rand()%2);
            break;
        };
    }

    Output.print_result();

    return 0;
}
