// copyright by hongwei dong (hwdong.com)
//-----------LkList.h-------------
typedef double ElemType;
typedef int Status;
#define OK 0
#define ERROR 1
typedef struct node{
    ElemType data;
    struct node *next;
}LNode, *LinkList; //LinkList �ȼ��� LNode* 

bool InitList_L(LinkList &L);
Status GetElem_L(LinkList L, int i, ElemType &e);
Status SetElem_L(LinkList L, int i, ElemType e);
Status ListDelete_L(LinkList &L, int i, ElemType& e);
Status ListInsert_L(LinkList &L, int i, ElemType e);
int ListLength(LinkList L);


//-----------LkList.cpp-------------
//#include "LkList.h"

//��ʼ��һ����ͷ���ĵ�����
bool InitList_L(LinkList &L){
	L = new LNode();
	if(!L) return false;
	L->next = 0;
	return true;
}
Status GetElem_L(LinkList L, int i, ElemType &e)
{
  LNode *p = L->next;   int j = 1;
  // ѭ��ֱ��pΪ�ջ��˵�i���ڵ�
  while(p && j < i) {
  	p = p->next;      
	++ j;
  }
  if(!p || j > i)   // ��i���ڵ㲻����
  	return ERROR;
  e = p->data;      // copy���ݵ�e��
  return OK;
}

Status SetElem_L(LinkList L, int i, ElemType e)
{
  LNode *p = L->next;   int j = 1;
  // ѭ��ֱ��pΪ�ջ��˵�i���ڵ�
  while(p && j < i) {
  	p = p->next;      
	++ j;
  }
  if(!p || j > i)   // ��i���ڵ㲻����
  	return ERROR;
  p->data = e;      // copy e��������
  return OK;
}

Status ListInsert_L(LinkList &L, int i, ElemType e)
{
	LNode *p = L;   int j = 0;
	// Ѱ�ҵ�i-1���ڵ�
	while(p && j < i-1){	
		p = p->next;
		++ j;
	}
	// ����i-1���ڵ㲻����
	if(!p || j > i-1)
		return ERROR;
	// ����һ���½ڵ㣬�����ӵ�L��
	LNode *s = new LNode; //(LNode *) malloc (sizeof(LNode));

	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}

Status ListDelete_L(LinkList &L, int i, ElemType& e)
{
	LNode *p = L;   int j = 0;
	// ��pָ���i-1���ڵ�
	while(p && j < i-1){	
		p = p->next;
		++ j;
	}
	// ����i���ڵ㲻����
	if(!(p->next) || j > i-1)
		return ERROR;
	LNode *q = p->next;       // qָ���ɾ���ڵ�
	p->next = q->next; // ʹq��������
	e = q->data;       // e�õ�q������
	delete q; //free(q);           // �ͷ�q�Ŀռ�
	return OK;
}

int ListLength(LinkList L){
	LNode *p = L; int j = 0;
	while(p->next){
		j++; p = p->next;
	}
	return j;
}


//-------------------test.cpp-----------
//#include "LkList.h"
#include <iostream>
using std::cout;
int main(){
	LinkList L;
	ElemType e = 67.8;
	InitList_L(L);
	ListInsert_L(L,1,e);
	e=99;
	ListInsert_L(L,3,e);
	e = 88;
	ListInsert_L(L,1,e);
	e = 33;
	ListInsert_L(L,2,e);
	e=45;
	SetElem_L(L,1,e);

	int length = ListLength(L);
	for(int i = 1 ;i<=length;i++){
		if(GetElem_L(L,i,e)==OK)
			cout<<e<<" ";
	}
	cout<<"\n";
}
