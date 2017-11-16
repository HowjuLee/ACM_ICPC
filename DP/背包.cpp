int f[111111],a[111],c[111];
int n,m;

//m背包的总容量、v物品的体积、w物品的价值
void OneZeroPack(int m,int v,int w)  //0-1背包
{
    for(int i=m;i>=v;i--)
        f[i]=max(f[i],f[i-v]+w);
}

//m背包的总容量、v物品的体积、w物品的价值
void CompletePack(int m,int v,int w)  //完全背包
{
    for(int i=v;i<=m;i++)
        f[i]=max(f[i],f[i-v]+w);
}

//m背包的总容量、v物品的体积、w物品的价值、num物品的数量
void MultiplePack(int m,int v,int w,int num)//多重背包
{
    if(v*num>=m)
    {
        CompletePack(m,v,w);
        return ;
    }
    int k=1;
    for(k=1;k<=num;k<<=1)
    {
        OneZeroPack(m,k*v,k*w);
        num=num-k;
    }
    if(num)
        OneZeroPack(m,num*v,num*w);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////

int V;
void CompletePack(int cost,int weight)
{
    for(int v=cost;v<=V;v++){
        dp[v]=max(dp[v],dp[v-cost]+weight);
    }
}

void ZeroOnepack(int cost,int weight)
{
    for(int v=V;v>=cost;v--)
        dp[v]=max(dp[v],dp[v-cost]+weight);
}

void MultiplePack(int cost,int weight,int amount)
{
    if(cost*amount>=V){
        CompletePack(cost,weight);
        return;
    }
    int k=1;

    while(k<amount){
        ZeroOnepack(k*cost,k*weight);
        amount-=k;
        k*=2;
    }
    ZeroOnepack(amount*cost,amount*weight);
}