/*一般是求小于等于数字N的某些特征数字个数，或者是区间[L,R]的之间的某些特征数字个数，后者一般可以转换成求差的方式来做。*/


int f(int num){
    int ans;
    int pos = 0;
    while(num){
        digit[++pos]=num%10;
        num=num/10;
    }
    return dfs( pos, s , true );
}
/*
digit为处理串的每个数位的数值。
s为初始的状态。
如果有其他限定条件，dfs中可以增加参数。*/



int dfs(int l, int s, bool jud) {
    if ( l==-1 ) return s == target_s;
    if ( !e && ~f[l][s] ) return f[l][s];
    int ans = 0;
    int nex = e ? digit[i] : 9;
    for (int d = 0; d <=  nex; ++d)
        ans += dfs( l-1 , new_s( s,d ) , e && d==nex );
    return jud ? ans : f[l][s] = ans;
}

/*其中：
f为记忆化数组；
l为当前处理串的第l位（权重表示法，也即后面剩下l+1位待填数）；
s为之前数字的状态（如果要求后面的数满足什么状态，也可以再记一个目标状态t之类，for的时候枚举下t）；
jud表示之前的数是否是上界的前缀（即后面的数能否任意填）。
for循环枚举数字时，要注意是否能枚举0，以及0对于状态的影响，
有的题目前导0和中间的0是等价的，但有的不是，对于后者可以在dfs时再加一个状态变量z，表示前面是否全部是前导0，也可以看是否是首位，
然后外面统计时候枚举一下位数。It depends.
于是关键就在怎么设计状态。当然做多了之后状态一眼就可以瞄出来。*/