#include "Master.h"
using namespace std;
chrono::steady_clock::time_point start, end;
void print()
{
    long double timee = chrono::duration<long double, std::milli>(::end - ::start).count();
    cout << "\nTime for 12 insertions = " << timee << "\nTime taken per insertion = " << timee / 12;
    cout << "\nConstant = " << timee / (12 * log2(12));
}
int main()
{
    ::start = chrono::steady_clock::now();
    Rb_Tree<int> obj({10, 18, 7, 15, 16, 30, 25, 40, 60, 2, 1, 70});
    ::end = chrono::steady_clock::now();
    cout << '\n'
         << obj.root->value << '\n';
    // cout << '\n'
    //      << inorder_successor<int>(move(obj), 16)->value << '\n'
    //      << inorder_predecessor(move(obj), 16)->value << '\n';
    // atexit(print);
    // obj.inorder_traversal(obj.root);
    // Tree<int>o1=Rb_Tree<int>(1);
}

/*
    NODE<int> node(100);
    const NODE<int>* const n=&node;
    const NODE<int>* no=&node;
    n->value=101; no->value=1011; // Both these statements give compiler error.
    no=(NODE<int>*)1200; // Does not give an error.
    n=(NODE<int>*)1200;  // Gives compiler error.
*/