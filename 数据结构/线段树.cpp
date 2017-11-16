const int maxn = 55555;  
int sum[maxn << 2]; 
int lazy[maxn << 2];
void PushUp(int rt)  
{  
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}  
  
void pushdown(int rt,int len){
    if(lazy[rt]){
        lazy[rt<<1]=lazy[rt];
        lazy[rt<<1|1]=lazy[rt];
        sum[rt<<1]=lazy[rt]*(len-(len>>1));
        sum[rt<<1|1]=lazy[rt]*(len>>1);
        lazy[rt]=0;
    }
}
  
void build(int l, int r, int rt)//建立线段树  (1,n,1)
{  
	sum[rt]=0;
    if (l == r)  
        //scanf("%d", &sum[rt]);  
    {  
        return;  
    }  
    int m = (l + r) >> 1;
    build(l, m, rt << 1);  
    build(m + 1, r, rt << 1 | 1);  
    PushUp(rt);  
}  
  
void update(int p, int add, int l, int r, int rt)  //(l,r,1,n,1)
{  
    if (l == r)  
    {  
        sum[rt] += add;  
        return;  
    }  
    int m = (l + r) >> 1;  
    if (p <= m) update(p, add, l, m,	 rt << 1);  
    else update(p, add, m + 1, r, rt << 1 | 1);  
    PushUp(rt);  
}  
  
int query(int ll, int rr, int l, int r, int rt)			//(l,r,1,n,1)查找值属于ll到rr的数，在区间l到r内查找
{  
    if (ll <= l && rr >= r) return sum[rt];  
    int m = (l + r) >> 1;  
    int ret = 0;  
    if (ll <= m) ret += query(ll, rr, l, m, rt << 1);  
    if (rr > m) ret += query(ll, rr, m + 1, r, rt << 1 | 1);  
    return ret;  
}  