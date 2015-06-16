#include <iostream>
#include <set>

using namespace std;

class StudentT {

public:
    int id;
    string name;
public:
    StudentT(int _id, string _name) : id(_id), name(_name) {
    }
    int getId() {    //  应该声明为const成员
        return id;
    }
    string getName() { // 应该声明为const成员
        return name;
    }
};

inline bool operator< (StudentT s1, StudentT s2) {
    return  s1.getId() < s2.getId();
}

int main() {

    set<StudentT> st;
    StudentT s1(0, "Tom");
    StudentT s2(1, "Tim");
    st.insert(s1);
    st.insert(s2);
    set<StudentT> :: iterator itr;
    for (itr = st.begin(); itr != st.end(); itr++) {
        cout << itr->getId() << " " << itr->getName() << endl;
    }
    return 0;
}
