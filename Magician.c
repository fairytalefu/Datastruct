/*************************************************************************
    > File Name: Magician.c ---> 1 8 2 5 10 3 12 11 9 4 7 6 13
    > Author: sfp&fly
    > Mail: fairytalefu@outlook.com
    > Created Time: Fri 29 Jul 2016 23:17:03 AM CST
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define Cardnumber 13

typedef struct Node
{
    int data;
    struct Node * next;
}Sqlist,*LinkList;

LinkList CreateList()
{
    LinkList head = NULL;
    LinkList s,r;
    int i;
    r = head;
    for(i = 1; i <= Cardnumber; i++)
    {
        s = (LinkList)malloc(sizeof(Sqlist));
        s->data = 0;
        if(head == NULL)
            head = s;
        else
            r->next = s;
        r = s;
    }
    r->next = head;
    return head;
}
void Magician(LinkList head)
{
    LinkList p = head;
    int CountNumber = 2;
    int i;
    p->data = 1;//第一次发牌

    for(CountNumber = 2; CountNumber <= Cardnumber; CountNumber++)
    {
        i = 0;
        while(i < CountNumber)
        {
            p = p->next;
            if(p->data == 0) ++i;      //该位置有牌应该跳过
        }
        p->data = CountNumber;
    }


}
void Magician_err_mend(LinkList head)
{
    LinkList p = head;
    int j;
    int CountNumber = 2;
    p->data = 1;//第一次发牌

    while(1)
    {
        for(j = 0; j < CountNumber; j++)
        {
            p = p->next;
            if(p->data != 0)
            {
                //p = p->next;
                j--;
                continue;
            }

        }
        if(p->data == 0)
        {
            p->data = CountNumber;
            CountNumber++;
            if(CountNumber == 14)
                break;
        }
    }
}
void DestroyList(LinkList *L)
{
    LinkList ptr = *L;
    LinkList buff[Cardnumber];
    int i = 0;
    while(i < Cardnumber)
    {
        buff[i++] = ptr;
        ptr = ptr->next;
    }
    for(i = 0; i < Cardnumber; ++i)
        free(buff[i]);
    *L = 0;
}
int main()
{
    LinkList p;
    int i;
    p = CreateList();
    Magician_err_mend(p);

    printf("按如下顺序排列!\n");
    for(i  =0; i < Cardnumber; i++)
    {
        printf("黑桃%d ", p->data);
        p = p->next;
    }
    DestroyList(&p);
    return 0;
}
