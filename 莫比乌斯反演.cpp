///莫比乌斯反演
const int maxn = 1e6+5;
int mu[maxn],prime[maxn];
bool check[maxn];

void Moblus(){  
    memset(check,false,sizeof(check));  
    mu[1] = 1;  
    int tot = 0;  
    for(int i = 2; i <= maxn; i++){  
        if( !check[i] ){  
            prime[tot++] = i;  
            mu[i] = -1;  
        }  
        for(int j = 0; j < tot&&prime[j]*i<maxn; j++){  
            if(i * prime[j] > maxn) break;  
            check[i * prime[j]] = true;  
            if( i % prime[j] == 0){  
                mu[i * prime[j]] = 0;  
                break;  
            }  
            else{  
                mu[i * prime[j]] = -mu[i];  
            }  
        }  
    }  
} 

/*

F(n)和f(n)是定义在非负整数集合上的两个函数，并且满足条件F(n)=∑f(d),其中d为n的因子，f(n)=∑μ(d)*F(n/d).

μ(d)性质
对任意整数n有∑μ(d)=1(n=1)或∑μ(d)=0(n>1)			d为n的因子

对任意整数n有∑(μ(d))/d=φ(n)/n;


在上面的公式中有一个函数μ(d)，它的定义如下：
 
    （1）若d=1，那么μ(d)=1;
    （2）若d=p1*p2*p3*...*pk，p1...pk均为互异素数，那么μ(d)=(-1)的k次方.
    （3）其它情况下μ(d)=0;
*/



//线性筛选求莫比乌斯反演代码

void Init()  
{  
    memset(vis,0,sizeof(vis));  
    mu[1] = 1;  
    cnt = 0;  
    for(int i=2; i<N; i++)  
    {  
        if(!vis[i])  
        {  
            prime[cnt++] = i;  
            mu[i] = -1;  
        }  
        for(int j=0; j<cnt&&i*prime[j]<N; j++)  
        {  
            vis[i*prime[j]] = 1;  
            if(i%prime[j]) mu[i*prime[j]] = -mu[i];  
            else  
            {  
                mu[i*prime[j]] = 0;  
                break;  
            }  
        }  
    }  
} 