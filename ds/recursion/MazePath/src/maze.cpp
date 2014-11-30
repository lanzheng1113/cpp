#include <iterator>
#include <vector>
#include "maze.h"

using namespace std;

const Pos2D Pos2D::NotAvailablePos = Pos2D(-1,-1);
std::ostream& operator <<(std::ostream& os,const Pos2D &  pos)
{
	os<<"("<<pos.row<<","<<pos.col<<")";
	return os;
}
Maze::Maze() : rowCnt(0),colCnt(0),cellArray(0)
{

}
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
//find first avaliable pos
Pos2D Maze::getFirstAvailablePos(Pos2D &curPos)
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
//push all Neighbor available pos
bool Maze::pushAllNeighbourCellStack(stack<Pos2D> &posStack,Pos2D curPos)
{
	int row = curPos.row,col = curPos.col;
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
//check if two pos can reach in one step
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
bool Maze::getoutOfMaze2(pair<list<Pos2D>,list<Pos2D> >& resultPair)
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
			resultPair.second.push_back(curPos);
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
	resultPair.second.push_back(exitPos);
	resultPair.first.push_back(Maze::exitPos);
	return true;
}

//using recursion to get out
bool Maze::getoutOfMaze3(std::pair<std::list<Pos2D>,std::list<Pos2D> >& resultPair)
{
	    return exitMaze(startPos,resultPair);
}
//using recursion to get out
bool Maze::exitMaze(Pos2D &curPos,std::pair<std::list<Pos2D>,std::list<Pos2D> >& resultPair)
{
		   bool bfind = false;
	       Cell& curCell = cellArray[curPos.row*colCnt+curPos.col];
	       if (curPos == exitPos)
	       {
	    	    bfind =  true;  //OK find our way out
	       }else if(curCell.content == Maze::VISITED_CONTENT
				|| curCell.content == Maze::BLOCKED_CONTENT )
		  {
	    	   bfind =  false;// can not visit or should not repeated a visited cell
		  }else
		  {
			    int row = curPos.row,col = curPos.col;
			    Pos2D nextPosArray[] = {
					 Pos2D(row,col+1),Pos2D(row,col-1)	// right and left
					,Pos2D(row+1,col),Pos2D(row-1,col)	// down and up
				};
			    cellArray[curPos.row*colCnt+curPos.col].content = Maze::VISITED_CONTENT; //marked as visited
				resultPair.first.push_back(curPos);
				resultPair.second.push_back(curPos);
			    //try four neighbor cell
			    for ( int i =0; !bfind && i < 4;i++)
			    	bfind = exitMaze(nextPosArray[i],resultPair);
			    if(!bfind)
				  {
			    	 resultPair.first.pop_back(); // if current cell can not get across ,remove it
				  }
		  }
	      return bfind;
}
//using stack to get out
bool Maze::getoutOfMaze(pair<list<Pos2D>,list<Pos2D> >& resultPair)
{
	Pos2D curPos = startPos;
	bool bfind = false;
	stack<Pos2D> posStack;
	resultPair.second.push_front(curPos);
	do
	{
		Cell& curNode = cellArray[curPos.row*colCnt+curPos.col];
		cellArray[curPos.row*colCnt+curPos.col].content = Maze::VISITED_CONTENT; //marked as visited
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
				resultPair.second.push_back(exitPos);
				bfind = true;
				break;
			}
			posStack.push(curNode.pos); // push current pos to stack
			curPos = nextAvailablePos;	// set the next available pos as current pos
			resultPair.second.push_back(curPos);
		}else
		{
			//pop until we find a node has chance to try
			while(curNode.triedTime == 4 && !posStack.empty())
			{
				curPos = posStack.top();
				posStack.pop();
				curNode = cellArray[curPos.row*colCnt+curPos.col];
				resultPair.second.push_back(curPos);
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

//unit test
/*
int main(int argc, char *argv[])
{
	string mapFileName;
	if (argc == 2)
	{
		mapFileName = string(argv[1]);
	}
	else
	{
		std::cout<<"input maze map file name: "<<std::endl;
		std::cin >> mapFileName;
	}
	ifstream mapStream;
	mapStream.open(mapFileName.c_str());
	Maze maze;
	if(!mapStream)
	{
		std::cerr<<" Could not open stream for reading: "<<mapFileName<<std::endl;
		return 1;
	}
	maze.initializeMap(mapStream);
	pair<list<Pos2D>,list<Pos2D>> resultPair;
	bool bsuccess = maze.getoutOfMaze3(maze.startPos,resultPair);
	//bool bsuccess = maze.getoutOfMaze(resultPair);
	std::cout<<std::endl<<"---Finding Process---"<<std::endl;
	if(bsuccess && resultPair.second.back() != maze.exitPos) {
		resultPair.second.push_back(maze.exitPos);
	}
	if(bsuccess && resultPair.first.back() != maze.exitPos) {
			resultPair.first.push_back(maze.exitPos);
	}
	std::copy(resultPair.second.begin(),resultPair.second.end(),
					std::ostream_iterator<Pos2D>(std::cout,"\t"));
	std::cout<<std::endl<<"---Sum: "<<resultPair.second.size()-1<<" steps---" <<std::endl;
    if(bsuccess)
	{

        std::cout<<"Get out by "<<resultPair.first.size()<<" steps: "<<std::endl;
		std::copy(resultPair.first.begin(),resultPair.first.end(),
					std::ostream_iterator<Pos2D>(std::cout,"\t\t"));
		std::cout<<std::endl;
	}else
	{
          std::cout<<"No Path to get out!"<<std::endl;
	}
	char waitkey;
	std::cout<<"Press any key to continue"<<std::endl;
	std::cin>>waitkey;
	return 0;
}
*/
