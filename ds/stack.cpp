#include <iostream>

using namespace std;

typedef int ElemType;
typedef struct lnode{
    ElemType data;
    struct lnode *next;
}LNode;

typedef LNode* LkStack;

bool init(LkStack &S){ //bool init(LNode* &S){
    S = new LNode(); if(!S) return false;
    S->next = 0; return true;
}
bool Push(LkStack &S,ElemType e){
    LNode *p = new LNode(); if(!p) return false;
    p->data = e;
    p->next  = S->next;
    S->next = p;
    return true;
}
bool Pop(LkStack &S){
    if(!S->next) return false;
    LNode *p = S->next;
    S->next = p->next;
    delete p; return true;
}
bool Top(LkStack &S,ElemType &e){
     if(!S->next) return false;
     e = S->next->data;
     return true;
}
bool isEmpty(LkStack S){
    return S->next==0;
}

void converse(){
    int N;
    std:cin>>N;
    LkStack SS; //SqStack SS;
   init(SS);
   ElemType e;
   while(N){
      Push(SS,N%8); N = N/8;
   }
   while(!isEmpty(SS)){
      Top(SS,e); Pop(SS);
      std::cout<<e;
   }
   std::cout<<"\n";

}
/*
typedef struct{
    ElemType *data;
    ElemType *top;
    int capacity;
}SqStack;


bool init(SqStack &S,int init_capacity = 100){ //default
   S.data = new ElemType[init_capacity];
   if(!S.data) return false;
   S.capacity =   init_capacity;
   S.top = S.data;
   return true;
}
const int INC = 30;
bool Push(SqStack &S,ElemType e){
    if(S.top-S.data==S.capacity){ //return false;
        ElemType *p  = new ElemType[S.capacity+INC];
        if(!p) return false;
        ElemType *q2 = p;
        for(ElemType *q = S.data; q<S.top; q++){
            *q2  =*q; q++;q2++;
        }
        delete[] S.data; S.data = p;
        S.top = q2;
    }
    *(S.top) = e; S.top++;
    return true;
}

bool Pop(SqStack &S){
    if(S.top==S.data) return false;
    S.top--; return true;
}
bool Top(SqStack &S,ElemType &e){
   if(S.top==S.data) return false;
   e = *(S.top-1); return true;
}
bool clear(SqStack &S){
    S.top = S.data; return true;
}

int size(SqStack &S){
    return S.top-S.data;
}
*/

int main()
{
    converse();    return 0;
   LkStack SS; //SqStack SS;
   init(SS);
   ElemType e;

   e = 10; Push(SS,e);
   e = 20; Push(SS,e);
   e = 30; Push(SS,e);
   e = 40; Push(SS,e);
   Top(SS,e);
   std::cout<<e<<"\n";
   Pop(SS);
   Top(SS,e);
   std::cout<<e<<"\n";
   return 0;
}
