// copyright by hongwei dong (hwdong.com)
#include "cstring"
#include "malloc.h"
#include "cstdio"


typedef struct{
   char name[30];
   float score;
} student;


void In_student(student &s){
   scanf("%s",s.name);
   scanf("%f",&(s.score));
}
void Out_student(const student s){
  printf("name:%s  score:%3.2f\n",
           s.name, s.score);
}


int main(){
  student stus[100];
  int i = 0,j = 0,k=0 ;
  do{
	 printf("请输入学生姓名和分数：\n");
     In_student(stus[i]); 
     if(stus[i].score>=60)  j++;   
  }while(stus[i++].score>=0);
  i--;

  for(k=0;k<i;k++)
   Out_student(stus[k]);

  printf("num of passed: %d\n",j);
}
