#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;

void createBadCharTable(const string& pattern, unordered_map<char, int>& badCharTable) {
    int m = pattern.length();
  
    for (int i = 0; i < m; ++i) {
        badCharTable[pattern[i]] = i;  
    }
}


vector<int> createGoodSuffixTable(const string& pattern) {
    int m = pattern.length();
    vector<int> goodSuffix(m, m); 
    
      vector<int> suffix(m + 1, 0);
    
 
    suffix[m - 1] = m;
    for (int i = m - 2; i >= 0; --i) {
        int j = i;
        while (j >= 0 && pattern[j] == pattern[m - 1 - (i - j)]) {
            --j;
        }
        suffix[i] = i - j;
    }
    
  
    for (int i = 0; i < m; ++i) {
        if (suffix[i] == i + 1) {
            for (int j = m - 1; j > i; --j) {
                if (goodSuffix[j] == m) {
                    goodSuffix[j] = m - 1 - i;
                }
            }
        }
    }
    
    return goodSuffix;
}


void boyerMooreSearch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();
    
    unordered_map<char, int> badCharTable;
    vector<int> goodSuffix = createGoodSuffixTable(pattern);

 
    createBadCharTable(pattern, badCharTable);

    int s = 0; 
    while (s <= n - m) {
        int j = m - 1; 
        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }

        if (j < 0) { 
            cout << "Pattern found at index " << s << endl;
         
            s += (s + m < n) ? max(goodSuffix[0], m - badCharTable[text[s + m]]) : 1;
        } else {
            
            s += max(goodSuffix[j], j - badCharTable[text[s + j]]);
        }
    }
}

int main() {
  
    string text = "ABAAABCDABAAABCDABACDABABCDBA";  

    string pattern = "ABCD";  
    
    cout << "Searching for pattern: \"" << pattern << "\" in text: \"" << text << "\"\n";
    boyerMooreSearch(text, pattern);
    
    return 0;
}
