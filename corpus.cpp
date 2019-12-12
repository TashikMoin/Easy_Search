#include <iostream>
using namespace std;

class trieNode {
   private:
    trieNode* data[26];
    bool endOfQuery;

   public:
    trieNode() {
        endOfQuery = false;

        for (int i = 0; i < 26; i++) {
            data[i] = NULL;
        }
    }

    void insert(string __input) {
        trieNode* temp = this;

        for (int i = 0; i < __input.size(); i++) {
            int index = __input[i] - 'A';
            if (temp->data[index] == NULL) {
                temp->data[index] = new trieNode();
                temp = temp->data[index];
            } else {
                temp = temp->data[index];
            }
        }
        temp->endOfQuery = true;
    }

    bool search(string __searchQuery) {
        trieNode* temp = this;

        for (int i = 0; i < __searchQuery.size(); i++) {
            int index = __searchQuery[i] - 'A';
            if (temp->data[index] == NULL) {
                return false;
            } else {
                temp = temp->data[index];
            }
        }

        return (temp != NULL && temp->endOfQuery == true);
    }

    ~trieNode() {}
};

class Trie {
   private:
    trieNode root;

   public:
    Trie() : root() {}
    void insert(string __key) {
        for (int i = 0; i < __key.size(); i++) {
            this->root.insert(__key.substr(i));
        }
    }

    void search(string __searchQuery) {
        if (root.search(__searchQuery)) {
            cout << __searchQuery << " is present\n";
        } else {
            cout << __searchQuery << " is not present\n";
        }
    }

    ~Trie() {}
};

int main(int argc, char const* argv[]) {
    Trie t;
    t.insert("BANANA");
    t.search("BANANA");
    return 0;
}