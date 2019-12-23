#include <bits/stdc++.h>
#include <cstring>
#include <ctime>
#include <iostream>
using namespace std;

class listNode {
   public:
    int sIndex;
    int eIndex;
    string source;
    listNode* next;

    listNode() {
        sIndex = 0;
        eIndex = 0;
        source = "";
        next = NULL;
    }

    listNode(int __sIndex, int __eIndex, string __source, listNode* __next = NULL) {
        sIndex = __sIndex;
        eIndex = __eIndex;
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

    void addToTail(int __sIndex, int __eIndex, string __source) {
        if (head == NULL) {
            head = tail = new listNode(__sIndex, __eIndex, __source);
        } else {
            tail->next = new listNode(__sIndex, __eIndex, __source);
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
        transform(__input.begin(), __input.end(), __input.begin(), ::toupper);

        for (int i = 0; i < __input.size(); i++) {
            int index = __input[i] - 'A';
            if (temp->data[index] == NULL) {
                temp->data[index] = new trieNode();
                temp = temp->data[index];
                temp->list.addToTail(__index, __index + i, __original);
            } else {
                temp = temp->data[index];
                temp->list.addToTail(__index, __index + i, __original);
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
        cout << "Query for search: " << __searchQuery << '\n';

        while (start != NULL) {
            cout << "Pattern match in: " << start->source << " start: " << start->sIndex << " end: " << start->eIndex << '\n';
            start = start->next;
        }

        return (true);
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
        transform(__searchQuery.begin(), __searchQuery.end(), __searchQuery.begin(), ::toupper);
        if (!root.search(__searchQuery)) {
            cout << __searchQuery << " not found\n";
        }
    }

    ~Trie() {}
};

int main(int argc, char const* argv[]) {
    Trie t;
    t.insert("cacacaaa");
    t.insert("accccgac");
    t.insert("tccttagc");
    t.search("accc");
    return 0;
}

/* 
    clock_t start;
    start = clock();
    start = clock() - start;
    cout << "Time taken for insertion: " << (float)start / CLOCKS_PER_SEC << " seconds\n"; 
 */
