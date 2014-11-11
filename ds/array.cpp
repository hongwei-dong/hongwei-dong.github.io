// copyright by hongwei dong (hwdong.com)
//-----------Array.h-------------
typedef double ElemType;
typedef struct{
  ElemType   *base;//����Ļ���ַ
  int dim;           //ά��
  int *bounds;   //��ά�Ľ�
  int *constants;//��ַ������ϵ��,��Ci
}Array;
bool  InitArray(Array &A,int dim,...);
void  Destory(Array &A);
bool  Value(Array &A,ElemType *e,...);
bool  Assign(Array &A, ElemType e,...); 



//-----------Array.cpp-------------
#include "malloc.h"
#include <cstdarg>

#define OK 0
#define ERROR 1
#define Max_Array_Dim 100

bool InitArray(Array &A,int dim, ...)
{
	if( dim <1||dim >= Max_Array_Dim) 
		return false;//ά���Ƿ�
	A.dim = dim;
	A.bounds = (int *)malloc(dim*sizeof(int));
	if( !A.bounds )    return ERROR;//�ڴ����ʧ��
	int elemtotal = 1;  //Ԫ�ص�����
	va_list ap; va_start(ap,dim);
	for( int i=0; i<dim; ++i){
		A.bounds[i] = va_arg ( ap,int);
		if(A.bounds[i] <=0) return -1;
		elemtotal *= A.bounds[i] ;
	}
	va_end( ap );

	A.base = (ElemType *)malloc(elemtotal *sizeof(ElemType));
	if(!A.base) return ERROR;
	A.constants=(int *)malloc( dim * sizeof(int)); //����Ci
	if (!A.constants)  return ERROR;    //�洢����ʧ��
	A.constants[dim-1]=1;        //cn=1
	for(int i= dim-2;i>=0;--i) //ci=ci+1*bi+1		 
		A.constants[i] = A.bounds[i+1]*A.constants[i+1];
		return OK;
}

bool Value(Array &A,ElemType *e,...){
	int off=0; va_list ap; 
	va_start(ap,e);//ʹapָ��e���һ������
	for(int i=0;i<A.dim;i++){
		int j=va_arg(ap,int); //j�б��浱ǰ�±�
		if(j<0||j>=A.bounds[i])   
			return ERROR;        //�±�ֵ�Ƿ�
		off+=A.constants[i]*j;  //��ci*ji���ۼ�
	}//for
	va_end(ap);
	*e=*(A.base+off); //��e����Ԫ��ֵ
	return OK;
}//Value


bool Assign(Array &A,ElemType e,...){
	int off=0; va_list ap; 
	va_start(ap,e);//ʹapָ��e���һ������
	for(int i=0;i<A.dim;i++){
		int j=va_arg(ap,int); //j�б��浱ǰ�±�
		if(j<0||j>=A.bounds[i])   
			return ERROR;        //�±�ֵ�Ƿ�
		off+=A.constants[i]*j;  //��ci*ji���ۼ�
	}//for
	va_end(ap);
	*(A.base+off) = e; //��e�޸�Ԫ��ֵ
	return OK;
}//Value

void  Destory(Array &A){
	free(A.base);
}


//--------------------test.cpp----------------
#include <cstdio>
int main(){
	Array A,B;
	InitArray(A,2,5,6);
	InitArray(B,3,4,5,2);

	ElemType e = 45;
	Assign(A,e,2,3);

	
	Value(A,&e,1,2);
	printf("%7.3f\n",e);

	Value(A,&e,2,3);
	printf("%7.3f\n",e);

	Value(B,&e,1,2,1);
	printf("%7.3f\n",e);

	e = 99;
	Assign(B,e,1,2,1);
	Value(B,&e,1,2,1);
	printf("%7.3f\n",e);


	return 0;
}
