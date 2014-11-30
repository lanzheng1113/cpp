/*
 * queen.cpp
 *
 *  Created on: 2014年11月30日
 */
#include <iostream>
#include <algorithm>    // std::fill
#include "queen.h"

/**
 * initialize related pointer
 */
Queen::Queen(int n):squares(n),howMany(0)
{
    columnAvailable = new bool[n];
    std::fill(columnAvailable,columnAvailable+n,true);

    leftDiagonalAvailable = new bool[2*n-1];
    std::fill(leftDiagonalAvailable,leftDiagonalAvailable+2*n-1,true);

    rightDiagonalAvailable = new bool[2*n-1];
    std::fill(rightDiagonalAvailable,rightDiagonalAvailable+2*n-1,true);

    posInRow = new int[n];
}

Queen::~Queen()
{
	delete[] columnAvailable;
	delete[] leftDiagonalAvailable;
	delete[] rightDiagonalAvailable;
	delete[] posInRow;
}
int Queen::getHowMany()
{
	return howMany;
}
void Queen::printResult()
{
	std::cout<<"***"<<squares<<" Queen, solution : "<<howMany+1<<" ***"<<std::endl;
	for(int i = 0;i< squares ;i++)
		std::cout << "\t"<<i;
	std::cout<<std::endl;
	for(int i =0;i < squares ;i++)
	{
        std::cout<<i;
		for (int j=0;j < squares;j++)
		{
			if ( posInRow[i] == j)
				std::cout << "\t"<<"Q";
			else
				std::cout<<"\t"<<"#";
		}
		std::cout<<std::endl;
	}
	howMany++;
}
/**
 *   put a queen in row
 */
void Queen::putQueen(int row)
{
    for(int col = 0; col < squares ; col++)
    {
    	   //if it is OK to put ,just put
           if ( columnAvailable[col]  && leftDiagonalAvailable[ row+col ] && rightDiagonalAvailable[squares-1+row-col])
           {
                 posInRow[row] = col;
                 //mark the  cell in the same column,or in left diagonal or right diagonal as unavailable
                 columnAvailable[col]  = false;
                 leftDiagonalAvailable[row+col] = false;
                 rightDiagonalAvailable[squares-1+row-col] = false;
                 // try put next row
                 if( row+1 < squares)
                	 putQueen(row+1);
                 else
                	 printResult(); //once get a solution,print it
                 //if failed put next row,undo marking
                columnAvailable[col]  = true;
                leftDiagonalAvailable[row+col] = true;
                rightDiagonalAvailable[squares-1+row-col] = true;
           }
    }
}




