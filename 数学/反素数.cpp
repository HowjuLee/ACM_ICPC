/////////定义：反素数定义：对于任何正整数x,其约数的个数记做g(x).例如g(1)=1,g(6)=4.如果某个正整数x满足:
/////////对于任意i(0<i<x),都有g(i)<g(x),则称x为反素数
/*性质：1.一个反素数的所有质因子必然是从2开始的连续若干个质数
		2.其所有的质因子的指数递减。*/

void dfs(int dept,LL ans = 1)  
{  
    if(dept == cnt)  
    {  
        fac[ct++] = ans;  
        return;  
    }  
    for(int i=0;i<=num[dept];i++)  
    {  
        dfs(dept+1,ans);  
        ans *= pri[dept];  
    }  
} 

/////////求因子个数剪枝版
void dfs(int dept,int limit,ll tmp,int num)
{
    if(num > n) return;
    if(num == n && ans > tmp) ans = tmp;
    for(int i=1;i<=limit;i++)
    {
        if(ans / prime[dept] < tmp || num*(i+1) > n) break;
        tmp *= prime[dept];
        if(n % (num*(i+1)) == 0)
            dfs(dept+1,i,tmp,num*(i+1));
    }
}


/////求小于某个数的最多因子的数剪枝版
void dfs(int dept,int limit,ULL tmp,int num)
{
    if(tmp > n) return;
    if(num > best)
    {
        best = num;
        ans = tmp;
    }
    if(num == best && ans > tmp) ans = tmp;
    for(int i=1;i<=limit;i++)
    {
        double cur = (double)tmp;
        if(n < cur*p[dept]) break;
        dfs(dept+1,i,tmp *= p[dept],num*(i+1));
    }
}