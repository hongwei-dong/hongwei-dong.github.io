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

const int INITSIZE = 33;
const int INC = 30;

int main(){
  int size = INITSIZE; 
  int i = 0,j = 0,k=0 ;
  student *stus = (student *)malloc(size*sizeof(student));
  do{
	  if(i>=size){
		  student *stus_new =(student *)realloc(stus,(size+INC)*sizeof(student));
		  if(stus_new) {
			  free(stus); stus = stus_new;
		  }
		  else{
			  //...
		  }
	  }
	  printf("请输入学生姓名和分数：\n");
	  In_student(stus[i]); 
	  if(stus[i].score>=60)  j++;   
  }while(stus[i++].score>=0);
  i--;

  for(k=0;k<i;k++)   Out_student(stus[k]);
  printf("num of passed:%d\n",j); free(stus);
}
