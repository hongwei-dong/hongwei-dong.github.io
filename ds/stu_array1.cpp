// copyright by hongwei dong (hwdong.com)
#include "cstring"
#include "malloc.h"
#include "cstdio"


typedef struct{
   char name[30];
   float score;
} student;


int main(){
  student stus[100];
  int i = 0,j = 0,k=0 ;
  do{ 
	  printf("请输入学生姓名和分数：\n");
	  scanf("%s", stus[i].name);
      scanf("%f", &(stus[i].score)); 
      if(stus[i].score>=60)  j++; 	  
  }while(stus[i++].score>=0);
  i--;

  for(k=0;k<i;k++){
     printf("name:%s  score:%3.2f\n",
           stus[k].name, stus[k].score);
  }
  printf("num of passed:%d\n",j);
}

