inline void BuildNext(const char* pattern, size_t length, unsigned int* next)  
{  
    unsigned int i, t;  
  
    i = 1;  
    t = 0;  
    next[1] = 0;  
  
    while(i < length + 1)  
    {  
        while(t > 0 && pattern[i - 1] != pattern[t - 1])  
        {  
            t = next[t];  
        }  
  
        ++t;  
        ++i;  
  
        if(pattern[i - 1] == pattern[t - 1])  
        {  
            next[i] = next[t];  
        }  
        else  
        {  
            next[i] = t;  
        }  
    }  
  
    //pattern末尾的结束符控制，用于寻找目标字符串中的所有匹配结果用  
    while(t > 0 && pattern[i - 1] != pattern[t - 1])  
    {  
        t = next[t];  
    }  
  
    ++t;  
    ++i;  
  
    next[i] = t;  
}  



unsigned int KMP(const char* text, size_t text_length, const char* pattern, size_t pattern_length, unsigned int* matches)  
{  
    unsigned int i, j, n;  
    unsigned int next[pattern_length + 2];  
  
    BuildNext(pattern, pattern_length, next);  
  
    i = 0;  
    j = 1;  
    n = 0;  
  
    while(pattern_length + 1 - j <= text_length - i)  
    {  
        if(text[i] == pattern[j - 1])  
        {  
            ++i;  
            ++j;  
  
            //发现匹配结果，将匹配子串的位置，加入结果  
            if(j == pattern_length + 1)  
            {  
                matches[n++] = i - pattern_length;  
                j = next[j];  
            }  
        }  
        else  
        {  
            j = next[j];  
  
            if(j == 0)  
            {  
                ++i;  
                ++j;  
            }  
        }  
    }  
  
    //返回发现的匹配数  
    return n;  
} 