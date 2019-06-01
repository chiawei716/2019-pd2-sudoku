#include <iostream>
#include "sudoku.h"
using namespace std;

//==========constructor=======

//Initialized
Sudoku::Sudoku() {
    //board construct
    board = new int*[9];
    for(int i=0; i<9; i++) board[i] = new int[9];

    //psb construct
    psb = new vector<int>**[40];
    for(int i=0; i<40; i++) psb[i] = new vector<int>*[9];
    for(int i=0; i<40; i++)
        for(int j=0; j<9; j++) psb[i][j] = new vector<int>[9];
    //to-do
    todo = new vector<int>[2];
    todo[0].reserve(84);
    todo[1].reserve(84);

    version = 0;
    solved = 0;
}

//Initialized for transform.
Sudoku::Sudoku(vector< vector<int> > input) {
    //board construct
    board = new int*[9];
    for(int i=0; i<9; i++) board[i] = new int[9];

    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++) {
            board[i][j] = input[i][j];
        }
    }
    version = 0;
    solved = 0;
}

//===========solve============

int Sudoku::solve() {
    //initialize
    int i, j, p, pass, pass2;
    for(i=0; i<9; i++)
        for(j=0; j<9; j++) {
            if(board[i][j] == 0) {
                for(p=0; p<=9; p++)
                    psb[version][i][j].push_back(p);
            } else psb[version][i][j].push_back(board[i][j]);
        }

    for(i=0; i<9; i++)
        for(j=0; j<9; j++)
            if(psb[version][i][j][0] != 0)
                check(i, j);

    //int tried=0;
    for(;;) {
        //tried++;
        //cout<<tried<<endl;
        for(;;) {
            for(;;) {
                if(version == -1) {
                    if(solved == 0) return 0;
                    else return 1;
                }
                pass = 1;
                for(i=0; i<9; i++) {
                    for(j=0; j<9; j++)
                        if(psb[version][i][j][0] == 0)
                            if(psb[version][i][j].size() == 1) {
                                version--;
                                pass = 0;
                                break;
                            }
                    if(pass == 0) break;
                }
                if(pass == 1) break;
            }
            pass2 = 1;
            for(i=0; i<9; i++)
                for(j=0; j<9; j++) {
                    if(psb[version][i][j][0] == 0)
                        if(psb[version][i][j].size() == 2) {
                            pass2 = 0;
                            psb[version][i][j][0] = psb[version][i][j][1];
                            psb[version][i][j].pop_back();
                            check(i, j);
                            if(todo[0].size() != 0) {
                                it = todo[0].begin();
                                it2 = todo[1].begin();
                                for(;;) {
                                    if(psb[version][*it][*it2].size() == 1) {
                                        todo[0].clear();
                                        todo[1].clear();
                                        break;
                                    } else if(psb[version][*it][*it2].size() == 2) {
                                        psb[version][*it][*it2][0] = psb[version][*it][*it2][1];
                                        psb[version][*it][*it2].pop_back();
                                        check(*it, *it2);
                                        it = todo[0].erase(it);
                                        it2 = todo[1].erase(it2);
                                        if(it == todo[0].end()) break;
                                    }
                                }
                            }
                        }
                }
            if(pass2 == 1) break;
        }

        new_branch();

        //check if solved
        pass = 1;
        for(i=0; i<9; i++) {
            for(j=0; j<9; j++)
                if(psb[version][i][j][0] == 0) {
                    pass = 0;
                    break;
                }
            if(pass == 0) break;
        }

        //if solved
        if(pass == 1) {
            if(solved == 0) {
                solved = 1;
                for(i=0; i<9; i++)
                    for(j=0; j<9; j++)
                        board[i][j] = psb[version][i][j][0];
            } else return 2;
            version--;
        }
    }
}

inline void Sudoku::check(int x, int y) {

    int i, j, p, q;
    //row and column
    for(i=0; i<9; i++) {
        if(i!=y)
            if(psb[version][x][i][0] == 0)
                if(psb[version][x][i].size() > 1)
                    clean(x, y, x, i);
        if(i!=x)
            if(psb[version][i][y][0] == 0)
                if(psb[version][i][y].size() > 1)
                    clean(x, y, i, y);
    }

    //cube
    if(x<3) p=0;
    else if(x<6) p=3;
    else p=6;

    if(y<3) q=0;
    else if(y<6) q=3;
    else q=6;

    for(i=p; i<p+3; i++)
        for(j=q; j<q+3; j++)
            if(i!=x && j!=y)
                if(psb[version][i][j][0] == 0)
                    if(psb[version][i][j].size() > 1)
                        clean(x, y, i, j);
    return;
}

inline void Sudoku::clean(int x, int y, int p, int q) {
    for(vector<int>::iterator it=psb[version][p][q].begin()+1; it!=psb[version][p][q].end(); it++) {
        if(*it == psb[version][x][y][0]) {
            it = psb[version][p][q].erase(it);
            if(psb[version][p][q].size() == 2) {
                todo[0].push_back(p);
                todo[1].push_back(q);
            }
            return;
        }
    }
    return;
}
/*
inline void Sudoku::clean(int x, int y, int p, int q) {
    for(int i=1; i<psb[version][p][q].size(); i++) {
        cout<<psb[version][p][q][i]<<endl;
        if(psb[version][p][q][i] == psb[version][x][y][0]) {
            it = psb[version][p][q].erase(psb[version][p][q].begin()+i);
            if(psb[version][p][q].size() == 2) {
                todo[0].push_back(p);
                todo[1].push_back(q);
            }
            return;
        }
    }
    return;
}*/


inline void Sudoku::new_branch() {
    int i, j, p, q, po, size, buf, pass;
    p = -1;
    q = -1;
    po = 10;
    pass = 0;
    for(i=0; i<9; i++) {
        for(j=0; j<9; j++) {
            size = psb[version][i][j].size();
            if(psb[version][i][j][0] == 0) {
                if(size == 1) return;
                else {
                    if(size == 3) {
                        p = i;
                        q = j;
                        pass = 1;
                        break;
                    } else if(size < po) {
                        p = i;
                        q = j;
                        po = size;
                    }
                }
            }
        }
        if(pass == 1) break;
    }
    if(p == -1) return;

    it = psb[version][p][q].begin() + 1;
    buf = *it;
    it = psb[version][p][q].erase(it);
    for(i=0; i<9; i++)
        for(j=0; j<9; j++) {
            psb[version+1][i][j].clear();
            psb[version+1][i][j].assign(psb[version][i][j].begin(), psb[version][i][j].end());
        }
    version++;
    psb[version][p][q].resize(1);
    psb[version][p][q][0] = buf;
    check(p, q);
    if(todo[0].size() != 0) {
        it = todo[0].begin();
        it2 = todo[1].begin();
        for(;;) {
            if(psb[version][*it][*it2].size() == 1) {
                todo[0].clear();
                todo[1].clear();
                return;
            } else if(psb[version][*it][*it2].size() == 2) {
                psb[version][*it][*it2][0] = psb[version][*it][*it2][1];
                psb[version][*it][*it2].pop_back();
                check(*it, *it2);
                it = todo[0].erase(it);
                it2 = todo[1].erase(it2);
                if(it == todo[0].end()) break;
            }
        }
    }
    return;
}


//===========transform========

void Sudoku::swapNum(int x, int y) {
    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++) {
            if(board[i][j] == x) board[i][j]=y;
            else if(board[i][j] == y) board[i][j]=x;
        }
    }
    return;
}

void Sudoku::swapRow(int x, int y) {
    int buf;
    for(int i=0; i<3; i++)
        for(int j=0; j<9; j++) {
            buf = board[x*3+i][j];
            board[x*3+i][j] = board[y*3+i][j];
            board[y*3+i][j] = buf;
        }
    return;
}

void Sudoku::swapCol(int x, int y) {
    int buf;
    for(int i=0; i<3; i++)
        for(int j=0; j<9; j++) {
            buf = board[j][x*3+i];
            board[j][x*3+i] = board[j][y*3+i];
            board[j][y*3+i] = buf;
        }
    return;
}

void Sudoku::rotate(int x) {
    if(x % 4 == 0) return;
    int buffer[9][9];
    for(int i=0; i<9; i++)
        for(int j=0; j<9; j++) buffer[i][j]=board[i][j];
    switch(x % 4) {
    case 1:
        for(int i=0; i<9; i++)
            for(int j=0; j<9; j++) board[i][j]=buffer[8-j][i];
        break;
    case 2:
        for(int i=0; i<9; i++)
            for(int j=0; j<9; j++) board[i][j]=buffer[8-i][8-j];
        break;
    case 3:
        for(int i=0; i<9; i++)
            for(int j=0; j<9; j++) board[i][j]=buffer[j][8-i];
        break;
    }
    return;
}

void Sudoku::flip(int x) {
    int buf;
    if(x == 0)
        for(int i=0; i<4; i++)
            for(int j=0; j<9; j++) {
                buf = board[i][j];
                board[i][j] = board[8-i][j];
                board[8-i][j] = buf;
            } else if(x == 1)
        for(int i=0; i<4; i++)
            for(int j=0; j<9; j++) {
                buf = board[j][i];
                board[j][i] = board[j][8-i];
                board[j][8-i] = buf;
            }
    return;
}

//===========COMMON==========

//Input puzzle.
void Sudoku::puzzle_input() {
    for(int i=0; i<9; i++)
        for(int j=0; j<9; j++) cin>>board[i][j];
    return;
}

//Print the board.
void Sudoku::print_result() {
    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++) {
            cout << board[i][j];
            if(j!=8) cout << ' ';
        }
        cout << '\n';
    }
    return;
}
