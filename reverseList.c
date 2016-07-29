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

//ͷ�巨
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
//β�巨
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
/* ��ʼ������˳�����Ա�L�Ѵ��ڡ��������������L������Ԫ�ظ��� */
int ListLength(LinkedList L)
{
    int i=0;
    LinkedList p=L->next; /* pָ���һ����� */
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
/* ��ʼ������˳�����Ա�L�Ѵ��� */
/* ������������ζ�L��ÿ������Ԫ����� */
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



//��һ�ַ����������½���һ��������newList��ÿ�ν�list�еĵ�һ�����ŵ�newList����
LinkedList ReverseSinglyLinkedList_1(LinkedList *list)
{
    LinkedList  *newList;    //�������ͷ���
    LNode       *tmp;       //ָ��list�ĵ�һ����㣬Ҳ����Ҫժ���Ľ��

    //
    //����Ϊ�ջ����ڴ����ʧ���򷵻�NULL
    //
    if (*list == NULL || ((*newList) = (LinkedList)malloc(sizeof(LNode))) == NULL)
    {
        return NULL;
    }

    //
    //��ʼ��newList
    //
    (*newList)->data = (*list)->data;
    (*newList)->next = NULL;

    //
    //���ν�list�ĵ�һ�����ŵ�newList�ĵ�һ�����λ��
    //
    while ((*list)->next != NULL)
    {
        tmp = (*newList)->next;         //����newList�еĺ������
        (*newList)->next = (*list)->next;       //��list�ĵ�һ�����ŵ�newList��
        (*list)->next = (*list)->next->next;     //��list��ժ��������
        (*newList)->next->next = tmp;        //�ָ�newList�к�������ָ��
    }

    //
    //ԭͷ���Ӧ���ͷŵ�����������ͷ����ָ��
    //
    free(*list);
    return *newList;
}

//�ڶ��ַ�����ÿ�ζ���ԭ��һ�����֮����Ǹ�������list����
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
/* ��ʼ������˳�����Ա�L�Ѵ���,1��i��ListLength(L)�� */
/* �����������L�е�i��λ��֮ǰ�����µ�����Ԫ��e��L�ĳ��ȼ�1 */
Status ListInsert(LinkedList *L,int i,ElemType e)
{
	int j;
	LinkedList p,s;
	p = *L;     /* ����һ����� p��ָ��ͷ��� */
	j = 1;
	while (p && j < i)     /* Ѱ�ҵ�i����� */
	{
		p = p->next;
		++j;
	}
	if (!p || j > i)
		return ERROR;   /* ��i��Ԫ�ز����� */
	s = (LinkedList)malloc(sizeof(LNode));  /*  �����½��(C���Ա�׼����) */
	s->data = e;
	s->next = p->next;      /* ��p�ĺ�̽�㸳ֵ��s�ĺ��  */
	p->next = s;          /* ��s��ֵ��p�ĺ�� */
	return OK;
}

/* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L) */
/* ���������ɾ��L�ĵ�i������Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1 */
Status ListDelete(LinkedList *L,int i,ElemType *e)
{
	int j;
	LinkedList p,q;
	p = *L;
	j = 1;
	while (p->next && j < i)	/* ����Ѱ�ҵ�i��Ԫ�� */
	{
        p = p->next;
        ++j;
	}
	if (!(p->next) || j > i)
	    return ERROR;           /* ��i��Ԫ�ز����� */
	q = p->next;
	p->next = q->next;			/* ��q�ĺ�̸�ֵ��p�ĺ�� */
	*e = q->data;               /* ��q����е����ݸ�e */
	free(q);                    /* ��ϵͳ���մ˽�㣬�ͷ��ڴ� */
	return OK;
}

/*********�����ҵ���������м�Ԫ��*******/
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
//ɾ���ظ������㷨
LinkedList RemoveDupNode(LinkedList L)
{
    LinkedList p,q,r;
    p=L->next;
    // p���ڱ�������
    while(p)
    {
        q=p;
        // q����p����Ľ�㣬����p��ֵ�Ƚ�
        while(q->next)
        {
            if(q->next->data==p->data)
            {
                // r������Ҫɾ���Ľ��
                r=q->next;
                // ��Ҫɾ���Ľ���ǰ�������
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
    printf("ͷ�巨----> L.\n");
    printf("L:\n");
    CreateListHead(&L, 11);
    ListTraverse(L);
    length = ListLength(L);
    printf("L�ĳ��ȣ�%d\n",length);

    printf("β�巨----> ls.\n");
    printf("ls:\n");
    CreateListTail(&ls, 10);
    ListTraverse(ls);
    length = ListLength(ls);
    printf("ls�ĳ��ȣ�%d\n",length);

    printf("L�ĵ�2��λ�ò���99:\n");
    ListInsert(&L,2,99);
    ListTraverse(L);
    length = ListLength(L);
    printf("L�ĳ��ȣ�%d\n",length);

    printf("ls�ĵ�2��λ�ò���100:\n");
    ListInsert(&ls,2,100);
    ListTraverse(ls);
    length = ListLength(ls);
    printf("ls�ĳ��ȣ�%d\n",length);

    printf("ɾ��L��2��λ�õ���:\n");
    ListDelete(&L,2,&e);
    ListTraverse(L);
    length = ListLength(L);
    printf("L�ĳ��ȣ�%d\n",length);
    printf("ɾ��ls��2��λ�õ���:\n");
    ListDelete(&ls,2,&e);
    ListTraverse(ls);
    length = ListLength(ls);
    printf("ls�ĳ��ȣ�%d\n",length);

    printf("����1_���õ�����L��\n");
    reverse(L);
    //ReverseSinglyLinkedList_1(&L);
    ListTraverse(L);
    printf("����2_���õ�����ls��\n");
    ReverseSinglyLinkedList_2(ls);
    ListTraverse(ls);

    printf("�����ҵ��������е��м�ֵ��\n");
    printf("L�м�ֵ mid = %d\n",GetMidNode(L, &mid));
    printf("ls�м�ֵ mid = %d\n",GetMidNode(ls, &mid));

    printf("ɾ��L�ظ�ֵ��\n");
    ListInsert(&L,2,2);
    ListTraverse(L);
    RemoveDupNode(L);
    ListTraverse(L);
    printf("Hello world!\n");
    return 0;
}
