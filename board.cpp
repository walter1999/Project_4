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
    int num_of_boards=0; 
    ifstream fin;
    
    // Read the sample grid from the file.
    string fileName = "sudoku.txt";
    fin.open(fileName.c_str());
    if (!fin)// if it doesnt open 
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }
    try
    {
        while (fin.get(value) && fin.peek() != 'Z')// reads boards until the end of the file 
        {
            if(column > 8){  // all the following if else statemenst are meant to deeal with the issue of many bords in a single file 
                column = 0;
                row++;
                if(value == '.'){
                    value = 0;
                    sudokuBoard[row][column] = value;
                    if(fin.eof()) num_of_boards++;}
                else{
                    value = value;
                    sudokuBoard[row][column] = value;
                    if(fin.eof()) num_of_boards++;
                    
                }
                
            }
            else{
                
                if(value == '.'){
                    value = 0;
                    sudokuBoard[row][column] = value;
                    if(fin.eof()) num_of_boards++;
                    
                }
                else{
                    value = value;
                    sudokuBoard[row][column] = value;
                    if(fin.eof()) num_of_boards++;
                }
            }
            
            column++;
        }
    }
    catch (indexRangeError &ex)
    {
        cout << ex.what() << endl;// if there is an index error exit the program 
        exit(1);
    }
}

void board::initializeConflicts(){
// fill the array with the designatd values. In this case 0-8
	
	//create vector of vectors for columns 
	
	for(int col1=0; col1<9 ; col1++){
		vector<bool> temp(9, false);// creates temp vector thats going to be .push_back after each column if done 
		
		for(int row1=0; row1<9; row1++){

		char holdValue= sudokuBoard[row1][col1];// assigns the value found in [i][j] to holdValue 

		if(holdValue !=0)
			temp[holdValue-1]=true;// sets the found value to true in the vector for that specific column

		} 
		
		col.push_back(temp);// adds vector to col
   
	}
	
	//create vector of vectors for rows 

	for(int row1=0; row1<9 ; row1++){
                vector<bool> temp(9, false);// creates temp vector thats going to be .push_back after each column if done

                for(int col1=0; col1<9; col1++){
		
		char holdValue= sudokuBoard[row1][col1];//assigns the value found in [i][j] to holdValue		

                if(holdValue !=0)
                        temp[holdValue-1]=true;// sets the found value to true in the vector for that specific column

                }

               col.push_back(temp);// adds vector to col

        }
	
	//create vectors of vector for square
	int squareCount = 0;// keeps track of which square the nested loops are working on
 	int rowCount = 0;// keeps track of rows
	int columnCount = 0;// keeps track of colmn
	while(squareCount<8){// total of 9 squares
	
	vector<bool> temp(9,false);// creates temporary vector
	
    	for(int i=rowCount; i<rowCount+3; i++){// nested loop that goes through each square

		for(int j=columnCount; j<columnCount+3; j++){
		
		char holdValue= sudokuBoard[row][col];
		
		if(holdValue !=0)
			temp[holdValue-1]= true;
		}

	}
	sqr.push_back(temp);// adds the vector to sqr
	columnCount +=3; // adds three to move to second square. Square were counted from left to rigth 
	squareCount ++; // add one to square 
	if(squareCount==3){// if we reached the end travelling from left to right then move down and start all over again
		columnCount=0;
		rowCount +=3;
	}
    }
}

void board::printBoard() const{
    
    for(int row1=0; row1<9; row1++){// nested loop that traverses all the elements within the board 
        for(int col1=0; col1<9; col1++){
            char temp = sudokuBoard[row1][col1];
            std::cout<<temp;
            
        }
        std::cout<<std::endl;
    }
 
    
}


void board::printConflicts() const{
    
    for(int r_c_s= 0; r_c_s < 3; r_c_s++){// nestes loops to traverse all elements found in the  conflict vectors
        for(int rows1 = 0; rows1 < 9; rows1++){
            for(int cols1 = 0; cols1 < 9; cols1++){
                if(r_c_s == 0){
                    std::cout<<"Row Conflicts"<<std::endl;
                    bool temp;
                    temp = row[rows1][cols1];
                    if(temp == true){std::cout<<rows1<<cols1<<" TRUE"<<std::endl;}// prints the conflicts for the rows
                    else {std::cout<<rows1<<cols1<<" FALSE"<<std::endl;}
                }
                
                else if(r_c_s == 1){
                    std::cout<<"Column Conflicts"<<std::endl;
                    bool temp;
                    temp = col[rows1][cols1];
                    if(temp == true){std::cout<<rows1<<cols1<<" TRUE"<<std::endl;}// prints the conflicts for the columns 
                    else {std::cout<<rows1<<cols1<<" FALSE"<<std::endl;}
                }
                
                else if(r_c_s == 2){
                    std::cout<<"Square Conflicts"<<std::endl;
                    bool temp;
                    temp = sqr[rows1][cols1];
                    if(temp == true){std::cout<<rows1<<cols1<<" TRUE"<<std::endl;}// prints the conflicts for the squares
                    else {std::cout<<rows1<<cols1<<" FALSE"<<std::endl;}
                }
                
            }
            
        }
        
    }
    
    
}


bool board::checkValue(int rows, int cols, char value) const{
    
    if(col[cols][value - 1] == false || row[rows][value-1] == false)// || UsedInBox(rows, cols, value) == false checks whethere value has conflicts 
        return true;
    else return false;
    
}

void board::addValue(int rows, int cols, char value){

    if( sudokuBoard[rows][cols]==0){// if the board is empty add value otherwise do not 
    sudokuBoard[rows][cols] = value;
    }
   else
	std::cout<<" Cell is already filled" <<std::endl;
    updateConflicts();//calls updateconflict to update the conflicts after the value was added 
}

void board::clearCell(int rows, int cols){// clears the cell at the given lovation
    sudokuBoard[rows][cols]= 0;
    updateConflicts();// updates the conflicts 
}

void board::updateConflicts(){
    initializeConflicts();// iterative call to fucntion 
}

bool board::checkSolve() const{
    
    for(int rows = 0; rows < 9; rows++){
        for(int cols = 0; cols<9; cols++){
            if(!row[rows][cols] && !col[cols][rows] && !sqr[rows][cols])// checks whether all the elments have been set to true 
		return false;
	   else 
		return true;
	
            
        }
        
    }
    
    
}
