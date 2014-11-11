/*--------copysight by hongwei dong (hwdong.com)---------------*/
#include "cstring"
#include "malloc.h"
#include "cstdio"


typedef struct{
   char name[30];
   float score;
} student;


struct LNode{
  student data; //Type data;
  LNode *next;
} ;

void In_student(student &s){
   scanf("%s",s.name);
   scanf("%f",&(s.score));
}
void Out_student(const student s){
  printf("name:%s  score:%3.2f\n",
           s.name, s.score);
}


void copy_stu(student &d, const student &s){ 
  strcpy((char *)d.name,(char *)s.name);
  d.score = s.score;   
}


int main(){
  student s;   int i = 0,j = 0,k=0 ;
  LNode *q = 0,*p =(LNode *)malloc(sizeof(LNode));
  p->next = 0;
  do{
	 printf("请输入学生姓名和分数：\n");
     In_student(s);  
	 if(s.score>=60)  j++;  
	 else if(s.score<0) break;
     q = (LNode *)malloc(sizeof(LNode));
     q->next  = p->next;
	 copy_stu(q->data,s);
     p->next = q;
  }while(s.score>=0);
  
  q = p->next;
  while(q) {   Out_student(q->data); q = q->next;}
  printf("num of passed:%d\n",j);

  return 0;
}
