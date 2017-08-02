/////LIS

const int maxn = 1e6+10;
int d[maxn],a[maxn];

int bsearch(int *d,int x,int y,int v)///二分查找
{
    int m;
    while(x<y){
        m = x+(y-x)/2;
        if(d[m]==v) return m;
        else if(d[m]>v) y=m;
        else x=m+1;
    }
    return -1;
}

int LIS(int *a,int n,int *d)
{
	int i,j;
	d[1]=a[1];
	int len=1;	////length
	for(int i=2;i<=n;i++){
		if(d[len]<a[i])
			j=++len;
		else	j=bsearch(a[i],d,1,len)+1;
		d[j]=a[i];
	}
	return len;
}

//////////////////////////////////////////
/*dp[i]表示以i结尾的子序列中LIS的长度。然后我用dp[j](0<=j<i)来表示在i之前的LIS的长度。
然后我们可以看到，只有当a[i]>a[j]的时候，我们需要进行判断，是否将a[i]加入到dp[j]当中。
为了保证我们每次加入都是得到一个最优的LIS，有两点需要注意：
第一，每一次，a[i]都应当加入最大的那个dp[j]，保证局部性质最优，也就是我们需要找到max(dp[j](0<=j<i))；
第二，每一次加入之后，我们都应当更新dp[j]的值，显然，dp[i]=dp[j]+1。 
如果写成递推公式，我们可以得到dp[i]=max(dp[j](0<=j<i))+(a[i]>a[j]?1:0)。 
于是我们就能够得到O(n^2)的动态规划方法的实现：*/


/*在前一种方法中，我们花费了很多时间在寻找最大的dp[j]上。
如果有办法让这个dp[j]变成一个递增的序列，我们就能使用二分来进行优化，从而使得复杂度下降为O(nlogn)了。
 幸运的是，这种方法确实是存在的。我们可以使用dp[i]来保存在前i个数中最大的那个数，很容易可以理解，这个dp[i]已经是单调不减的。
 接下来的处理其实有些贪心的思想，对于每一个a[i]，我们都在dp数组中寻找比它大的第一个数的下标，不妨设为pos，然后用a[i]来更新dp[pos]。
 于是我们可以明白，len就应当是max(len, pos+1)。*/
 
 //在这里我们使用lower_bound函数，这个函数将会返回小于等于val的第一个值的指针，如果不存在就返回end指针
const int MAXN = 1010;
int n;
int a[MAXN];
int dp[MAXN];

int lis()
{
    memset(dp, 0, sizeof(int)*n);
    int len = 1;
    dp[0] = a[0];
    for (int i = 1; i < n; ++i)
    {
        int pos = lower_bound(dp, dp + len, a[i]) - dp;
        dp[pos] = a[i];
        len = max(len, pos + 1);
    }
    return len;
}