// copyright by hongwei dong (hwdong.com)
//-----------Array.h-------------
typedef double ElemType;
typedef struct{
  ElemType   *base;//数组的基地址
  int dim;           //维数
  int *bounds;   //各维的界
  int *constants;//地址函数的系数,即Ci
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
		return false;//维数非法
	A.dim = dim;
	A.bounds = (int *)malloc(dim*sizeof(int));
	if( !A.bounds )    return ERROR;//内存分配失败
	int elemtotal = 1;  //元素的总数
	va_list ap; va_start(ap,dim);
	for( int i=0; i<dim; ++i){
		A.bounds[i] = va_arg ( ap,int);
		if(A.bounds[i] <=0) return -1;
		elemtotal *= A.bounds[i] ;
	}
	va_end( ap );

	A.base = (ElemType *)malloc(elemtotal *sizeof(ElemType));
	if(!A.base) return ERROR;
	A.constants=(int *)malloc( dim * sizeof(int)); //计算Ci
	if (!A.constants)  return ERROR;    //存储分配失败
	A.constants[dim-1]=1;        //cn=1
	for(int i= dim-2;i>=0;--i) //ci=ci+1*bi+1		 
		A.constants[i] = A.bounds[i+1]*A.constants[i+1];
		return OK;
}

bool Value(Array &A,ElemType *e,...){
	int off=0; va_list ap; 
	va_start(ap,e);//使ap指向e后第一个参数
	for(int i=0;i<A.dim;i++){
		int j=va_arg(ap,int); //j中保存当前下标
		if(j<0||j>=A.bounds[i])   
			return ERROR;        //下标值非法
		off+=A.constants[i]*j;  //求ci*ji并累加
	}//for
	va_end(ap);
	*e=*(A.base+off); //用e返回元素值
	return OK;
}//Value


bool Assign(Array &A,ElemType e,...){
	int off=0; va_list ap; 
	va_start(ap,e);//使ap指向e后第一个参数
	for(int i=0;i<A.dim;i++){
		int j=va_arg(ap,int); //j中保存当前下标
		if(j<0||j>=A.bounds[i])   
			return ERROR;        //下标值非法
		off+=A.constants[i]*j;  //求ci*ji并累加
	}//for
	va_end(ap);
	*(A.base+off) = e; //用e修改元素值
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
