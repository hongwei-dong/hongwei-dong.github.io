// copyright by hongwei dong (hwdong.com)
//---------------SqStack.h----------"
//typedef double SElemType;
typedef char SElemType;
typedef int Status;
#define OK 0
#define ERROR 1
#define OVERFLOW 2

typedef struct{
   SElemType *base;
   SElemType *top;
   int       stacksize;
} SqStack;

Status InitStack(SqStack &S);
Status Push(SqStack &S, SElemType e);
Status Pop(SqStack &S);
SElemType Top(SqStack &S);
inline bool IsEmpty(SqStack S) { return S.base==S.top;}


//---------------SqStack.cpp----------"
//#include "SqStack.h"
#include <malloc.h>
const int STACK_INIT_SIZE  = 100;
const int STACKINCREMENT = 20;
Status InitStack(SqStack &S)
{
  //����ռ�
  S.base = (SElemType*) malloc(STACK_INIT_SIZE * sizeof(SElemType));
  if(!S.base)	return OVERFLOW;
  S.top       = S.base;           //����ָ��
  S.stacksize = STACK_INIT_SIZE;  //���ô�С
  return OK;
}

Status Push(SqStack &S, SElemType e){
	//���ռ䲻�������·���
	if(S.top - S.base >= S.stacksize)	{
		S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT)*sizeof(SElemType));
	   if(!S.base) return OVERFLOW;
		S.top = S.base + S.stacksize;
	   S.stacksize += STACKINCREMENT;
	}	
	*S.top ++ = e; //��������
	return OK;
}

Status Pop(SqStack &S)//, SElemType &e)
{
	if(S.top == S.base)  //��ջ
		return ERROR;
	//e = * --S.top;       //��ջ
	--S.top;
	return OK;
}

SElemType Top(SqStack &S){
	SElemType e;
	if(S.top == S.base) return e; //����һ����Ч������
	return *(S.top-1);
}


//-----------------------����ƥ�����IsBracketsMatch-----------------
//#include "SqStack.h"
#include <cstdio>
/*
׼��һ��ջ�����ڴ��ɨ��������������
�������ɨ��ÿһ���ַ�{
  ����������������ţ�����ջ
  ����������������ţ���
      ��ջ���ַ��͵�ǰ�ַ��Ƚ�
      ��ƥ�䣬�򵯳�ջ���ַ���������ǰɨ��
      ����ƥ�䣬���򷵻ز�ƥ���־
  }
�������ַ���ɨ����ϣ�ջӦ��Ϊ��
*/
bool isLeftBracket(const char ch){
	if(ch=='('||ch=='['||ch=='{') return true;
	return false;
}
bool isRightBracket(const char ch){
	if(ch==')'||ch==']'||ch=='}') return true;
	return false;
}
bool isBracketMatch(const char lc,const char rc){
	if(lc=='('&&rc==')'||lc=='['&&rc==']'||lc=='{'&&rc=='}') return true;
	return false;
}
bool IsBracketsMatch(const char *str){
	SqStack S; 
	InitStack(S);//���Բ���ʼ������ô����
	const char *p = str;
	while(*p!='\0'){
		if(isLeftBracket(*p)) Push(S,*p);
		else if(isRightBracket(*p)){
			char ch = Top(S);
			if(!isBracketMatch(ch,*p)) return false;
			Pop(S);
		}
		p++; //����
	}
	if(IsEmpty(S)) return true;
	return false;
}

int main(){
	char *s = "{}[([][])]"; // "[(])��(()]"
	if(IsBracketsMatch(s))printf("Brackets is matched!\n");
	else printf("Brackets is not matched!\n");

	return 0;
}