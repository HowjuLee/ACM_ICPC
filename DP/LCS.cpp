//////最长公共子串
string LCS_continuous(string str1,string str2)  
{  
    int i,j,maxnum=0,maxj=0;  
    int n1=str1.size(),n2=str2.size();  
    vector<int> last,cur,temp;//last、cur记录上一行、当前行的LCS信息，temp作为辅助数组。  
    for(i=0;i<n2+1;i++)//初始值：第0行第0列置0  
    {  
        last.push_back(0);  
        cur.push_back(0);  
    }  
    temp=cur;  
    for(i=1;i<=n1;i++)  
    {  
        cur=temp;//cur清零  
        for(j=1;j<=n2;j++)  
        {  
            if(str1[i-1]==str2[j-1])  
            {  
                cur[j]=last[j-1]+1;  
                if(cur[j]>maxnum)//更新最大值  
                {  
                    maxnum=cur[j];  
                    maxj=j-1;//记录最大值列号  
                }  
            }  
        }  
        last=cur;//把当前行信息传递给last  
    }  
    return str2.substr(maxj-maxnum+1,maxnum);  
}  

//////最长公共子序列
#include<stdio.h>
#include<string.h>
#define MAX(a,b) (a>b?a:b)
const int MAXN=1010;
int dp[MAXN][MAXN];
char a[MAXN],b[MAXN];
int main(){
while(~scanf("%s%s",a+1,b+1)){
    memset(dp,0,sizeof(dp));
    int i,j;
    for( i=1;a[i];i++){
        for(j=1;b[j];j++){
            if(a[i]==b[j])dp[i][j]=dp[i-1][j-1]+1;
            else dp[i][j]=MAX(dp[i][j-1],dp[i-1][j]);
        }
    }
    printf("%d\n",dp[i-1][j-1]);
}
return 0;}



