#ifndef _MAZE_H_
#define _MAZE_H_

#include <iostream>
#include <string>
#include <list>
#include <stack>
#include <fstream>

class Pos2D
{
public:
	Pos2D()
	{
		row = col = 0;
	}
    Pos2D(int r,int c)
	{
		row = r,col = c;
	}
	bool operator != (const Pos2D& pos)
	{
		return !(*this == pos);
	}
	bool operator == (const Pos2D& pos)
	{
		return this->row == pos.row
			&& this->col == pos.col;
	}

public:
	const static Pos2D NotAvailablePos;
    int row,col;
};

struct Cell
{
	Pos2D pos;
	char content;	// 'm' startpos '0' represents passage,'1' blocked,'e' exit,'.' visited
	int  triedTime;
};
class Maze
{
public:
	Maze();
	Maze(std::istream& mazeMapStream);
	~Maze();
	void initializeMap(std::istream& mazeMapStream);
	bool getoutOfMaze(std::pair<std::list<Pos2D>,std::list<Pos2D> >& resultPair);
	bool getoutOfMaze2(std::pair<std::list<Pos2D>,std::list<Pos2D> >& resultPair);
	bool getoutOfMaze3(std::pair<std::list<Pos2D>,std::list<Pos2D> >& resultPair);
private:
	Pos2D getFirstAvailablePos(Pos2D &curPos);
	bool is2PosNeighbour(Pos2D& fisrtPos,Pos2D& secondPos);
	bool  pushAllNeighbourCellStack(std::stack<Pos2D>& stack,Pos2D curPos);
	bool exitMaze(Pos2D &curPos,std::pair<std::list<Pos2D>,std::list<Pos2D> >& resultPair);
//for convenient we set it to public
public:
	static const char ENTRY_CONTENT = 'm',EXIT_CONTENT='e',BLOCKED_CONTENT='1',PASSAGE_CONTENT='0',VISITED_CONTENT='.';
	Cell *cellArray;
	int rowCnt,colCnt;
	Pos2D startPos,exitPos;
};

#endif
