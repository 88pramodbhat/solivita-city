#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

void createBadCharTable(const string& pattern, unordered_map<char, int>& badCharTable) {
    int m = pattern.length();
    for (int i = 0; i < m; ++i) {
        badCharTable[pattern[i]] = i;
    }
}

void boyerMooreSearch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();

    unordered_map<char, int> badCharTable;

    
    createBadCharTable(pattern, badCharTable);

    int s = 0;  
    while (s <= n - m) {
        int j = m - 1; 
        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }
        
        if (j < 0) {
            cout << "Pattern found at index " << s << endl;
            s += (s + m < n) ? m - badCharTable[text[s + m]] : 1;  
        } else {
            s += max(1, j - badCharTable[text[s + j]]);
        }
    }
}

int main() {
    string text = "ABAAABCDABAAABCDABACDABABCDBA";
    string pattern = "ABCD";
    
    boyerMooreSearch(text, pattern);
    
    return 0;
}
