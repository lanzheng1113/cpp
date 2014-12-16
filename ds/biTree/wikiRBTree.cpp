
/***
来自: http://zh.wikipedia.org/wiki/红黑树
****/
#define BLACK 1
#define RED 0

#include <iostream>
using namespace std;
 
class bst {
private:
 
    struct Node {
        int value;
        bool color;
        Node *leftTree, *rightTree, *parent;
 
        Node() {
            color = RED;
            leftTree = NULL;
            rightTree = NULL;
            parent = NULL;
            value = 0;
        }
 
        Node* grandparent() {
            if (parent == NULL) {
                return NULL;
            }
            return parent->parent;
        }
 
        Node* uncle() {
            if (grandparent() == NULL) {
                return NULL;
            }
            if (parent == grandparent()->rightTree)
                return grandparent()->leftTree;
            else
                return grandparent()->rightTree;
        }
 
        Node* sibling() {
            if (parent->leftTree == this)
                return parent->rightTree;
            else
                return parent->leftTree;
        }
    };
 
    void rotate_right(Node *p) {
        Node *gp = p->grandparent();
        Node *fa = p->parent;
        Node *y = p->rightTree;
 
        fa->leftTree = y;
 
        if (y != NIL)
            y->parent = fa;
        p->rightTree = fa;
        fa->parent = p;
 
        if (root == fa)
            root = p;
        p->parent = gp;
 
        if (gp != NULL) {
            if (gp->leftTree == fa)
                gp->leftTree = p;
            else
                gp->rightTree = p;
        }
 
    }
 
    void rotate_left(Node *p) {
        if (p->parent == NULL) {
            root = p;
            return;
        }
        Node *gp = p->grandparent();
        Node *fa = p->parent;
        Node *y = p->leftTree;
 
        fa->rightTree = y;
 
        if (y != NIL)
            y->parent = fa;
        p->leftTree = fa;
        fa->parent = p;
 
        if (root == fa)
            root = p;
        p->parent = gp;
 
        if (gp != NULL) {
            if (gp->leftTree == fa)
                gp->leftTree = p;
            else
                gp->rightTree = p;
        }
    }
 
    void inorder(Node *p) {
        if (p == NIL)
            return;
 
        if (p->leftTree)
            inorder(p->leftTree);
 
        cout << p->value <<"-"<<outputColor(p->color)<<"\t";
 
        if (p->rightTree)
            inorder(p->rightTree);
    }
 
    string outputColor(bool color) {
        return color ? "BLACK" : "RED";
    }
 
    Node* getSmallestChild(Node *p) {
        if (p->leftTree == NIL)
            return p;
        return getSmallestChild(p->leftTree);
    }
 
    bool delete_child(Node *p, int data) {
        if (p->value > data) {
            if (p->leftTree == NIL) {
                return false;
            }
            return delete_child(p->leftTree, data);
        } else if (p->value < data) {
            if (p->rightTree == NIL) {
                return false;
            }
            return delete_child(p->rightTree, data);
        } else if (p->value == data) {
            if (p->rightTree == NIL) {
                delete_one_child(p);
                return true;
            }
            Node *smallest = getSmallestChild(p->rightTree);
            swap(p->value, smallest->value);
            delete_one_child(smallest);
 
            return true;
        }
    }
 
    void delete_one_child(Node *p) {
        Node *child = p->leftTree == NIL ? p->rightTree : p->leftTree;
        if (p->parent == NULL && p->leftTree == NIL && p->rightTree == NIL) {
            p = NULL;
            root = p;
            return;
        }
 
        if (p->parent == NULL) {
            delete  p;
            child->parent = NULL;
            root = child;
            root->color = BLACK;
            return;
        }
 
        if (p->parent->leftTree == p) {
            p->parent->leftTree = child;
        } else {
            p->parent->rightTree = child;
        }
        child->parent = p->parent;
 
        if (p->color == BLACK) {
            if (child->color == RED) {
                child->color = BLACK;
            } else
                delete_case(child);
        }
 
        delete p;
    }
 
    void delete_case(Node *p) {
        if (p->parent == NULL) {   // case 1
            p->color = BLACK;
            return;
        }
        if (p->sibling()->color == RED) {	// case 2
            p->parent->color = RED;
            p->sibling()->color = BLACK;
            if (p == p->parent->leftTree)
                rotate_left(p->sibling());
            else
                rotate_right(p->sibling());
        }
        if (p->parent->color == BLACK && p->sibling()->color == BLACK
                && p->sibling()->leftTree->color == BLACK && p->sibling()->rightTree->color == BLACK) { // case 3
            p->sibling()->color = RED;
            delete_case(p->parent);
        } else if (p->parent->color == RED && p->sibling()->color == BLACK
                && p->sibling()->leftTree->color == BLACK && p->sibling()->rightTree->color == BLACK) {	// case 4
            p->sibling()->color = RED;
            p->parent->color = BLACK;
        } else {
            if (p->sibling()->color == BLACK) {   // case 5
                if (p == p->parent->leftTree && p->sibling()->leftTree->color == RED
                        && p->sibling()->rightTree->color == BLACK) {
                    p->sibling()->color = RED;
                    p->sibling()->leftTree->color = BLACK;
                    rotate_right(p->sibling()->leftTree);
                } else if (p == p->parent->rightTree && p->sibling()->leftTree->color == BLACK
                        && p->sibling()->rightTree->color == RED) {
                    p->sibling()->color = RED;
                    p->sibling()->rightTree->color = BLACK;
                    rotate_left(p->sibling()->rightTree);
                }
            }
	    //case 6
            p->sibling()->color = p->parent->color;
            p->parent->color = BLACK;
            if (p == p->parent->leftTree) {
                p->sibling()->rightTree->color = BLACK;
                rotate_left(p->sibling());
            } else {
                p->sibling()->leftTree->color = BLACK;
                rotate_right(p->sibling());
            }
        }
    }
 
    void insert(Node *p, int data) {
        if (p->value >= data) {
            if (p->leftTree != NIL)
                insert(p->leftTree, data);
            else {
                Node *tmp = new Node();
                tmp->value = data;
                tmp->leftTree = tmp->rightTree = NIL;
                tmp->parent = p;
                p->leftTree = tmp;
                insert_case(tmp);
            }
        } else {
            if (p->rightTree != NIL)
                insert(p->rightTree, data);
            else {
                Node *tmp = new Node();
                tmp->value = data;
                tmp->leftTree = tmp->rightTree = NIL;
                tmp->parent = p;
                p->rightTree = tmp;
                insert_case(tmp);
            }
        }
    }
 
    void insert_case(Node *p) {
        if (p->parent == NULL) {
            root = p;
            p->color = BLACK;
            return;
        }
        if (p->parent->color == RED) {
            if (p->uncle()->color == RED) {
                p->parent->color = p->uncle()->color = BLACK;
                p->grandparent()->color = RED;
                insert_case(p->grandparent());
            } else {
                if (p->parent->rightTree == p && p->grandparent()->leftTree == p->parent) {
                    rotate_left(p);
                    rotate_right(p);
                    p->color = BLACK;
                    p->leftTree->color = p->rightTree->color = RED;
                } else if (p->parent->leftTree == p && p->grandparent()->rightTree == p->parent) {
                    rotate_right(p);
                    rotate_left(p);
                    p->color = BLACK;
                    p->leftTree->color = p->rightTree->color = RED;
                } else if (p->parent->leftTree == p && p->grandparent()->leftTree == p->parent) {
                    p->parent->color = BLACK;
                    p->grandparent()->color = RED;
                    rotate_right(p->parent);
                } else if (p->parent->rightTree == p && p->grandparent()->rightTree == p->parent) {
                    p->parent->color = BLACK;
                    p->grandparent()->color = RED;
                    rotate_left(p->parent);
                }
            }
        }
    }
 
    void DeleteTree(Node *p) {
        if (!p || p == NIL) {
            return;
        }
        DeleteTree(p->leftTree);
        DeleteTree(p->rightTree);
        delete p;
    }
public:
 
    bst() {
        NIL = new Node();
        NIL->color = BLACK;
        root = NULL;
    }
 
    ~bst() {
        if (root)
            DeleteTree(root);
        delete NIL;
    }
 
    void inorder() {
        if (root == NULL)
            return;
        inorder(root);
        cout << endl;
    }
 
    void insert(int x) {
        if (root == NULL) {
            root = new Node();
            root->color = BLACK;
            root->leftTree = root->rightTree = NIL;
            root->value = x;
        } else {
            insert(root, x);
        }
    }
 
    bool delete_value(int data) {
        return delete_child(root, data);
    }
private:
    Node *root, *NIL;
};
int main()
{
    bst  tree;
    int elements[] = {12,1,9,2,0,11,7,19, 4 ,15,18,5,14,13,10,16,6,3,8,17};
    int count = sizeof(elements) / sizeof(int);
    for(int i=0;i < count ;++i) {
		 tree.insert(elements[i]);
		 //std::cout<<"inserted: "<<elements[i]<<",traverse: "<<std::endl;
		 //tree.inorder();
		 //std::cout<<std::endl;
    }
    for(int i=0;i < count ;++i) {
		 tree.delete_value(elements[i]);
		 std::cout<<"remove: "<<elements[i]<<",traverse: "<<std::endl;
		 tree.inorder();
		 std::cout<<std::endl;
    }
}
