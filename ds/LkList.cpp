// copyright by hongwei dong (hwdong.com)
//-----------LkList.h-------------
typedef double ElemType;
typedef int Status;
#define OK 0
#define ERROR 1
typedef struct node{
    ElemType data;
    struct node *next;
}LNode, *LinkList; //LinkList 等价于 LNode* 

bool InitList_L(LinkList &L);
Status GetElem_L(LinkList L, int i, ElemType &e);
Status SetElem_L(LinkList L, int i, ElemType e);
Status ListDelete_L(LinkList &L, int i, ElemType& e);
Status ListInsert_L(LinkList &L, int i, ElemType e);
int ListLength(LinkList L);


//-----------LkList.cpp-------------
//#include "LkList.h"

//初始化一个带头结点的单链表
bool InitList_L(LinkList &L){
	L = new LNode();
	if(!L) return false;
	L->next = 0;
	return true;
}
Status GetElem_L(LinkList L, int i, ElemType &e)
{
  LNode *p = L->next;   int j = 1;
  // 循环直到p为空或到了第i个节点
  while(p && j < i) {
  	p = p->next;      
	++ j;
  }
  if(!p || j > i)   // 第i个节点不存在
  	return ERROR;
  e = p->data;      // copy数据到e中
  return OK;
}

Status SetElem_L(LinkList L, int i, ElemType e)
{
  LNode *p = L->next;   int j = 1;
  // 循环直到p为空或到了第i个节点
  while(p && j < i) {
  	p = p->next;      
	++ j;
  }
  if(!p || j > i)   // 第i个节点不存在
  	return ERROR;
  p->data = e;      // copy e到数据中
  return OK;
}

Status ListInsert_L(LinkList &L, int i, ElemType e)
{
	LNode *p = L;   int j = 0;
	// 寻找第i-1个节点
	while(p && j < i-1){	
		p = p->next;
		++ j;
	}
	// 若第i-1个节点不存在
	if(!p || j > i-1)
		return ERROR;
	// 生成一个新节点，并链接到L中
	LNode *s = new LNode; //(LNode *) malloc (sizeof(LNode));

	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}

Status ListDelete_L(LinkList &L, int i, ElemType& e)
{
	LNode *p = L;   int j = 0;
	// 让p指向第i-1个节点
	while(p && j < i-1){	
		p = p->next;
		++ j;
	}
	// 若第i个节点不存在
	if(!(p->next) || j > i-1)
		return ERROR;
	LNode *q = p->next;       // q指向待删除节点
	p->next = q->next; // 使q脱离链表
	e = q->data;       // e得到q的数据
	delete q; //free(q);           // 释放q的空间
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
