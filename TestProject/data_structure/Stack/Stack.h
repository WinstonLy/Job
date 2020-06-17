#ifndef __STACK__H__
#define __STACK__H__

typedef int Elem;
class Stack
{
public:
    Stack(int _size);
    ~Stack();
    bool StackEmpty();
    void ClearStack();
    bool PushStack(Elem &_elem);
    bool PopStack(Elem &_elem);
    bool GetTopStack(Elem &_elem);

private:
    int m_iTop;
    int m_iSize;
    int m_iLength;
    Elem *m_pElem;
};


#endif