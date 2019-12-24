#include <bits/stdc++.h>
#include <cstring>
#include <ctime>
#include <fstream>
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
    trieNode* data[4];
    bool endOfQuery;
    infoList list;

   public:
    trieNode() : list() {
        endOfQuery = false;

        for (int i = 0; i < 4; i++) {
            data[i] = NULL;
        }
    }

    int returnIndex(char __input) {
        if (__input == 'A') {
            return 0;
        } else if (__input == 'C') {
            return 1;
        } else if (__input == 'G') {
            return 2;
        } else if (__input == 'T') {
            return 3;
        }
        return -1;
    }

    void insert(string __original, string __input, int __index) {
        trieNode* temp = this;
        transform(__input.begin(), __input.end(), __input.begin(), ::toupper);

        for (int i = 0; i < __input.size(); i++) {
            int index = returnIndex(__input[i]);
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
        ofstream outputFile;
        outputFile.open("corpusOutput.txt");
        trieNode* temp = this;
        listNode* start = NULL;

        for (int i = 0; i < __searchQuery.size(); i++) {
            int index = returnIndex(__searchQuery[i]);
            if (temp->data[index] == NULL) {
                return false;
            } else {
                temp = temp->data[index];
            }
        }

        if (temp != NULL) {
            start = temp->list.getHead();
            cout << "Query for search: " << __searchQuery << '\n';

            while (start != NULL) {
                cout << "Pattern match in: " << start->source << " start: " << start->sIndex << " end: " << start->eIndex << '\n';
                outputFile << "Pattern match in: " << start->source << " start: " << start->sIndex << " end: " << start->eIndex << '\n';
                start = start->next;
            }
            outputFile.close();
            return (true);
        }
        return (false);
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

    void getFromFile() {
        ifstream inputFile;
        inputFile.open("input.txt");
        string input;
        while (inputFile >> input) {
            int found = input.find('N');
            if (found != string::npos) {
                continue;
            }
            this->insert(input);
        }
    }

    void search(string __searchQuery) {
        ofstream outputFile;
        outputFile.open("corpusOutput.txt");

        int found = __searchQuery.find('N');
        if (found != string::npos) {
            cout << __searchQuery << " contains undefined nucleotide\n";
            outputFile << __searchQuery << " contains undefined nucleotide\n";
            return;
        }

        transform(__searchQuery.begin(), __searchQuery.end(), __searchQuery.begin(), ::toupper);
        if (!root.search(__searchQuery)) {
            cout << __searchQuery << " not found\n";
            outputFile << __searchQuery << " not found\n";
        }
        outputFile.close();
    }

    void testFromFile() {
        ifstream inputFile;
        inputFile.open("testCase.txt");
        string input;
        inputFile >> input;
        this->search(input);
        inputFile.close();
    }

    ~Trie() {}
};

int main(int argc, char const* argv[]) {
    Trie t;
    clock_t start;
    start = clock();
    t.getFromFile();
    start = clock() - start;
    cout << "\n\nTime taken for insertion: " << (float)start / CLOCKS_PER_SEC << " seconds\n\n";
    start = clock();
    t.testFromFile();
    start = clock() - start;
    cout << "Time taken for searching: " << (float)start / CLOCKS_PER_SEC << " seconds\n";
    return 0;
}

/* 
    clock_t start;
    start = clock();
    start = clock() - start;
    cout << "Time taken for insertion: " << (float)start / CLOCKS_PER_SEC << " seconds\n"; 
 */
