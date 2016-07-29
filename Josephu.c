/*************************************************************************
    > File Name: Josephu.c------>约瑟夫环
    > Author: sfp&fly
    > Mail: fairytalefu@outlook.com
    > Created Time: Fri 29 Jul 2016 11:17:03 AM CST
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
}Node,*ptrNode;

//不带头结点的循环链表
ptrNode create(int n)
{
    ptrNode p = NULL,head;
    head = (ptrNode)malloc(sizeof(Node));
    p = head;
    ptrNode s;
    int i = 1;
    if(0 != n)
    {
        while( i <= n)
        {
            s = (ptrNode)malloc(sizeof(Node));
            s->data = i++;
            p->next = s;
            p = s;
        }
        s->next = head->next;
    }
    free(head);
    return s->next;
}
int main(void)
{
    int n = 41;
    int m = 3;
    int i;
    ptrNode p = create(n);
    ptrNode temp;

    m %= n;

    while(p != p->next)
    {
        for(i = 1; i < m - 1; i++)
        {
            p = p->next;
        }
        printf("%d->",p->next->data);
        temp = p->next;
        p->next = temp->next;

        free(temp);
        p = p->next;
    }
    printf("%d\n",p->data);
    return 0;
}
