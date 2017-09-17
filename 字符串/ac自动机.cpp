const int maxn = 1e7 + 5;
const int MAX = 10000000;   //串长度
int cnt;
struct node{
    node *next[26];
    node *fail;
    int sum;
};
node *root;
char key[70];
node *q[MAX];
int head,tail;
node *newnode;
char pattern[maxn];
int N;
void Insert(char *s)
{
    node *p = root;
    for(int i = 0; s[i]; i++)
    {
        int x = s[i] - 'a';
        if(p->next[x] == NULL)
        {
            newnode=(struct node *)malloc(sizeof(struct node));
            for(int j=0;j<26;j++) newnode->next[j] = 0;
            newnode->sum = 0;newnode->fail = 0;
            p->next[x]=newnode;
        }
        p = p->next[x];
    }
    p->sum++;
}
void build_fail_pointer()
{
    head = 0;
    tail = 1;
    q[head] = root;
    node *p;
    node *temp;
    while(head < tail)
    {
        temp = q[head++];
        for(int i = 0; i <= 25; i++)
        {
            if(temp->next[i])
            {
                if(temp == root)
                {
                    temp->next[i]->fail = root;
                }
                else
                {
                    p = temp->fail;
                    while(p)
                    {
                        if(p->next[i])
                        {
                            temp->next[i]->fail = p->next[i];
                            break;
                        }
                        p = p->fail;
                    }
                    if(p == NULL) temp->next[i]->fail = root;
                }
                q[tail++] = temp->next[i];
            }
        }
    }
}
void ac_automation(char *ch)
{
    node *p = root;
    int len = strlen(ch);
    for(int i = 0; i < len; i++)
    {
        int x = ch[i] - 'a';
        while(!p->next[x] && p != root) p = p->fail;
        p = p->next[x];
        if(!p) p = root;
        node *temp = p;
        while(temp != root)
        {
           if(temp->sum >= 0)
           {
               cnt += temp->sum;
               temp->sum = -1;
           }
           else break;
           temp = temp->fail;
        }
    }
}

void Init()
{
	root=(struct node *)malloc(sizeof(struct node));
    for(int j=0;j<26;j++) root->next[j] = 0;
    root->fail = 0;
    root->sum = 0;
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        Init();
        scanf("%d",&N);
        getchar();
        for(int i = 1; i <= N; i++)
        {
            gets(key);
            Insert(key);
        }
        gets(pattern);
        cnt = 0;
        build_fail_pointer();
        ac_automation(pattern);
        printf("%d\n",cnt);
    }
    return 0;
}



///////数组版
int nxt[maxlen][30],FAIL[maxlen],edd[maxlen],root,L;//nxt记录节点，在这里edd指针代表以当前节点为字符串尾的字符串个数     
    int mark[maxlen];  
    int newnode()    
    {    
        for(int i=0;i<26;i++)    
            nxt[L][i]=-1;//节点连接的边初始化为-1     
        edd[L]=0;    
        mark[L]=0;  
        return L++;    
    }    
    void init()    
    {    
        L=0;    
        root=newnode();    
    }    
        
    void insert(char buf[],int l)//trie树的建立     
    {    
        int now=root;    
        for(int i=0;i<l;i++)    
        {    
            if(nxt[now][buf[i]-'a']==-1)nxt[now][buf[i]-'a']=newnode();    
            now=nxt[now][buf[i]-'a'];    
        }    
        edd[now]++;    
    }    
    void build()//建立ac自动机     
    {    
        queue<int>que;    
        for(int i=0;i<26;i++)    
        {    
            if(nxt[root][i]==-1)nxt[root][i]=root;    
            else                                 //若有连边则将节点加入队列 ，并将FAIL指针指向root     
            {    
                FAIL[nxt[root][i]]=root;    
                que.push(nxt[root][i]);    
            }    
        }    
        while(!que.empty())    
        {    
            int now=que.front();    
            que.pop();    
            for(int i=0;i<26;i++)    
            {    
                if(nxt[now][i]==-1)            //若无连边，则将该边指向当前节点FAIL指针指向的相应字符连接的节点     
                    nxt[now][i]=nxt[FAIL[now]][i];    
                else                            //若有连边，则将儿子节点的FAIL指针指向当前节点FAIL指针指向相应字符接的节点     
                {    
                    FAIL[nxt[now][i]]=nxt[FAIL[now]][i];    
                    que.push(nxt[now][i]); //加入队列继续遍历     
                }    
            }    
        }    
    }    
    int query(char buf[],int l)    
    {    
        int now=root;    
        int res=0;    
        for(int i=0;i<l;i++)    
        {    
            now=nxt[now][buf[i]-'a'];    
            int temp=now;    
            while(temp!=root&&mark[temp]==0)//根据题目要求改变形式     
            {    
                res+=edd[temp];    
                edd[temp]=0;    
                mark[temp]=1;  
                temp=FAIL[temp];    
            }    
        }    
        return res; //在这里返回的是匹配到的模式串的数量     
    }  