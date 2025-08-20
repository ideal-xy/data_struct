#include <vector>
#include <string>

using namespace std;

vector<int> getPM(string pattern) {
    int m = pattern.size();
    vector<int> pm(m, 0);  // pm[i]表示pattern[0..i]的最长前缀后缀公共长度

    for (int i = 1; i < m; i++) 
    {
        int len = pm[i-1];  
        
        // 若当前字符不匹配，尝试更短的前缀
        while (len > 0 && pattern[i] != pattern[len]) 
        {
            len = pm[len - 1];  // 核心：利用之前的PM值缩短长度
        }
        
        // 若匹配，长度加1
        if (pattern[i] == pattern[len]) 
        {
            len++;
        }
        
        pm[i] = len;  // 记录当前位置的PM值
    }
    
    return pm;
}

// 使用PM值进行KMP匹配
int kmpMatch(string text, string pattern, vector<int>& pm) {
    int n = text.size();
    int m = pattern.size();
    int i = 0;  // 主串指针
    int j = 0;  // 模式串指针
    
    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
            if (j == m) {  // 匹配成功
                return i - m;
            }
        } else {
            if (j > 0) {
                // 利用PM值回退模式串指针（本质是向右移动模式串）
                j = pm[j-1];
            } else {
                // 模式串指针在0位置时，主串后移
                i++;
            }
        }
    }
    return -1;  // 匹配失败
}
