#include <iostream>
#include <stack>
using namespace std;

char op_prior_table[][7] = {
    { '>','>','<','<','<','>','>' },
    { '>','>','<','<','<','>','>' },
    { '>','>','>','>','<','>','>' },
    { '>','>','>','>','<','>','>' },
    { '<','<','<','<','<','=','!' },
    { '>','>','>','>','!','>','>' },
    { '<','<','<','<','<','!','=' }
};

int index_of_op(const char op){
    if(op=='+') return 0;
    else if(op=='-') return 1;
    else if(op=='*') return 2;
    else if(op=='/') return 3;
    else if(op=='(') return 4;
    else if(op==')') return 5;
    else             return 6;   // '#'
}

int prior(const char op1,const char op2){
    int i = index_of_op(op1),j = index_of_op(op2);
    char cmp = op_prior_table[i][j];
    if(cmp=='>') return 1;
    else if(cmp=='<') return -1;
    else if(cmp=='=') return 0;
    return 10000;
}

//用算符op对两个运算数进行运算 : n1 op n2
int op2num(const char op,int n1, int n2){
    if(op=='+') return n1+n2;
    //...此处补充你的代码
}
int compute_mid_expression(const char *exp){
    stack<char> op_stack;
    stack<int> num_stack;
    const char *p = exp;
    op_stack.push('#');
    while(*p!='\0'){
        if( *p>='0'&&*p<='9' )  {//运算数
            num_stack.push(*p); //运算数直接入栈
            p++;
        }
        else {//运算符
            char op1 = op_stack.top();
            int priority =  prior(op1,*p);
            if(priority==1 ){//栈顶算符优先，需要立即弹出进行计算了
                op_stack.pop();
                //... 加入你的代码
            }
            else if(priority==-1 ){ //当前算符*p优先
                op_stack.push(*p); p++;
            }
            else if(priority==0 ){

            }
            else{}
        }
    }
}

int main()
{
    char *express = "3*(2+4)-8/2#";
    cout<<compute_mid_expression(express)<<"\n";
    return 0;
}
