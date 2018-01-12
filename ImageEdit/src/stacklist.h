#ifndef STACKLIST
#define STACKLIST
#include "all.h"


typedef struct node *PNode;
struct node
{
    QString element;
/* flag = 0 means load a new picture
 * flag = 1 means the same picture
*/
    int flag;
    PNode next;
};

typedef struct stackList
{
    PNode top;
    int num;
}StackList;


/*check the stack is empty*/
int  stackListIsEmpty(StackList*ps);
/*obtain the size of the stack */
int  stackListGetSizeOf(StackList*ps);
/*get the top element*/
PNode stackListGetTop(StackList*ps,QString &pItem);
/*push a element to stack*/
PNode stackListPush(StackList*ps,QString &pItem,int flag);
/*obtain the latest element*/
PNode stackListPop(StackList*ps,QString &pItem);
/*clear the stack*/
void stackListClear(StackList*ps);
/*destory the stack*/
void stackListDestory(StackList*ps);


#endif // STACKLIST

