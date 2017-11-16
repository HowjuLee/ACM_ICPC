/*树状数组模板题*/
#include<iostream>
#include<cstdio>
#include<cstring>
#define MAXN 50005
using namespace std;
int que[MAXN],c[MAXN];
char chr[10];
int lowbit(int x)
{
    return x&(-x);//用来计算a^k中的k
}
//实现每个树状数组元素所分管的元素之和的计算
void create(int n)
{
    int i,s,j;
    for(i=1;i<=n;i++)
    {
        s=lowbit(i);
        for(j=0;j<s;j++)//含自身向前推s个
        {
            c[i]=c[i]+que[i-j];
        }
    }
}
//求数组的和的算法如下
int sum(int n)
{
    int s=0;
    while(n>0)
    {
        s+=c[n];
        n=n-lowbit(n);
    }
    return s;
}
//修改操作，往上修改
void change(int i,int n,int x)
{
    while(i<=n)
    {
        c[i]=c[i]+x;
        i=i+lowbit(i);
    }
}
int main()
{
    int t,cas=1,i,j,n,x,s,a,b;
    cin>>t;
    while(t--)
    {
        memset(c,0,sizeof(c));
        cin>>n;
        for(i=1;i<=n;i++)
            scanf("%d",&que[i]);
        create(n);
        cout<<"Case "<<cas++<<":"<<endl;
        while(1)
        {
            scanf("%s",chr);
            if(!strcmp(chr,"Add"))
            {
                scanf("%d%d",&j,&x);
                change(j,n,x);
            }
            else if(!strcmp(chr,"Sub"))
            {
                scanf("%d%d",&j,&x);
                change(j,n,-x);
            }
            else if(!strcmp(chr,"Query"))
            {
                scanf("%d%d",&a,&b);
                s=sum(b)-sum(a-1);
                printf("%d\n",s);
            }
            else
                break;
        }
    }
    return 0;
}
