#include <iostream>
#include <stack>
#include <math.h>

using namespace std;

int main(){
    struct Record{
        float val;
    };

    Record temp;
    

    stack<Record> build_stack;
    build_stack.push({val:10.22});

    temp = build_stack.top();
    cout << temp.val << endl;
    float a;
    a = INFINITY;
    cout << a  << (a>100000000) << endl;

}