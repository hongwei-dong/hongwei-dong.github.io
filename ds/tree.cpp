// copyright by hongwei dong (hwdong.com)
#include <cstdio>
typedef char Type;
typedef struct _BiNode{
	Type data;
	struct _BiNode *lchild, *rchild;
}BiTNode;
typedef BiTNode* BiTree;

void visit(BiTNode* p){
	printf("%c",p->data);
}
void PreTraverse(BiTNode* T){
	if(!T) return ;
	visit(T);
	PreTraverse(T->lchild);
	PreTraverse(T->rchild);
}


void PreOrderCreatBiTree(BiTNode* &T){
	Type e;
	scanf("%c",&e);
	if(e== '#'){ T = 0; return;} //递归出口


	if(!(T= new BiTNode) ){ //处理根
		throw "内存不够!";return;
	}
	T->data = e;

	PreOrderCreatBiTree(T->lchild);//左子树
	PreOrderCreatBiTree(T->rchild);//右子树
}

int Depth (BiTNode* T ){
  if (!T) return 0 ;
  int l = Depth( T->lchild );
  int r = Depth( T->rchild );  
  return l>r?l+1:r+1;
}

int main(){
	BiTNode* T = 0;
	PreOrderCreatBiTree(T);
	PreTraverse(T);
	int d = Depth(T);
	printf("\ndepth of the tree is :%d\n",d);

	return 0;
}