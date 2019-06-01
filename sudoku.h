#ifndef SUDOKU_H
#define SUDOKU_H

/***************************************************
 * Finish your .cpp according to this header file. *
 * You can modify this file if needed.             *
 ***************************************************/
#include <vector>

class Sudoku {
  public:
    Sudoku();
    Sudoku(std::vector< std::vector<int> > );
    /*
        // generate
        static Sudoku generate();
    */
    // transform
    void swapNum(int, int);
    void swapRow(int, int);
    void swapCol(int, int);
    void rotate(int);
    void flip(int);

    // solve
    void check(int, int);
    void clean(int, int, int, int);
    void new_branch();
    int solve();

    // common used
    void puzzle_input();
    void print_result();

  private:
    int **board;
    std::vector<int>::iterator it, it2;
    std::vector<int> ***psb;
    int version;
    int solved;
    std::vector<int> *todo;
};

#endif // SUDOKU_H
