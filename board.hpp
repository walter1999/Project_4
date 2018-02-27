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
    matrix<char> sudokuBoard[9][9];// declares board

    vector<vector <bool> > row;// vector of vectors for row conflict

    vector<vector <bool> > col;// vector of vector for column conflict

    vector<vector <bool> > sqr;// vector of vector for square

public:
    void initializeBoard();// crates the board 

    void initializeConflicts();// fills arrays with conflicts 
    
    void printBoard() const;// prints the board the to the screen 

    void printConflicts() const;// prints all the conflicts 
    
    bool checkValue(int rows, int cols, char value) const;// checks whether a value is allowed
    
    void addValue(int rows, int cols, char value);// adds value to specified location
    
    void clearCell(int rows, int cols);// clears cell 
    
    void updateConflicts();// updates conflict. Calls initialize conflicts 
    
    bool checkSolve() const;// checks whether on the cells have been set to true 
   
};

#endif /* board_hpp */
