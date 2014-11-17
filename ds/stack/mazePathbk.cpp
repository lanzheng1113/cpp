#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <fstream>
#include <iterator>

using namespace std;

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
ostream& operator <<(ostream& os,const Pos2D &  pos)
{
	os<<"("<<pos.row<<","<<pos.col<<")";
	return os;
}
const Pos2D Pos2D::NotAvailablePos = Pos2D(-1,-1);

struct Cell
{
	Pos2D pos;
	char content;	// 'm' startpos '0' represents passage,'1' blocked,'e' exit,'.' visited
	int  triedTime;
};
class Maze
{
public:
	Maze(){}
	Maze(istream& mazeMapStream);
	~Maze();
	void initializeMap(istream& mazeMapStream);
	bool getoutOfMaze(pair<list<Pos2D>,list<string>>& resultPair);
	bool getoutOfMaze2(pair<list<Pos2D>,list<string>>& resultPair);
private:
	Pos2D getFirstAvailablePos(Pos2D curPos);
	bool is2PosNeighbour(Pos2D& fisrtPos,Pos2D& secondPos);
	bool  pushAllNeighbourCellStack(stack<Pos2D>& stack,Pos2D curPos);
	static const char ENTRY_CONTENT = 'm',EXIT_CONTENT='e',PASSAGE_CONTENT='0',VISITED_CONTENT='.';
private:
	Cell *cellArray;
	int rowCnt,colCnt;
	Pos2D startPos,exitPos;
};
Maze::Maze(istream& mazeMapStream)
{
	initializeMap(mazeMapStream);
}
Maze::~Maze()
{
	delete[] cellArray;
}
void Maze::initializeMap(istream& mazeMapStream)
{
	string line;
	vector<string> mazeMapVec;
	while(getline(mazeMapStream,line))
		mazeMapVec.push_back(line);
	rowCnt = mazeMapVec.size();
	colCnt = mazeMapVec[0].length();
	cellArray = new Cell[rowCnt*colCnt];
	int row =0,col=0;
	for(const string& str: mazeMapVec)
	{   
		col = 0;
		for(char ch : str)
		{   
			int index = row*colCnt+col;
			cellArray[index].pos = Pos2D(row,col);
			if(ch == Maze::ENTRY_CONTENT) 
			{
				startPos = cellArray[index].pos;	// set as current pos(startPos)
			}else if(ch == Maze::EXIT_CONTENT)
			{
				exitPos = cellArray[index].pos; //set as exit pos
			}
			cellArray[index].content = ch;
			cellArray[index].triedTime = 0;
			++col;
		}
		++row;
	}
}
Pos2D Maze::getFirstAvailablePos(Pos2D curPos)
{   
	int row = curPos.row,col = curPos.col;
	int triedTime =  cellArray[row*colCnt+col].triedTime;
	Pos2D firstAvailPos = Pos2D::NotAvailablePos;
	Pos2D nextPosArray[] = {
		 Pos2D(row,col+1),Pos2D(row,col-1)	//right and left
		,Pos2D(row+1,col),Pos2D(row-1,col)	//down and up
	};
	if(triedTime == 4)
		return Pos2D::NotAvailablePos;
	// try in right left down up order
	bool bfind = false;
	while(triedTime < 4)
	{
		 firstAvailPos = nextPosArray[triedTime];
		 Cell& nextCell = cellArray[firstAvailPos.row*colCnt+firstAvailPos.col];	
		 if(nextCell.content == Maze::PASSAGE_CONTENT || nextCell.content == Maze::EXIT_CONTENT)
		 {
			 bfind = true;
			 break;
		 }
		 triedTime++;
	}
	cellArray[row*colCnt+col].triedTime = triedTime; //update tried time
	if(bfind)
		return firstAvailPos;
	else
		return  Pos2D::NotAvailablePos;
}
bool Maze::pushAllNeighbourCellStack(stack<Pos2D> &posStack,Pos2D curPos)
{
	int row = curPos.row,col = curPos.col;
	//Pos2D nextPosArray[] = {
	//	Pos2D(row,col+1),Pos2D(row,col-1)	//right and left
	//	,Pos2D(row+1,col),Pos2D(row-1,col)	//down and up
	//};
	Pos2D nextPosArray[] = {
		Pos2D(row-1,col),Pos2D(row+1,col)	//up and down
		,Pos2D(row,col-1),Pos2D(row,col+1)	//left and right
	};
	bool bfind = false;
	for(int i =0;i < 4;i++)
	{    
		Pos2D nextPos = nextPosArray[i];
		Cell& nextCell = cellArray[nextPos.row*colCnt+nextPos.col];	
		if(nextCell.content == Maze::PASSAGE_CONTENT 
			|| nextCell.content == Maze::EXIT_CONTENT)
		{   
			bfind = true;
			posStack.push(nextPos);
		}
	}
	return bfind;
}
bool Maze::is2PosNeighbour(Pos2D& fisrtPos,Pos2D& secondPos)
{   
	bool bNeighbour = false;
	if(fisrtPos.row == secondPos.row)
	{
		if(fisrtPos.col-secondPos.col ==1 || fisrtPos.col-secondPos.col ==-1)
			bNeighbour = true;
	}else if(fisrtPos.col == secondPos.col)
	{
		if(fisrtPos.row-secondPos.row ==1 || fisrtPos.row-secondPos.row ==-1)
			bNeighbour = true;
	}
	return bNeighbour;
}
bool Maze::getoutOfMaze2(pair<list<Pos2D>,list<string>>& resultPair)
{
	Pos2D curPos = startPos;
	stack<Pos2D> posStack;
	bool bfind = false;
	while(curPos != Maze::exitPos )
	{   
		cellArray[curPos.row*colCnt+curPos.col].content = Maze::VISITED_CONTENT;
		bfind = pushAllNeighbourCellStack(posStack,curPos);
		if(posStack.empty())
		{
			return false;
		}else
		{   
			resultPair.second.push_back("Goto: ("+std::to_string(curPos.row)+","+std::to_string(curPos.col)+")");
			if(bfind)
			{
				resultPair.first.push_back(curPos);
			}else  //dead cell,modify the path
			{   
				std::list<Pos2D>::reverse_iterator rend = resultPair.first.rend();
				std::list<Pos2D>::reverse_iterator rbegin = resultPair.first.rbegin();
				list<Pos2D> removeList;
				removeList.push_front(curPos);
				Pos2D nextPos = posStack.top();
				while(rbegin != rend)
				{
					Pos2D& pos = *rbegin;
					if(is2PosNeighbour(nextPos,pos))
					{
						break;
					}
					else
					{   
						removeList.push_front(pos);
						resultPair.first.remove(pos);
					}
					rbegin = resultPair.first.rbegin();
				}
				std::cout<<"remove path: "<<std::endl;
				std::copy(removeList.begin(),removeList.end(),std::ostream_iterator<Pos2D>(std::cout,"\t\t"));
				std::cout<<std::endl;
			}
			curPos = posStack.top();
			posStack.pop();
		}
	}
	resultPair.second.push_back("Goto: ("+std::to_string(Maze::exitPos.row)+","+std::to_string(Maze::exitPos.col)+")");
	resultPair.first.push_back(Maze::exitPos);
	return true;
}
 bool Maze::getoutOfMaze(pair<list<Pos2D>,list<string>>& resultPair)
{
	Pos2D curPos = startPos;
	bool bfind = false;
	stack<Pos2D> posStack;
	resultPair.second.push_front("start: ("+std::to_string(curPos.row)+","+std::to_string(curPos.col)+")");
	do
	{   
		Cell& curNode = cellArray[curPos.row*colCnt+curPos.col];
		cellArray[curPos.row*colCnt+curPos.col].content = '.'; //marked as visited 
		//try at most four time(right left down up) to find a available neighbour node
		Pos2D nextAvailablePos = getFirstAvailablePos(curPos);
		if(nextAvailablePos != Pos2D::NotAvailablePos)
		{   
			if(nextAvailablePos == exitPos) // successfully found path
			{
				resultPair.first.push_front(exitPos);
				resultPair.first.push_front(curPos);
				while(!posStack.empty())
				{
					resultPair.first.push_front(posStack.top());
					posStack.pop();
				}
				resultPair.second.push_back("exit: ("+std::to_string(exitPos.row)+","+std::to_string(exitPos.col)+")");
				bfind = true; 
				break;
			}
			posStack.push(curNode.pos); // push current pos to stack
			curPos = nextAvailablePos;	// set the next available pos as current pos
			resultPair.second.push_back("Goto: ("+std::to_string(curPos.row)+","+std::to_string(curPos.col)+")");
		}else
		{   
			//pop until we find a node has chance to try
			while(curNode.triedTime == 4 && !posStack.empty())
			{
				curPos = posStack.top();
				posStack.pop();
				curNode = cellArray[curPos.row*colCnt+curPos.col];
				resultPair.second.push_back("Backto: ("+std::to_string(curPos.row)+","+std::to_string(curPos.col)+")");
			}
			if(posStack.empty())
			{   
				bfind = false; 
				break;
			}
		}
	}
	while (!posStack.empty());

    return bfind;
}
int main(int argc, char *argv[])
{  
	string mapFileName ;
	ifstream mapStream;
	std::cout<<"input maze map file name: "<<std::endl;
	std::cin >> mapFileName;
	mapStream.open(mapFileName.c_str());
	Maze maze;
	if(!mapStream)
	{
		std::cerr<<" Could not open stream for reading."<<std::endl;
		return 1;
	}
	maze.initializeMap(mapStream);
	pair<list<Pos2D>,list<string>> resultPair;
	bool bsuccess = maze.getoutOfMaze2(resultPair);
	std::cout<<std::endl<<"---Finding Process---"<<std::endl;
	std::copy(resultPair.second.begin(),resultPair.second.end(),
					std::ostream_iterator<string>(std::cout,"\t"));
	std::cout<<std::endl<<"---Sum: "<<resultPair.second.size()-1<<" steps---" <<std::endl;
    if(bsuccess)
	{   
        std::cout<<"Get out by :"<<std::endl;
		std::copy(resultPair.first.begin(),resultPair.first.end(),
					std::ostream_iterator<Pos2D>(std::cout,"\t\t"));
		std::cout<<std::endl;
	}else
	{
          std::cout<<"No Path to get out!"<<std::endl;
	}
	return 0;
}