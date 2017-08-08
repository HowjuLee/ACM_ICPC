//欧拉函数

int prime[MAX_N];
bool is_prime[MAX_N+1];

void sieve(int n)
{
	int p=0;
	for(int i=0;i<=n;i++)
		is_prime[i]=true;

	is_prime[0]=is_prime[1]=false;

	for(int i=2;i<=n;i++)
	{
		if(is_prime[i])
		{
			prime[p++]=i;
			for(int j=2*i;j<=n;j+=i)
				is_prime[j]=false;
		}
	}
	//return p;
}
void make()
{
	phi[1] = 1;  
		for (i = 2; i < 10000; i++) {  
			if (!mark[i]) {  
				phi[i] = i - 1;  
				continue;  
			}  
			for (j = 0; j < size && prime[j] * prime[j] <= i; j++) {  
				if (i % prime[j] == 0) {  
					if (i / prime[j] % prime[j] == 0)  
						phi[i] = prime[j] * phi[i / prime[j]];  
					else  
						phi[i] = (prime[j] - 1) * phi[i / prime[j]];  
					break;  
				}  
			}  
		}
}



/////////
int phi(int n)  
{  
    int i,rea=n;  
    for(i=2;i*i<=n;i++)  
    {  
        if(n%i==0)  
        {  
            rea=rea-rea/i;  
            while(n%i==0)  n/=i;  
        }  
    }  
    if(n>1)  
        rea=rea-rea/n;  
    return rea;  
} 