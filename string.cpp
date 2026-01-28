#include <iostream>
#include <numeric>

#define MAX_LEN 25

struct SString
{
    char ch[MAX_LEN];
    int length;
};

struct Hstring
{
    char* str;
    int length;
};

int Index(SString& s,SString& t) // 最简单的模式匹配
{
    int i=1,j=1;
    while(i < s.length && j<t.length)
    {
        if (s.ch[i] == t.ch[j]) 
        {
            ++i;
            ++j;
        }
        else
        {
            i = i-j+2;
            j=1;
        }

        if (j == t.length+1) {return i-t.length;}
    }
    return -1;
}


int main()
{
    std::cout << "Hello, World!" << std::endl;
    return 0;
    std::vector<int> vec{1,2,3,4,5};
    std::accumulate(vec.begin(),vec.end(),0);
}



