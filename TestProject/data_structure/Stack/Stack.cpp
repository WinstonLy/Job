#include "Stack.h"
#include <cstdlib>
Stack::Stack(int _size)
{
    m_iSize = _size;
    m_iTop = 0;
    m_iLength = 0;
    m_pElem = new Elem(m_iSize);

}
Stack::~Stack()
{
    delete m_pElem;
    m_pElem = NULL;
}
bool Stack::StackEmpty()
{
    if(m_iLength == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}
void Stack::ClearStack()
{
    m_iLength = 0;
    m_iTop = 0;
}

bool Stack::PushStack(Elem &_elem)
{
    if(m_iTop >= m_iSize)
    {
        return false;
    }

    m_pElem[++m_iTop] = _elem;
    
    ++m_iLength;
    return true;
}

bool Stack::PopStack(Elem &_elem)
{
    if(m_iTop == 0)
    {
        return false;
    }
    
    _elem = m_pElem[m_iTop];
    --m_iTop;
    --m_iLength;
    return true;

}
bool Stack::GetTopStack(Elem &_elem)
{
    if(m_iTop == 0)
    {
        return false;
    }
    
    _elem = m_pElem[m_iTop];

    return true;
}