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

//��̬����ĳ�ʼ����

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
/*���Ҫ�����µĽ�㵽��̬�����У�
 *������Ҫ�õ�һ�����������λ����
 *����µĽ�㣬malloc_ssl���ǵõ�
 *һ������������±꣬���ҷ��ء�
 */
int Malloc_SSL(StaticLinkList space)
{
    //�õ���һ�������±�
    int i = space[MAX_SIZE-1].cur ;
    if(space[0].cur)                                                   //������ڱ�������
    {
        //�õ���������ĵ�һ�������±�
        i = space[0].cur ;
    }
    //���ý��ĵ�һ����㽫��ʹ�ã����Ǳ��ý��С������һ������ƶ�
    space[0].cur = space[i].cur ;
    return i ;
}
//����Free_SSL���ǽ����±�Ľ��ŵ�����������ȥ��
void Free_SSL(StaticLinkList space, int i)
{
    //��֮ǰ�ı�������ĵ�һ������С����뵽L[i]��cur��
    space[i].cur  = space[0].cur;
    //�±�Ϊi��Ԫ�س�Ϊ��������ĵ�һ�����
    space[0].cur = i;
}
int GetListLength(StaticLinkList L) //��������ĵ�ǰ����
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
//�����½�������
Status InserList(StaticLinkList L ,int i ,ElemType e)
{
    int k = MAX_SIZE-1 ;
    int m;
    if( i < 1 || i >GetListLength(L)+1)
       return ERROR ;
    //�õ���������ĵ�һ��Ԫ��
    int j = Malloc_SSL(L);
    if (j)//���Ԫ�ش���
    {
        L[j].data = e ;
        //�õ���i-1��Ԫ�ص��±�
        for(m = 1 ; m < i ; ++m)
            k = L[k].cur ;
        /*����i-1��Ԫ�ص�cur����Ϊ�¼ӵ���������±꣬
         *���¼ӵ���������±�����Ϊ֮ǰ��i-1��Ԫ�ش洢��curֵ
         */
        L[j].cur = L[k].cur;
        L[k].cur = j;
        return OK;
    }
    return ERROR;
}

//ɾ����̬�����е�Ԫ��:
Status DeleteLinkList(StaticLinkList L, int i)
{
    if(i < 1 || i > GetListLength(L))
        return ERROR;
    int k = MAX_SIZE - 1;
    int j;
    for(j = 1 ; j < i ; ++j)//�ҵ���i-1��Ԫ��
    {
        k = L[k].cur;
    }
    j = L[k].cur ;//�õ���i��Ԫ�ص��±�
    L[k].cur = L[j].cur ;//����i��Ԫ�ش洢��curֵ��ֵ����i-1��Ԫ�ص�cur
    Free_SSL(L ,  j);//�ͷŵ���i��Ԫ�أ���i��Ԫ�ص��±�Ϊj
    return OK;
}

void Print(StaticLinkList L) //��ӡ����
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
