// copyright by hongwei dong (hwdong.com)
//------------------string.h---------------
typedef struct{
    char *s;
    int _size;
 }String;
 bool initString(String &s,char *s0);
 void destoryString(String &s);
 void clearString(String &s);
 int size( String s);
 int catString(String &T,String s1,String s2);
 String subString(String S,int pos,int len);
 int findString(String S,String T,int pos);
 int insertString(String &S,String T,int pos);

 //------------------string.cpp---------------
#include <cstdio>
#include <cstring>
#include <malloc.h>

 bool initString(String &S,char *s0){
    int len = strlen(s0);
    S.s = (char *)malloc((len+1)*sizeof(char));
    if(!S.s) return false;
    strcpy(S.s,s0);
    S._size = len;
    return true;
}

String subString(String S,int pos,int len)
{ 
  String T; T.s = 0;T._size = 0; 
  T.s = (char*)malloc((len+1)*sizeof(char));
  if(T.s){
     for(int i = 0 ;i<len;i++)
        T.s[i] = S.s[i+pos-1];
	 T.s[len] = '\0';
     T._size = len;
  }
  return T;
}
int insertString (String &S,String T,int pos)
{//1. ����λ�úϷ���
	if(pos<1||pos>S._size+1) return 1;

 //2. ����ռ�
	int len = S._size+T._size;
	char *p  = (char *)malloc((len+1)*sizeof(char));
	if(!p) return 2;

 //3. ��������
	 //�±�Ϊi��Ԫ�������Ϊi+1
	int i = 0;
	for( ; i<pos-1;i++)
		p[i] = S.s[i]; 
	for(int j = 0; j<T._size;j++,i++)
		p[i] = T.s[j];
	for(int j = pos-1; j<S._size;j++,i++)
		p[i] = S.s[j];
	p[i] = '\0'; 
	free(S.s);
	S.s  = p ;
	S._size = len;
	return 0;
 }


int catString(String &T,String s1,String s2)
{
  int len = s1._size+s2._size; 
  T.s = (char *)malloc((len+1)*sizeof(char));
  if(!T.s) return 0;
  T._size = len;
  strcpy(T.s,s1.s);
  char *p = T.s+s1._size;
  strcpy(p,s2.s);
  return T._size; 
}




 //------------------test.cpp---------------
int main(){
	String S,S1;
	initString(S,"Li Ping");
	printf("S:=%s\n",S.s);

	initString(S1,"Zhang Wei");
	printf("S1:=%s\n",S1.s);

	String T;
	catString(T,S,S1);
	printf("T:= %s\n",T.s);

	String S2;
	initString(S2,"Wang");
	printf("S2=: %s\n",S2.s);

	insertString(T,S2,3);
	printf("T:= %s\n",T.s);
		return 0;
}