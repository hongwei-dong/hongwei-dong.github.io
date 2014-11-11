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
  //分配空间
  S.base = (SElemType*) malloc(STACK_INIT_SIZE * sizeof(SElemType));
  if(!S.base)	return OVERFLOW;
  S.top       = S.base;           //设置指针
  S.stacksize = STACK_INIT_SIZE;  //设置大小
  return OK;
}

Status Push(SqStack &S, SElemType e){
	//若空间不够，重新分配
	if(S.top - S.base >= S.stacksize)	{
		S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT)*sizeof(SElemType));
	   if(!S.base) return OVERFLOW;
		S.top = S.base + S.stacksize;
	   S.stacksize += STACKINCREMENT;
	}	
	*S.top ++ = e; //插入数据
	return OK;
}

Status Pop(SqStack &S)//, SElemType &e)
{
	if(S.top == S.base)  //空栈
		return ERROR;
	//e = * --S.top;       //出栈
	--S.top;
	return OK;
}

SElemType Top(SqStack &S){
	SElemType e;
	if(S.top == S.base) return e; //返回一个无效的数据
	return *(S.top-1);
}


//-----------------------括号匹配程序IsBracketsMatch-----------------
//#include "SqStack.h"
#include <cstdio>
/*
准备一个栈，用于存放扫描遇到的左括号
从左向后扫描每一个字符{
  如果遇到的是左括号，则入栈
  如果遇到的是右括号，则
      把栈顶字符和当前字符比较
      若匹配，则弹出栈顶字符，继续向前扫描
      若不匹配，程序返回不匹配标志
  }
当所有字符都扫描完毕，栈应当为空
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
	InitStack(S);//试试不初始化会怎么样？
	const char *p = str;
	while(*p!='\0'){
		if(isLeftBracket(*p)) Push(S,*p);
		else if(isRightBracket(*p)){
			char ch = Top(S);
			if(!isBracketMatch(ch,*p)) return false;
			Pop(S);
		}
		p++; //继续
	}
	if(IsEmpty(S)) return true;
	return false;
}

int main(){
	char *s = "{}[([][])]"; // "[(])，(()]"
	if(IsBracketsMatch(s))printf("Brackets is matched!\n");
	else printf("Brackets is not matched!\n");

	return 0;
}