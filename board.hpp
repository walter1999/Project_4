//
//  board.hpp
//  Project_4_a
//
//  Created by Thomas Campion on 2/25/18.
//  Copyright © 2018 Thomas Campion. All rights reserved.
//

#ifndef board_hpp
#define board_hpp

#include <stdio.h>
#include "matrix.h"
#include <vector>

using std::vector;

class board{
private:
    matrix<char> sudokuB[9][9];
    vector<vector <bool>> row;
    vector<vector <bool>> col;
    vector<vector <bool>> sqr;
public:
    void initializeBoard();
    void initializeConflicts();
    
    void printBoard() const;
    void printConflicts() const;
    
    bool checkValue(int row, int col, char value) const;
    
    void addValue(int row, int col, char value);
    
    void clearCell(int row, int col);
    
    void updateConflicts();
    
    bool checkSolve() const;
};

#endif /* board_hpp */
