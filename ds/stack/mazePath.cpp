#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <iterator>     // std::ostream_iterator

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
	static Pos2D NotAvailablePos;
    int row,col;
};
ostream& operator <<(ostream& os,const Pos2D &  pos)
{
	os<<"("<<pos.row<<","<<pos.col<<")";
	return os;
}
Pos2D Pos2D::NotAvailablePos = Pos2D(-1,-1);

class Node
{
public:
	Pos2D pos;
	bool isBlocked;
	int  triedTime;
	bool hasWalked;
};
Pos2D getFirstAvailablePos(Node *nodeArray,int colCnt,Pos2D curPos)
{   
	int row = curPos.row,col = curPos.col;
	int triedTime =  nodeArray[row*colCnt+col].triedTime;
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
		 Node& nextNode = nodeArray[firstAvailPos.row*colCnt+firstAvailPos.col];	
		 if(!nextNode.isBlocked && !nextNode.hasWalked)
		 {
			 bfind = true;
			 break;
		 }
		 triedTime++;
	}
	nodeArray[row*colCnt+col].triedTime = triedTime; //update tried time
	if(bfind)
		return firstAvailPos;
	else
		return  Pos2D::NotAvailablePos;
}
 bool getoutOfMaze(const vector<string> &mazeMapVec,pair<vector<Pos2D>,vector<string>>& resultPair)
{
    //Step1 initalize maze
	int rowCnt,colCnt;
	Pos2D curPos,exitPos;
	stack<Pos2D> posStack;
	rowCnt = mazeMapVec.size();
	colCnt = mazeMapVec[0].length();
	Node *nodeArray = new Node[rowCnt*colCnt];
	int row =0,col=0;
	for(const string& str: mazeMapVec)
	{   
		col = 0;
		for(char ch : str)
		{   
			int index = row*colCnt+col;

			nodeArray[index].pos = Pos2D(row,col);
			if(ch == 'm') 
			{
				curPos = nodeArray[index].pos;	// set as current pos(startPos)
			}else if(ch == 'e')
			{
				exitPos = nodeArray[index].pos; //set as exit pos
			}
			nodeArray[index].isBlocked = (ch == '1');
            nodeArray[index].hasWalked = false;
			nodeArray[index].triedTime = 0;
			++col;
		}
		++row;
	}
	resultPair.second.push_back("start: ("+std::to_string(curPos.row)+","+std::to_string(curPos.col)+")");
	//Step2 find path to get out
	bool bfind = false;
	do
	{   
		Node& curNode = nodeArray[curPos.row*colCnt+curPos.col];
		nodeArray[curPos.row*colCnt+curPos.col].hasWalked = true;
		//try at most four time(right left down up) to find a available neighbour node
		Pos2D nextAvailablePos = getFirstAvailablePos(nodeArray,colCnt,curPos);
		if(nextAvailablePos != Pos2D::NotAvailablePos)
		{   
			if(nextAvailablePos == exitPos) // successfully found path
			{
				resultPair.first.push_back(exitPos);
				resultPair.first.push_back(curPos);
				while(!posStack.empty())
				{
					resultPair.first.push_back(posStack.top());
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
				curNode = nodeArray[curPos.row*colCnt+curPos.col];
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

    delete[] nodeArray;	// release memory

    return bfind;
}
int main(int argc, char *argv[])
{  

	vector<string> mazeMapVec {
	    "11111111111"
        ,"10000010001"
        ,"10100010101"
        ,"e0100000101"
        ,"10111110101"
        ,"10101000101"
        ,"10001010001"
        ,"11111010001"
        ,"101m1010001"
        ,"10000010001"
        ,"11111111111"
	};
	pair<vector<Pos2D>,vector<string>> resultPair;
	bool bsuccess = getoutOfMaze(mazeMapVec,resultPair);
	std::cout<<std::endl<<"---Finding Process---"<<std::endl;
	std::copy(resultPair.second.begin(),resultPair.second.end(),
					std::ostream_iterator<string>(std::cout,"\n"));
	std::cout<<std::endl<<"---Sum: "<<resultPair.second.size()-1<<" steps---" <<std::endl;
    if(bsuccess)
	{   
        std::cout<<"Get out by :"<<std::endl;
		std::copy(resultPair.first.rbegin(),resultPair.first.rend(),
					std::ostream_iterator<Pos2D>(std::cout,"\n"));
		std::cout<<std::endl;
	}else
	{
          std::cout<<"No Path to get out!"<<std::endl;
	}
	return 0;
}