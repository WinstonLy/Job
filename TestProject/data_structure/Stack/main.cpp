#include "Stack.h"
#include <iostream>

using namespace std;

int main()
{
    Stack *s = new Stack(5);
    Elem e;
    Elem array[5] = {1, 2, 3, 4, 5};
    if(s == NULL)
    {
        cout << "初始化失败" << endl;
        return 0;
    }
    
    if(s->StackEmpty())
    {
        cout << "Stack Empty" << endl;
    }
    
    for(int i=0; i<5; ++i)
    {
        if(!s->PushStack(array[i]))
            cout << "push error" << endl;
    }

    if(s->StackEmpty())
    {
        cout << "Stack Empty" << endl;
    }
    for(int i=0; i<5; ++i)
    {
        if(!s->PopStack(e))
            cout << "Pop error" << endl;
        cout << 'e' << 5-i << ':' << e << endl;
    }
   
    
    if(s->StackEmpty())
    {
        cout << "Stack Empty" << endl;
    }

    delete s;
    s = NULL;
}