/********************************************************************************
FileName:SqList.c
Author:fly
Email:fairytalefu@outlook.com
Time:13:03 pm 2016.4.3
********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef struct
{
    int *elem;
    int length;
    int listsize;
}Sqlist;
int init_list(Sqlist *L)
{
    (*L).elem = (int *)malloc(LIST_INIT_SIZE * sizeof(int));
    (*L).length = 0;
    (*L).listsize = LIST_INIT_SIZE;
    return 1;
}
void CreateList(Sqlist *L)
{
    int i;
    printf("Please enter the elem number:\n");
    scanf("%d",&(*L).length);
    printf("Please enter the elem of th sqlist:\n");
    for(i = 0; i <(*L).length; i++)
        scanf("%d",&(*L).elem[i]);
    printf("\n");
}
void print(Sqlist L)
{
    int i;
    for(i = 0; i < L.length; i++)
        printf("%d",L.elem[i]);
    printf("\n");
}
int location(Sqlist *L, int e)
{
    int i;
    i = 0;
    while((*L).elem[i] != e && i <(*L).length)
        i++;
    if (i > (*L).length)
        return -1;
    else
        return i + 1;

}
int List_Insert(Sqlist * L, int pos, int e)
{
   int *newbase, *q, *p;
   if (pos < 1 || pos > (*L).length + 1)
        return 0;
   if((*L). length >= (*L).listsize)
   {
       newbase = (int *)realloc((*L).elem, ((*L).listsize + LISTINCREMENT) * sizeof(int));
       (*L).elem = newbase;
       (*L).listsize += LISTINCREMENT;
   }
   q = &(*L).elem[pos - 1];
   for ( p = &(*L).elem[(*L).length - 1]; p >= q; --p)
        *(p+1) = *p;
   *q = e;
   ++(*L).length;
   return 1;
}
int List_Del(Sqlist *L, int pos, int e)
{
    int *q, *p;
    if (pos < 1 || pos > (*L).length)
        return 0;
    p = &(*L).elem[pos -1];
    e = *p;
    q = (*L).elem + (*L).length - 1;
    for (++p; p <= q; ++p)
        *(p-1) = *p;
    --(*L).length;
    return 1;
}

void Combine(Sqlist la, Sqlist lb, Sqlist *ld)
{
    int *pa_last, *pb_last, *pa, *pb, *pc;
    pa = la.elem;
    pb = lb.elem;
    (*ld).listsize = (*ld).length = la.length + lb.length;
    pc = (*ld).elem = (int *) malloc ((*ld).listsize * sizeof(int));
    pa_last = la.elem + la.length - 1;
    pb_last = lb.elem + lb.length - 1;
    while (pa < pa_last && pb <= pb_last)
    {
        if(*pa <= *pb)
            *pc++ = *pa++;
        else
            *pc++ = *pb++;
    }
    while (pa <= pa_last)
        *pc++ = *pa++;
    while (pb <= pb_last)
        *pc++ = *pb++;
}
int main(void)
{
    Sqlist lc,ld,lb,la;
    int e,locale,pos,elem;
    init_list(&lc);
    CreateList(&lc);
    print(lc);
    printf("Please enter the elem your want to find:\n");
    scanf("%d",&e);
    locale = location(&lc, e);
    printf("the location of elem is %d\n",locale);
    printf("Please enter the insert position and the elem:\n");
    scanf("%d%d",&pos,&elem);
    List_Insert(&lc,pos,elem);
    printf("after insert elem ,the Sqlist is:\n");
    print(lc);


    printf("Please enter the insert position and the elem:\n");
    scanf("%d%d",&pos,&elem);
    List_Del(&lc,pos,elem);
    printf("after delete elem ,the Sqlist is:\n");
    print(lc);

    init_list(&ld);
    init_list(&la);
    CreateList(&la);
    init_list(&lb);
    CreateList(&lb);
    Combine(la,lb,&ld);
    print(ld);

    return 0;
}
