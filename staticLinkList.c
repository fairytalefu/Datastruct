/*************************************************************************
    > File Name: static.c
    > Author: sfp&fly
    > Mail: fairytalefu@outlook.com
    > Created Time: Fri 29 Jul 2016 11:17:03 AM CST
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR -1

#define MAX_SIZE 100
typedef int ElemType;
typedef int Status;

typedef struct
{
    ElemType data;
    int cur;
}Component, StaticLinkList[MAX_SIZE];

//静态链表的初始化：

Status InitList(StaticLinkList space)
{
    int i;
    for(i = 0 ; i < MAX_SIZE-1 ; ++i)
    {
        space[i].cur = i+1;
    }
    space[MAX_SIZE-1].cur  = 0;

    return OK;
}
/*如果要插入新的结点到静态链表中，
 *首先需要得到一个备用链表的位置来
 *存放新的结点，malloc_ssl就是得到
 *一个备用链表的下标，并且返回。
 */
int Malloc_SSL(StaticLinkList space)
{
    //得到第一个结点的下标
    int i = space[MAX_SIZE-1].cur ;
    if(space[0].cur)                                                   //如果存在备用链表
    {
        //得到备用链表的第一个结点的下标
        i = space[0].cur ;
    }
    //备用结点的第一个结点将被使用，于是备用结点小标往后一个结点移动
    space[0].cur = space[i].cur ;
    return i ;
}
//其中Free_SSL就是将该下标的结点放到备用链表中去。
void Free_SSL(StaticLinkList space, int i)
{
    //将之前的备用链表的第一个结点的小标存入到L[i]的cur中
    space[i].cur  = space[0].cur;
    //下标为i的元素成为备用链表的第一个结点
    space[0].cur = i;
}
int GetListLength(StaticLinkList L) //返回链表的当前长度
{
    int j = 0;
    int k = L[MAX_SIZE - 1].cur;
    while(k)
    {
        ++j;
        k = L[k].cur;
    }
    return j;
}
//插入新结点操作：
Status InserList(StaticLinkList L ,int i ,ElemType e)
{
    int k = MAX_SIZE-1 ;
    int m;
    if( i < 1 || i >GetListLength(L)+1)
       return ERROR ;
    //得到备用链表的第一个元素
    int j = Malloc_SSL(L);
    if (j)//如果元素存在
    {
        L[j].data = e ;
        //得到第i-1个元素的下标
        for(m = 1 ; m < i ; ++m)
            k = L[k].cur ;
        /*将第i-1个元素的cur设置为新加的这个结点的下标，
         *将新加的这个结点的下标设置为之前第i-1个元素存储的cur值
         */
        L[j].cur = L[k].cur;
        L[k].cur = j;
        return OK;
    }
    return ERROR;
}

//删除静态链表中的元素:
Status DeleteLinkList(StaticLinkList L, int i)
{
    if(i < 1 || i > GetListLength(L))
        return ERROR;
    int k = MAX_SIZE - 1;
    int j;
    for(j = 1 ; j < i ; ++j)//找到第i-1个元素
    {
        k = L[k].cur;
    }
    j = L[k].cur ;//得到第i个元素的下标
    L[k].cur = L[j].cur ;//将第i个元素存储的cur值赋值给第i-1个元素的cur
    Free_SSL(L ,  j);//释放掉第i个元素，第i个元素的下标为j
    return OK;
}

void Print(StaticLinkList L) //打印链表
{
    int k = L[MAX_SIZE - 1].cur;
    while(k)
    {
        printf("%d ",L[k].data);
        k = L[k].cur;
    }
    printf("\n");
}
int main()
{
    StaticLinkList L;
    int i;
    InitList(L);
    for(i = 1; i < 10; i++)
        InserList(L, i, i);
    Print(L);
    DeleteLinkList(L,4);
    Print(L);
    return 0;
}
