typedef struct Trie_node  
{  
    int count;                    // 统计单词前缀出现的次数  
    struct Trie_node* next[26];   // 指向各个子树的指针  
    bool exist;                   // 标记该结点处是否构成单词    
}TrieNode , *Trie;  
  
TrieNode* createTrieNode()  
{  
    TrieNode* node = (TrieNode *)malloc(sizeof(TrieNode));  
    node->count = 0;  
    node->exist = false;  
    memset(node->next , 0 , sizeof(node->next));    // 初始化为空指针  
    return node;  
}  
  
void Trie_insert(Trie root, char* word)  
{  
    Trie node = root;  
    char *p = word;  
    int id;  
    while( *p )  
    {  
        id = *p - 'a';  
        if(node->next[id] == NULL)  
        {  
            node->next[id] = createTrieNode();  
        }  
        node = node->next[id];  // 每插入一步，相当于有一个新串经过，指针向下移动  
        ++p;  
        node->count += 1;      // 这行代码用于统计每个单词前缀出现的次数（也包括统计每个单词出现的次数）  
    }  
    node->exist = true;        // 单词结束的地方标记此处可以构成一个单词  
}  
  
int Trie_search(Trie root, char* word)  
{  
    Trie node = root;  
    char *p = word;  
    int id;  
    while( *p )  
    {  
        id = *p - 'a';  
        node = node->next[id];  
        ++p;  
        if(node == NULL)  
            return 0;  
    }  
    return node->count;  
}



void de(Trie p)
{
    if(p==NULL)
        return ;
    int i;
    for(i=0;i<10;i++)
    {
        de(p->next[i]);
    }
    free(p);

}