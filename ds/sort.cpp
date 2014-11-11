// copyright by hongwei dong (hwdong.com)
//------------------sort.h---------------
#define MAXSIZE 1024     // 最多元素个数
typedef double KeyType;   // 关键字类型
typedef char InfoType;
typedef struct{
	KeyType key;       // 关键字
	InfoType otherinfo;
}RedType;              // 一条数据记录
typedef struct{
	RedType r[MAXSIZE+1]; // 数组
	int length;           // 元素个数
}SqList;    

bool LT(KeyType k1,KeyType k2) {return k1<k2;}
void swap(RedType &r1, RedType &r2){ RedType t = r1; r1 = r2; r2 = t;}

//---------------------insert sort----------------
void InsertSort(SqList &L) {
	for(int i = 2; i <= L.length; i ++)
		if(LT(L.r[i].key, L.r[i-1].key)) //i比i-1小
		{
			L.r[0] = L.r[i];      //用r[0]先记录r[i]的值
			L.r[i] = L.r[i-1];    //r[i-1]后移一个单元

			//从i-2开始，往左扫描，直到找到一个<=r[0]的
			int j;
			for(j=i-2; LT(L.r[0].key, L.r[j].key); j--)
				L.r[j+1] = L.r[j];       //每个元素后移
			L.r[j+1] = L.r[0];    //最后把r[0]写入
		}
}


//---------------------heap sort----------------
void HeapAdjust(SqList &H, int s, int m) {
	RedType rc = H.r[s]; //暂时保存待下移的数据
	for(int j = 2 * s; j <= m; j *= 2) {
	  if(j < m && LT(H.r[j].key, H.r[j+1].key))
	    j ++;    //j指向s较大的“儿子”
	  if(!LT(rc.key,H.r[j].key))
	    break;  //若j的值比rc小，说明找到了s的位置
	  H.r[s] = H.r[j]; //否则元素j上移
	  s = j;
	}
	H.r[s] = rc;   //写入s
}


void HeapSort(SqList &H){
   //将H.r[1…H.length()]建成大顶堆
   for(int i = H.length /2;i>0;i--)
     HeapAdjust(H, i, H.length);

   //输出堆顶H.r[1],并调整H.r[1…i-1]
   for(int i = H.length;i>1;i--){
     swap(H.r[1], H.r[i]); //两者交换
     HeapAdjust(H,1,i-1);
   }
}


//------------------main.cpp---------------
#include <stdio.h>
void OutPut(const SqList &sL){
	for(int i = 1; i<=sL.length;i++){
		printf("%8.2f  ",sL.r[i]);
	}
	printf("\n");
}

//#define TIME_TEST
#ifdef TIME_TEST
#include <time.h>
#endif

int main(){
#ifdef TIME_TEST
	time_t   start, finish;
	double   elapsed_time;
#endif

	SqList sL;
	RedType r; 
	r.otherinfo = 'A';
	sL.length = 0;
	r.key = 36;	 sL.r[++sL.length] = r; 
	r.key = 16;	 sL.r[++sL.length] = r; 
	r.key = 26;	 sL.r[++sL.length] = r; 
	r.key = 66;	 sL.r[++sL.length] = r; 
	r.key = 296; sL.r[++sL.length] = r; 
	r.key = 106; sL.r[++sL.length] = r; 
	r.key = 56;	 sL.r[++sL.length] = r; 

	
	SqList tL = sL;
	OutPut(tL);
#ifdef TIME_TEST
	time( &start );
#endif
	InsertSort(tL);
#ifdef TIME_TEST
	time( &finish );
	elapsed_time = difftime( finish, start );
	printf( "InsertSort takes %6.0f seconds.\n", elapsed_time );
#endif
	OutPut(tL);
	
	tL = sL;
	OutPut(tL);
#ifdef TIME_TEST
	time( &start );
#endif
	HeapSort(sL);
#ifdef TIME_TEST
	time( &finish );
	elapsed_time = difftime( finish, start );	
	printf( "HeapSort takes %6.0f seconds.\n", elapsed_time );
#endif
	OutPut(tL);
		
	return 0;
}