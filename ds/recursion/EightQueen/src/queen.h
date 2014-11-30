/*
 * queen.h
 *
 *  Created on: 2014年11月30日
 *      Author: wangdq
 */

#ifndef QUEEN_H_
#define QUEEN_H_

class Queen
{
public:
	Queen(int n);
	~Queen();
	void putQueen(int row);
	int getHowMany();
private:
	void printResult();
private:
	    bool *columnAvailable;
	    bool *leftDiagonalAvailable;
	    bool *rightDiagonalAvailable;
	    int *posInRow;
        int squares;
        int howMany;
};

#endif /* QUEEN_H_ */
