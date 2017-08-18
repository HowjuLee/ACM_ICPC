#define M  249997 
#define M1 1000001 
#define M2 0xF0000000 
 
// RS Hash Function  
unsigned int RSHash(char*str) 
{ 
    unsigned int b=378551 ; 
    unsigned int a=63689 ; 
    unsigned int hash=0 ; 
     
    while(*str) 
    { 
        hash=hash*a+(*str++); 
        a*=b ; 
    } 
     
    return(hash % M); 
} 
 
// JS Hash Function  
unsigned int JSHash(char*str) 
{ 
    unsigned int hash=1315423911 ; 
     
    while(*str) 
    { 
        hash^=((hash<<5)+(*str++)+(hash>>2)); 
    } 
     
    return(hash % M); 
} 
 
// P. J. Weinberger Hash Function  
unsigned int PJWHash(char*str) 
{ 
    unsigned int BitsInUnignedInt=(unsigned int)(sizeof(unsigned int)*8); 
    unsigned int ThreeQuarters=(unsigned int)((BitsInUnignedInt*3)/4); 
    unsigned int OneEighth=(unsigned int)(BitsInUnignedInt/8); 
    unsigned int HighBits=(unsigned int)(0xFFFFFFFF)<<(BitsInUnignedInt-OneEighth); 
    unsigned int hash=0 ; 
    unsigned int test=0 ; 
     
    while(*str) 
    { 
        hash=(hash<<OneEighth)+(*str++); 
        if((test=hash&HighBits)!=0) 
        { 
            hash=((hash^(test>>ThreeQuarters))&(~HighBits)); 
        } 
    } 
     
    return(hash % M); 
} 
 
// ELF Hash Function  
unsigned int ELFHash(char*str) 
{ 
    unsigned int hash=0 ; 
    unsigned int x=0 ; 
     
    while(*str) 
    { 
        hash=(hash<<4)+(*str++); 
        if((x=hash&0xF0000000L)!=0) 
        { 
            hash^=(x>>24); 
            hash&=~x ; 
        } 
    } 
     
    return(hash % M); 
} 
 
// BKDR Hash Function  
unsigned int BKDRHash(char*str) 
{ 
    unsigned int seed=131 ;// 31 131 1313 13131 131313 etc..  
    unsigned int hash=0 ; 
     
    while(*str) 
    { 
        hash=hash*seed+(*str++); 
    } 
     
    return(hash % M); 
} 
 
// SDBM Hash Function  
unsigned int SDBMHash(char*str) 
{ 
    unsigned int hash=0 ; 
     
    while(*str) 
    { 
        hash=(*str++)+(hash<<6)+(hash<<16)-hash ; 
    } 
     
    return(hash % M); 
} 
 
// DJB Hash Function  
unsigned int DJBHash(char*str) 
{ 
    unsigned int hash=5381 ; 
     
    while(*str) 
    { 
        hash+=(hash<<5)+(*str++); 
    } 
     
    return(hash % M); 
} 
 
// AP Hash Function  
unsigned int APHash(char*str) 
{ 
    unsigned int hash=0 ; 
    int i ; 
     
    for(i=0;*str;i++) 
    { 
        if((i&1)==0) 
        { 
            hash^=((hash<<7)^(*str++)^(hash>>3)); 
        } 
        else  
        { 
            hash^=(~((hash<<11)^(*str++)^(hash>>5))); 
        } 
    } 
     
    return(hash % M); 
} 





//////////////////////////
/////数值hash
// 整数hash
// 大素数104729,  224737,  611953,  1299709,  2015177
const int MOD =  20023;
bool bhash[MOD];
int vhash[MOD];
int cnt[MOD];
bool find_hash(int & pos)
{
    int val = pos;
    pos %= MOD;
    for (; bhash[pos]; pos=(pos+1)%MOD)
    {
        if (vhash[pos] == val)return true;
    }
    return false;
}
int make_hash(int  val)
{
    int pos = val;
    if (! find_hash(pos))
    {
        bhash[pos]  = true;
        vhash[pos] = val;
        cnt[pos] =  0;
    }
    cnt[pos] ++;
    return  pos;
}
//字符串hash
const int MOD =  20023;
bool bhash[MOD];
char vhash[MOD][45];
char  str[45];
int cal_str()
{
    int i, j, pos;
    for (i=pos=0,j=1; str[i]; i++,j=(j*27)&INT_MAX,pos&=INT_MAX)
    {
        int num = str[i] - 'a';
        if (str[i] == ' ')num = 26;
        pos += j*num;
    }
    return pos % MOD;
}
bool find_hash(int & pos)
{
    pos = cal_str();
    for (; bhash[pos]; pos=(pos+1)%MOD)
    {
        if (strcmp(vhash[pos], str) ==  0)return true;
    }
    return false;
}
int make_hash()
{
    int pos;
    if (! find_hash(pos))
    {
        bhash[pos]  = true;
        strcpy(vhash[pos], str);
    }
    return pos;
}