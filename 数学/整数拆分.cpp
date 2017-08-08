///////整数拆分

/*1）当n==m时
可以分为两种情况，一个是使用n本身，只有一种情况。二个是使用不大于n-1的整数进行拆分。
所以此时q(n,m)=1+q(n,n-1)；
2）当n<m时
使用比n大的数进行拆分没有意义，所以此时q(n,m)=q(n,n)
3）当n>m时
这时候有两种情况，一个是使用m对n进行拆分，一个是使用小于m的数对n进行拆分
对于第一个，使用m对n进行拆分，所以拆分出来的情况最大的数是m，剩下的所有数加起来为n-m，问题变成使用不大于m的整数对n-m进行拆分，所以此时为q(n-m,m)
对于第二个，使用小于m的数对n进行拆分，表示为q(n,m-1)
4）当n==1或者m==1时 只有一种情况，返回1。注意，这里可能会漏掉m==1的情况，实际上这种情况是存在的。
所以可以使用递归函数编程如下：*/


#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <time.h>
using namespace std;

const int mod = 1000000007;
typedef long long ll;

ll solve(ll a,ll b)
{
    if(a==1||b==1)
        return 1;

    else if(b>a)    return solve(a,a)%mod;

    else if(a==b)
        return (solve(a,b-1)+1)%mod;

    else if(b<a){
        return solve(a-b,b)%mod+solve(a,b-1)%mod;
    }
}

int main()
{
    cin.sync_with_stdio(0);
    ll n;
    while(scanf("%I64d",&n)!=EOF){
        cout<<solve(n,n)<<endl;
        cout<<clock()<<endl;
    }
    return 0;
}




/*使用母函数法
整数分解用母函数可以这样理解，分别用任意个1，2，3，4，……，n可以加起来可以表示成n的种数。
又因为当使用整数m对n进行分解时，所使用的次数不能多于n/m次，所以可以写下母函数如下：
G(x)＝(1+x^1+x^2+……+x^n)*(1+x^2+x^4+……+x^((n/2)*2))*……
          ＊(1+x^m+x^(2*m)+x^(3*m)+……+x^((n/m)*m))*……*(1+x^n)
在程序中使用set数组表示每一轮乘法后得到系数，c数组表示到现在为止乘法得到的系数总和。
最后算出结果后x^n对应的系数则为可分解的可能数。代码如下：*/

#include<stdio.h>  
const int num=1000;  
int set[num];  
int c[num];  
void init(){  
    for(int i=0; i<num; i++){  
        c[i]=1;  
        set[i]=0;  
    }  
}  
  
int main(){  
    int n;  
    int sum;  
    init();  
    while(scanf("%d",&n)!=EOF){  
        sum=0;  
        init();  
        for(int i=2; i<=n; i++){  
            for(int j=0; j<=n; j+=i){  
                for(int k=0; j+k<=n; k++){  
                        set[k+j]+=c[k];   
                }  
            }  
            for(int x=0; x<=n; x++){  
                c[x]=set[x];  
                set[x]=0;  
            }  
        }  
        printf("%d\n",c[n]);  
    }  
    return 0;  
}  
/////////////////////////////////////////////
#include <iostream>

using namespace std;

#define  MYDATA long long
const MYDATA MOD=1000000007;

#define  AMS 100005
MYDATA pp[AMS];
MYDATA asist[2*AMS];
void myinit()
{
	for(int i=0;i<AMS;i++)
	{
		/*算出五角数（正常五角数为1,5,12,22.... k*(3*k-1)/2）*/
		/*此部分，需要算出的是分割函数(1,2,5,7,12,15,22,26.....
		[k*(3*k-1)/2,k*(3*k+1)/2 ])*/
		asist[2*i]=i*(i*3-1)/2;
		asist[2*i+1]=i*(i*3+1)/2;
	}
}
void mymethod()
{
	pp[1]=1;
	pp[2]=2;
	pp[0]=1;
	for(int i=3;i<AMS;i++)
	{
		int k=0;
		int flags;
		pp[i]=0;
		/*pp[n]=pp[n-1]+pp[n-2]-pp[n-5]-pp[n-7]+pp[12]+pp[15]
		-.... ..... [+pp[n-k*[3k-1]/2]  + pp[n-k*[3k+1]/2]]*/
		for(int j=2;asist[j]<=i;j++)
		{
			/*说明：式子中+MOD是必须的，否则输出可能出错（有可能为负数）*/
			flags=k&2;
			if(!flags)
				pp[i]=(pp[i]+pp[i-asist[j]]+MOD)%MOD;
			else
				pp[i]=(pp[i]-pp[i-asist[j]]+MOD)%MOD;
			k++;
			k%=8;
		}
	}
}

int main()
{ 
	int t,n;
	myinit();
	mymethod();
  
    cin>>t;
    while(t--)
    {
        cin>>n;
	cout<<pp[n]<<endl;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>  
  
//使用一个数组记录在递归过程中产生的前面需要重复输出的值  
int set[100];  
//用于在递归过程中判断是否递归到最深处，输出回车  
int k;  
  
//此函数表示使用不大于m的整数对n进行拆分的情况，i用于表示set数组已经存在的记录数长度  
void q(int n,int m,int i){  
    if(n==k&&n!=m){   
        //此时递归栈已经退回到某一分支的最上层，输出回车  
        //并重置计数器i为0  
        printf("\n");  
        i=0;  
    }  
    if(n==1){  
        //当n为1，意味者着只能表示1  
        printf("1 ");  
        return;  
    }  
    else if(m==1){  
        //当m为1，意味着要输出n个m相加  
        for(int i=0; i<n-1; i++)  
            printf("1+");  
        printf("1 ");  
        return;  
    }  
    if(n<m) {  
        q(n,n,i);  
    }  
    if(n==m){  
        //当n等于m时，到达本次递归求和的一个叶子，此时需要输出多一个空格，表示下一次输出为另一个叶子  
        printf("%d ",n);  
        //在递归输出另一个叶子之前，将之前记录的在叶子之上的数一并输出，如上图示过程1  
        for(int j=0; j<i; j++)  
            printf("%d+",set[j]);  
        q(n,m-1,i);  
          
    }  
    if(n>m){  
        //如果n大于m，使用m作为分解，则要首先输出m+的形式  
        printf("%d+",m);  
        //记录下作为树干节点m的值并使i自增  
        set[i++]=m;  
        //递归输出m+以后的分解  
        q(n-m,m,i);  
        //递归完毕后需要将数组记录后退一个，回到上一个节点，如上图示过程2  
        i--;  
        //执行另一个分支，在下一次递归之前输出记录的数据，如上图示过程3  
        for(int j=0; j<i; j++)  
            printf("%d+",set[j]);  
        //递归输出另一分支情况  
        q(n,m-1,i);  
    }  
      
      
}  
  
int main(){  
    int n;  
    while(scanf("%d",&n)!=EOF){  
        if(n<=0){  
            printf("Please input a positive interger.\n\n");  
            continue;  
        }  
        k=n;  
        q(n,n,0);  
        printf("\n\n");  
    }  
}  