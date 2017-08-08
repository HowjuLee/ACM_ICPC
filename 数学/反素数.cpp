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