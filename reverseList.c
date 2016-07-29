/*************************************************************************
    > File Name: reverseList.c
    > Author: sfp&fly
    > Mail: fairytalefu@outlook.com
    > Created Time: Fri 29 Jul 2016 16:17:03 AM CST
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

//头插法
void CreateListHead(LinkedList *L, int n)
{
    LinkedList p;
    int i;
    *L = (LinkedList)malloc(sizeof(LNode));
    (*L)->next = NULL;
    for(i = 0; i < n; i++)
    {
        p = (LinkedList)malloc(sizeof(LNode));
        p->data = i;
        p->next = (*L)->next;
        (*L)->next = p;
    }

}
//尾插法
void CreateListTail(LinkedList *L, int n)
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
    r->next = NULL;
}
/* 初始条件：顺序线性表L已存在。操作结果：返回L中数据元素个数 */
int ListLength(LinkedList L)
{
    int i=0;
    LinkedList p=L->next; /* p指向第一个结点 */
    while(p)
    {
        i++;
        p=p->next;
    }
    return i;
}

Status visit(ElemType c)
{
    printf("-> %d ",c);
    return OK;
}
/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
Status ListTraverse(LinkedList L)
{
    LinkedList p=L->next;
    while(p)
    {
        visit(p->data);
        p=p->next;
    }
    printf("\n");
    return OK;
}



//第一种方法就是重新建立一个单链表newList，每次将list中的第一个结点放到newList后面
LinkedList ReverseSinglyLinkedList_1(LinkedList *list)
{
    LinkedList  *newList;    //新链表的头结点
    LNode       *tmp;       //指向list的第一个结点，也就是要摘除的结点

    //
    //参数为空或者内存分配失败则返回NULL
    //
    if (*list == NULL || ((*newList) = (LinkedList)malloc(sizeof(LNode))) == NULL)
    {
        return NULL;
    }

    //
    //初始化newList
    //
    (*newList)->data = (*list)->data;
    (*newList)->next = NULL;

    //
    //依次将list的第一个结点放到newList的第一个结点位置
    //
    while ((*list)->next != NULL)
    {
        tmp = (*newList)->next;         //保存newList中的后续结点
        (*newList)->next = (*list)->next;       //将list的第一个结点放到newList中
        (*list)->next = (*list)->next->next;     //从list中摘除这个结点
        (*newList)->next->next = tmp;        //恢复newList中后续结点的指针
    }

    //
    //原头结点应该释放掉，并返回新头结点的指针
    //
    free(*list);
    return *newList;
}

//第二种方法是每次都将原第一个结点之后的那个结点放在list后面
LinkedList ReverseSinglyLinkedList_2(LinkedList list)
{
    LNode   *tmp = NULL;
    LNode   *p = NULL;

    if (list == NULL)
    {
        return NULL;
    }
    tmp = list->next;
    while (tmp->next != NULL)
    {
        p = tmp->next;
        tmp->next = p->next;
        p->next = list->next;
        list->next = p;
    }
    return list;
}

void reverse(LinkedList L)
{
    LNode *p,*q;
    p = L->next;
    L->next = NULL;
    while(p != NULL)
    {
        q = p->next;
        p->next = L->next;
        L->next = p;
        p = q;
    }
}
/* 初始条件：顺序线性表L已存在,1≤i≤ListLength(L)， */
/* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
Status ListInsert(LinkedList *L,int i,ElemType e)
{
	int j;
	LinkedList p,s;
	p = *L;     /* 声明一个结点 p，指向头结点 */
	j = 1;
	while (p && j < i)     /* 寻找第i个结点 */
	{
		p = p->next;
		++j;
	}
	if (!p || j > i)
		return ERROR;   /* 第i个元素不存在 */
	s = (LinkedList)malloc(sizeof(LNode));  /*  生成新结点(C语言标准函数) */
	s->data = e;
	s->next = p->next;      /* 将p的后继结点赋值给s的后继  */
	p->next = s;          /* 将s赋值给p的后继 */
	return OK;
}

/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
Status ListDelete(LinkedList *L,int i,ElemType *e)
{
	int j;
	LinkedList p,q;
	p = *L;
	j = 1;
	while (p->next && j < i)	/* 遍历寻找第i个元素 */
	{
        p = p->next;
        ++j;
	}
	if (!(p->next) || j > i)
	    return ERROR;           /* 第i个元素不存在 */
	q = p->next;
	p->next = q->next;			/* 将q的后继赋值给p的后继 */
	*e = q->data;               /* 将q结点中的数据给e */
	free(q);                    /* 让系统回收此结点，释放内存 */
	return OK;
}

/*********快速找到单链表的中间元素*******/
int GetMidNode(LinkedList L, int * e)
{
    LinkedList search,mid;
    mid = search = L;
    while(search->next != NULL)
    {
        if(search->next->next != NULL)
        {
            search = search->next->next;
            mid = mid->next;
        }
        else
            search = search->next;
    }
    *e = mid->data;
    return *e;
}
//删除重复结点的算法
LinkedList RemoveDupNode(LinkedList L)
{
    LinkedList p,q,r;
    p=L->next;
    // p用于遍历链表
    while(p)
    {
        q=p;
        // q遍历p后面的结点，并与p数值比较
        while(q->next)
        {
            if(q->next->data==p->data)
            {
                // r保存需要删掉的结点
                r=q->next;
                // 需要删掉的结点的前后结点相接
                q->next=r->next;
                free(r);
            }
            else
                q=q->next;
        }
        p=p->next;
    }
    return L;
}
int main()
{
    LinkedList L,ls;
    int e,mid,length;
    printf("头插法----> L.\n");
    printf("L:\n");
    CreateListHead(&L, 11);
    ListTraverse(L);
    length = ListLength(L);
    printf("L的长度：%d\n",length);

    printf("尾插法----> ls.\n");
    printf("ls:\n");
    CreateListTail(&ls, 10);
    ListTraverse(ls);
    length = ListLength(ls);
    printf("ls的长度：%d\n",length);

    printf("L的第2个位置插入99:\n");
    ListInsert(&L,2,99);
    ListTraverse(L);
    length = ListLength(L);
    printf("L的长度：%d\n",length);

    printf("ls的第2个位置插入100:\n");
    ListInsert(&ls,2,100);
    ListTraverse(ls);
    length = ListLength(ls);
    printf("ls的长度：%d\n",length);

    printf("删除L第2个位置的数:\n");
    ListDelete(&L,2,&e);
    ListTraverse(L);
    length = ListLength(L);
    printf("L的长度：%d\n",length);
    printf("删除ls第2个位置的数:\n");
    ListDelete(&ls,2,&e);
    ListTraverse(ls);
    length = ListLength(ls);
    printf("ls的长度：%d\n",length);

    printf("方法1_逆置单链表L：\n");
    reverse(L);
    //ReverseSinglyLinkedList_1(&L);
    ListTraverse(L);
    printf("方法2_逆置单链表ls：\n");
    ReverseSinglyLinkedList_2(ls);
    ListTraverse(ls);

    printf("快速找到单链表中的中间值：\n");
    printf("L中间值 mid = %d\n",GetMidNode(L, &mid));
    printf("ls中间值 mid = %d\n",GetMidNode(ls, &mid));

    printf("删除L重复值：\n");
    ListInsert(&L,2,2);
    ListTraverse(L);
    RemoveDupNode(L);
    ListTraverse(L);
    printf("Hello world!\n");
    return 0;
}
