/*************************************************************************
    > File Name: echoList.c --->�жϵ������Ƿ��л�
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

//β�巨
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


//�Ƚϲ�����
int Hasloop1(LinkedList L)
{
    LinkedList cur1 = L;//����ڵ�cur1
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
                    printf("����λ���ڵ�%d���ڵ㴦��\n\n",pos2);
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
//���ÿ���ָ��ķ���
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
         //   printf("����λ���ڵ�%d���ڵ㴦��\n\n",pos);
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
        printf("���ۣ������л���\n");
    else
        printf("���ۣ������޻���\n\n\t");

    loop2 = Hasloop2(L);
    if(loop2)
        printf("���ۣ������л���\n");
    else
        printf("���ۣ������޻���\n");
    return 0;
}


