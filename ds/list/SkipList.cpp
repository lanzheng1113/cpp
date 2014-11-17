#include <iostream>
#include "SkipList.h"

template<class T>
SkipList<T>::SkipList():maxLevel(1)
{
   head = new SkipNode<T>();
}

template<class T>
SkipList<T>::~SkipList()
{   
	//free space at level 1
    SkipNodePtr pCurHead = head->next[0];
    while(pCurHead != 0)
	{
            SkipNodePtr pTmp = pCurHead->next[0];
			delete pCurHead;
			pCurHead = pTmp;
	}
	delete head;
	head = 0;
	std::cout<<"Free SkipList space"<<std::endl;
}

template<class T>
T* SkipList<T>::find(const T& key)
{
     int curLevel = maxLevel;
	 SkipNodePtr pCur = head;
	 while(curLevel > 0)
	 {
		while(pCur->next[curLevel-1] != 0 && pCur->next[curLevel-1]->key < key)
			pCur = pCur->next[curLevel-1];
		if(pCur->next[curLevel-1] != 0 && pCur->next[curLevel-1]->key == key)
			return &pCur->next[curLevel-1]->key;//if match ,return immediately
        curLevel--;//search down layer
	 }
	 return 0;
}

template<class T>
bool SkipList<T>::insert(const T& key)
{   
	SkipNodePtr priorInsertPos[MAX_LEVEL];
	int curLevel = maxLevel;
	SkipNodePtr pCur = head;
	while(curLevel > 0)
	{
		while(pCur->next[curLevel-1] != 0 
			&& pCur->next[curLevel-1]->key < key)
			  pCur = pCur->next[curLevel-1];
		if(pCur->next[curLevel-1] != 0
			&& pCur->next[curLevel-1]->key == key)
			return false;//if already exsit ,return false
		priorInsertPos[curLevel-1] = pCur;//store insert position
		curLevel--;//search down layer
    }
    int levelCnt = getRandomLevel();//get random level count
    SkipNodePtr pInsert = new SkipNode<T>(key);
	//insert new node from level 1 to levelCnt
	for(int i = 1;i <= levelCnt;i++)
	{
		if(i > maxLevel)
		{
			head->next[i-1] = pInsert;
		}else
		{
            pInsert->next[i-1] = priorInsertPos[i-1]->next[i-1];
			priorInsertPos[i-1]->next[i-1] = pInsert;
		}
	}
	if(levelCnt > maxLevel)
		maxLevel = levelCnt; //update max level
	return true;
}

template<class T>
bool SkipList<T>::remove(const T& key)
{
    SkipNodePtr priorRemovePos[MAX_LEVEL];
	SkipNodePtr pRemove = 0;
	int curLevel = maxLevel;
	int startFindLevel = -1; //-1 represent not find
	//search all levels,record position prior to remove
	SkipNodePtr pCur = head;
	while(curLevel > 0)
	{   
		while(pCur->next[curLevel-1] != 0 && pCur->next[curLevel-1]->key < key)
			  pCur = pCur->next[curLevel-1];
		if(pCur->next[curLevel-1] != 0 && pCur->next[curLevel-1]->key == key)
		{   
			if(startFindLevel == -1)
			{
				startFindLevel = curLevel;
				pRemove = pCur->next[curLevel-1];
			}
			priorRemovePos[curLevel-1] = pCur;//store pos prior to remove
		}
		curLevel--;//search down layer
    }
    if(startFindLevel == -1)
	   return false;
	//update the reference pointer
    for(int i = startFindLevel;i > 0;i--)
	{
		  priorRemovePos[i-1]->next[i-1] = pRemove->next[i-1];
		  if(pRemove->next[i-1] == 0)
			  maxLevel--;  // reduce one level,update maxLevel
	}
	//delete the node only onece
	delete pRemove;
	return true;
}

template<class T>
bool SkipList<T>::isEmpty()
{
     return head->next[0] == 0 ;
}

template<class T>
int SkipList<T>::getRandomLevel()
{
    int k=1;
    while (rand()%2)
        k++;
    k=(k<MAX_LEVEL)?k:MAX_LEVEL;
    return k;
}
//for debuging only
template<class T>
void SkipList<T>::print()
{
   if(isEmpty())
   {
	   std::cout<<"SkipList []"<<std::endl;
   }else
   {  
	  int level = maxLevel;
	  std::cout<<"-----------------------------------"<<std::endl;
	  std::cout<<"SkipList ["<<std::endl;
	  for(int i = maxLevel;i > 0;i--)
	  {
		  std::cout<<i<<" :  ";
		  SkipNodePtr pHead = head->next[i-1];
		  while(pHead != 0)
		  {
			  std::cout<<pHead->key<<"  ";
              pHead = pHead->next[i-1];
		  }
		  if(i > 1)
			std::cout<<std::endl<<"|"<<std::endl<<"|"<<std::endl;
	  }
	  std::cout<<std::endl<<"]"<<std::endl;
	  std::cout<<"-----------------------------------"<<std::endl;
   }
}
