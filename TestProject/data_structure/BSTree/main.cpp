#include <iostream>
#include "Tree.h"

using namespace std;

int main(void)
{
    BSTree *s = new BSTree();
    cout << "Please input node" << endl;
    int a;
    while(cin >> a)
    {
        s->insert(a);
    }
    cin.clear();

    cout << "PreOrder " << endl;
    s->preOrder();

    return 0;

}