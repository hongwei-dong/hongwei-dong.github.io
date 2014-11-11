// copyright by hongwei dong (hwdong.com)
//------------------sort.h---------------
#define MAXSIZE 1024     // ���Ԫ�ظ���
typedef double KeyType;   // �ؼ�������
typedef char InfoType;
typedef struct{
	KeyType key;       // �ؼ���
	InfoType otherinfo;
}RedType;              // һ�����ݼ�¼
typedef struct{
	RedType r[MAXSIZE+1]; // ����
	int length;           // Ԫ�ظ���
}SqList;    

bool LT(KeyType k1,KeyType k2) {return k1<k2;}
void swap(RedType &r1, RedType &r2){ RedType t = r1; r1 = r2; r2 = t;}

//---------------------insert sort----------------
void InsertSort(SqList &L) {
	for(int i = 2; i <= L.length; i ++)
		if(LT(L.r[i].key, L.r[i-1].key)) //i��i-1С
		{
			L.r[0] = L.r[i];      //��r[0]�ȼ�¼r[i]��ֵ
			L.r[i] = L.r[i-1];    //r[i-1]����һ����Ԫ

			//��i-2��ʼ������ɨ�裬ֱ���ҵ�һ��<=r[0]��
			int j;
			for(j=i-2; LT(L.r[0].key, L.r[j].key); j--)
				L.r[j+1] = L.r[j];       //ÿ��Ԫ�غ���
			L.r[j+1] = L.r[0];    //����r[0]д��
		}
}


//---------------------heap sort----------------
void HeapAdjust(SqList &H, int s, int m) {
	RedType rc = H.r[s]; //��ʱ��������Ƶ�����
	for(int j = 2 * s; j <= m; j *= 2) {
	  if(j < m && LT(H.r[j].key, H.r[j+1].key))
	    j ++;    //jָ��s�ϴ�ġ����ӡ�
	  if(!LT(rc.key,H.r[j].key))
	    break;  //��j��ֵ��rcС��˵���ҵ���s��λ��
	  H.r[s] = H.r[j]; //����Ԫ��j����
	  s = j;
	}
	H.r[s] = rc;   //д��s
}


void HeapSort(SqList &H){
   //��H.r[1��H.length()]���ɴ󶥶�
   for(int i = H.length /2;i>0;i--)
     HeapAdjust(H, i, H.length);

   //����Ѷ�H.r[1],������H.r[1��i-1]
   for(int i = H.length;i>1;i--){
     swap(H.r[1], H.r[i]); //���߽���
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