#ifndef _SKIP_LIST_
#define _SKIP_LIST_

#define MAX_LEVEL 16

template<class T>
class SkipNode
{
public:
    SkipNode()
	{
		for(int i = 0;i < MAX_LEVEL ;i++)
			next[i] = 0;
    }
    SkipNode(T k):key(k)
	{
       for(int i = 0;i < MAX_LEVEL ;i++)
			next[i] = 0;
	}
public:
	T key;
    SkipNode* next[MAX_LEVEL];
};

template<class T>
class SkipList
{
public:
	 SkipList();
	 ~SkipList();
	 T* find(const T& key);
     bool insert(const T& key);
	 bool remove(const T& key);
	 bool isEmpty();
	 void print();
private:
	int getRandomLevel();
private:
    int maxLevel;
	typedef SkipNode<T>* SkipNodePtr;
    SkipNodePtr head;
};
#endif
