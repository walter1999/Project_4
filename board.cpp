//
//  board.cpp
//  Project_4_a
//
//  Created by Thomas Campion on 2/25/18.
//  Copyright © 2018 Thomas Campion. All rights reserved.
//

#include "board.hpp"
#include <stdio.h>
#include <iostream>
#include "matrix.h"
#include <vector>
#include <fstream>
#include "d_except.h"

void board::initializeBoard(){
    char value;
    int row = 0;
    int column = 0;
    
    ifstream fin;
    
    // Read the sample grid from the file.
    string fileName = "sudoku.txt";
    fin.open(fileName.c_str());
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }
    try
    {
        while (fin.get(value) && fin.peek() != 'Z')
        {
            if(column > 8){
                column = 0;
                row++;
                if(value == '.'){
                    value = 0;
                    sudokuB[row][column] = value;
                    if(fin.eof()) num_of_boards++;}
                else{
                    value = value;
                    sudokuB[row][column] = value;
                    if(fin.eof()) num_of_boards++;
                    
                }
                
            }
            else{
                
                if(value == '.'){
                    value = 0;
                    sudokuB[row][column] = value;
                    if(fin.eof()) num_of_boards++;
                    
                }
                else{
                    value = value;
                    sudokuB[row][column] = value;
                    if(fin.eof()) num_of_boards++;
                }
            }
            
            column++;
        }
    }
    catch (indexRangeError &ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
}

void board::initializeConflicts(){
 
    for(int row = 0; row<9; row++){
        for(int col = 0; col<9; col++){
            
            
        }
    }
    
    
}

void board::printBoard() const{
    
    for(int row=0; row<9; row++){
        for(int col=0; col<9; col++){
            char temp = sudokuB[row][col];
            std::cout<<temp;
            
        }
        std::cout<<std::endl;
    }
 
    
}


void board::printConflicts() const{
    
    for(int r_c_s= 0; r_c_s < 3; r_c_s++){
        for(int rows = 0; rows < 9; rows++){
            for(int cols = 0; cols < 9; cols++){
                if(r_c_s == 0){
                    std::cout<<"Row Conflicts"<<std::endl;
                    bool temp;
                    temp = row[rows][cols];
                    if(temp == true){std::cout<<rows<<cols<<" TRUE"<<std::endl;}
                    else {std::cout<<rows<<cols<<" FALSE"<<std::endl;}
                }
                
                else if(r_c_s == 1){
                    std::cout<<"Column Conflicts"<<std::endl;
                    bool temp;
                    temp = col[rows][cols];
                    if(temp == true){std::cout<<rows<<cols<<" TRUE"<<std::endl;}
                    else {std::cout<<rows<<cols<<" FALSE"<<std::endl;}
                }
                
                else if(r_c_s == 2){
                    std::cout<<"Square Conflicts"<<std::endl;
                    bool temp;
                    temp = sqr[rows][cols];
                    if(temp == true){std::cout<<rows<<cols<<" TRUE"<<std::endl;}
                    else {std::cout<<rows<<cols<<" FALSE"<<std::endl;}
                }
                
            }
            
        }
        
    }
    
    
}


bool board::checkValue(int rows, int cols, char value) const{
    
    if(col[cols][value - 1] == false || row[rows][value-1] == false || UsedInBox(rows, cols, value) == false)
        return true;
    else return false;
    
}

void board::addValue(int row, int col, char value){
    sudokuB[row][col] = value;
    
    updateConflicts();
}

void board::clearCell(int row, int col){
    sudokuB[row][col]= 0;
    updateConflicts();
}

void board::updateConflicts(){
    initializeConflicts();
}

bool board::checkSolve() const{
    int solve = 0;
    int unsolve =0;
    
    for(int row = 0; row < 9; row++){
        for(int col = 0; col<9; col++){
            if(unsolve > 0){return false; printBoard(); printConflicts();}
            
        }
        
    }
    
    
}
