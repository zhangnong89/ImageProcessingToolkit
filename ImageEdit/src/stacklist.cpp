#include"stacklist.h"

int stackListIsEmpty(StackList *ps)
{
    if(ps->top == NULL && ps->num == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int stackListGetSizeOf(StackList *ps)
{
    return ps->num;
}

PNode stackListGetTop(StackList *ps, QString &pItem)
{
    if(stackListIsEmpty(ps) != 1 && pItem == NULL)
    {
        pItem = ps->top->element;
    }
    return ps->top;
}
PNode stackListPush(StackList *ps, QString &pItem,int flag)
{    
    PNode pNode = new node;
    QString temStr;
    if(pNode != NULL)
    {
        pNode->element=pItem;
        pNode->flag=flag;
        pNode->next=stackListGetTop(ps,temStr);
        ps->num++;
        ps->top = pNode;
    }
    return pNode;
}
PNode stackListPop(StackList *ps, QString &pItem)
{
    PNode p = ps->top;
    if(stackListIsEmpty(ps) != 1 && p != NULL)
    {
//        if(pItem != NULL)
//        {
            pItem = p->element;
//        }
        ps->num--;
        ps->top = ps->top->next;
        delete p;
    }
    return ps->top;
}
void stackListClear(StackList *ps)
{
    QString temStr;
    while (!stackListIsEmpty(ps))
    {
       stackListPop(ps,temStr);
    }
}
void stackListDestory(StackList *ps)
{
    if(stackListIsEmpty(ps) != 1)
    {
        stackListClear(ps);
    }
    delete ps;
}
