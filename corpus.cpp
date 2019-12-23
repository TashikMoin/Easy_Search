#include <cstring>
#include <iostream>
using namespace std;

class listNode {
   public:
    int index;
    string source;
    listNode* next;

    listNode() {
        index = 0;
        source = "";
        next = NULL;
    }

    listNode(int __index, string __source, listNode* __next = NULL) {
        index = __index;
        source = __source;
        next = __next;
    }
};

class infoList {
    listNode *head, *tail;

   public:
    infoList() {
        head = tail = NULL;
    }

    void addToTail(int __index, string __source) {
        if (head == NULL) {
            head = tail = new listNode(__index, __source);
        } else {
            tail->next = new listNode(__index, __source);
            tail = tail->next;
        }
    }

    listNode* getHead() {
        return head;
    }

    ~infoList() {
        listNode* temp;
        while (head != NULL) {
            temp = head->next;
            delete head;
            head = temp;
        }
    }
};

class trieNode {
   private:
    trieNode* data[26];
    bool endOfQuery;
    infoList list;

   public:
    trieNode() : list() {
        endOfQuery = false;

        for (int i = 0; i < 26; i++) {
            data[i] = NULL;
        }
    }

    void insert(string __original, string __input, int __index) {
        trieNode* temp = this;

        for (int i = 0; i < __input.size(); i++) {
            int index = __input[i] - 'A';
            if (temp->data[index] == NULL) {
                temp->data[index] = new trieNode();
                temp = temp->data[index];
                temp->list.addToTail(__index, __original);
            } else {
                temp = temp->data[index];
                temp->list.addToTail(__index, __original);
            }
        }
        temp->endOfQuery = true;
    }

    bool search(string __searchQuery) {
        trieNode* temp = this;
        listNode* start = NULL;

        for (int i = 0; i < __searchQuery.size(); i++) {
            int index = __searchQuery[i] - 'A';
            if (temp->data[index] == NULL) {
                return false;
            } else {
                temp = temp->data[index];
            }
        }

        start = temp->list.getHead();
        cout << "Search for " << __searchQuery << '\n';

        while (start != NULL) {
            cout << "Pattern match in: " << start->source << " start: " << start->index << '\n';
            start = start->next;
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
            this->root.insert(__key, __key.substr(i), i);
        }
    }

    void search(string __searchQuery) {
        if (!root.search(__searchQuery)) {
            cout << __searchQuery << " not found\n";
        }
    }

    ~Trie() {}
};

int main(int argc, char const* argv[]) {
    Trie t;
    t.insert("ACGTACGT");
    t.search("ANA");
    return 0;
}