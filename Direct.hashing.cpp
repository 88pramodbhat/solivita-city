#include <iostream>
#include <vector>
#include <string>

using namespace std;


const int TABLE_SIZE = 10;
class HashTable {
private:
    vector<pair<int, string>> table[TABLE_SIZE]; 
    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    void insert(int key, const string &value) {
        int index = hashFunction(key);
        table[index].push_back(make_pair(key, value)); 
    }
    string search(int key) {
        int index = hashFunction(key);
        for (auto &entry : table[index]) {
            if (entry.first == key) {
                return entry.second; 
            }
        }

        return "Not Found"; 
    }
    void remove(int key) {
        int index = hashFunction(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it);
                cout << "Key " << key << " deleted successfully.\n";
                return;
            }
        }

        cout << "Key " << key << " not found.\n";
    }
    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Index " << i << ": ";
            for (auto &entry : table[i]) {
                cout << "(" << entry.first << ", " << entry.second << ") ";
            }
            cout << endl;
        }
    }
};

int main() {
    HashTable ht;
    ht.insert(101, "Fire Hydrant 1");
    ht.insert(202, "Hospital 1");
    ht.insert(303, "Police Station 1");
  
    cout << "Hash Table after insertion:\n";
    ht.display();

    int searchKey = 202;
    cout << "\nSearching for key " << searchKey << ": " << ht.search(searchKey) << endl;

    int removeKey = 101;
    ht.remove(removeKey);
  
    cout << "\nHash Table after deletion:\n";
    ht.display();

    return 0;
}
