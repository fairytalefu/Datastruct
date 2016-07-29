/*************************************************************************
    > File Name: echoList.c --->判断单链表是否有环
    > Author: sfp&fly
    > Mail: fairytalefu@outlook.com
    > Created Time: Fri 29 Jul 2016 11:17:03 AM CST
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR -1

typedef int Status;
typedef int ElemType;

typedef struct LNode
{
    int     data;
    struct LNode    *next;
}LNode, *LinkedList;

//尾插法
LinkedList CreateListTail(LinkedList *L, int n)
{
    LinkedList p,r;
    int i;
    *L = (LinkedList)malloc(sizeof(LNode));
    r = *L;
    for(i = 0; i < n; i++)
    {
        p = (LinkedList)malloc(sizeof(LNode));
        p->data = i;
        r->next = p;
        r = p;
    }
    r->next = (*L)->next->next;
    return *L;
}


//比较步数法
int Hasloop1(LinkedList L)
{
    LinkedList cur1 = L;//定义节点cur1
    int pos1 = 0;
    while(cur1)
    {
        LinkedList cur2 = L;
        int pos2 = 0;
        while(cur2)
        {
            if(cur2 == cur1)
            {
                if(pos1 == pos2)
                    break;
                else
                {
                    printf("环的位置在第%d个节点处。\n\n",pos2);
                    return OK;
                }
            }
            cur2 = cur2->next;
            pos2++;
        }
        cur1 = cur1->next;
        pos1++;
    }
    return 0;
}
//利用快慢指针的方法
int Hasloop2(LinkedList L)
{
    LinkedList p =L;
    LinkedList q = L;
    int pos = 0;
    while(p != NULL && q != NULL && q->next != NULL)
    {
        p = p->next;
        pos++;
        if(q->next->next != NULL)
            q = q->next->next;
        printf("p:%d, q:%d\n",p->data,q->data);
        if(p == q)
        {
         //   printf("环的位置在第%d个节点处。\n\n",pos);
            return OK;
        }

    }
    return 0;
}
int main(void)
{
    int loop1,loop2;
    LinkedList L;
    CreateListTail(&L, 10);
    //ListTraverse(L);
    loop1 = Hasloop1(L);
    if(loop1)
        printf("结论：链表有环！\n");
    else
        printf("结论：链表无环！\n\n\t");

    loop2 = Hasloop2(L);
    if(loop2)
        printf("结论：链表有环！\n");
    else
        printf("结论：链表无环！\n");
    return 0;
}


