#include "stdafx.h"
#pragma hdrstop

using namespace std;

struct Node {
    Node* l = nullptr;
    Node* r = nullptr;
    int v = 0;
};

Node* createTree() {
    Node* l41 = new Node { 0, 0, 41 };
    Node* l42 = new Node { 0, 0, 42 };
    Node* l43 = new Node { 0, 0, 43 };
    Node* l44 = new Node { 0, 0, 44 };
    Node* l45 = new Node { 0, 0, 45 };
    Node* l46 = new Node { 0, 0, 46 };
    Node* l47 = new Node { 0, 0, 47 };
    Node* l48 = new Node { 0, 0, 48 };

    Node* l31 = new Node{ l41, l42, 31 };
    Node* l32 = new Node{ l43, l44, 32 };
    Node* l33 = new Node{ l45, l46, 33 };
    Node* l34 = new Node{ l47, l48, 34 };

    Node* l21 = new Node{ l31, l32, 21 };
    Node* l22 = new Node{ l33, l34, 22 };

    Node* l11 = new Node{ l21, l22, 11 };

    return l11;
}
void printInOrder(Node* n) {
    
    if (n == nullptr)
        return;

    printInOrder(n->l);

    cout << n->v << ", ";

    printInOrder(n->r);
}

void printPreOrder(Node* n) {

    if (n == nullptr)
        return;

    cout << n->v << ", ";

    printPreOrder(n->l);
    printPreOrder(n->r);
}

void printPostOrder(Node* n) {

    if (n == nullptr)
        return;

    printPostOrder(n->l);
    printPostOrder(n->r);

    cout << n->v << ", ";
}

void findLCA(Node* n, int v1, int v2) {

}


void testTree() {
    Node* root = createTree();

    cout << "\nIn order  : ";
    printInOrder(root);

    cout << "\nPre order : ";
    printPreOrder(root);

    cout << "\nPost order: ";
    printPostOrder(root);
}

string findLongestUCSubstr(const string& str, size_t numuc) {
    unordered_set<char> found_chars;

    string substr;  //  current substring
    string resstr;  //  res substring

    string::const_iterator it = str.begin();

    while (it != str.end()) {

        if (found_chars.find(*it) == found_chars.end()) {
            if (found_chars.size() < numuc) {
                substr += *it;
                found_chars.insert(*it);
            } 
            else {
                if (substr.size() > resstr.size())
                    if (substr.size() >= numuc && substr.size() >= resstr.size())
                        resstr = substr;

                substr.clear();
                found_chars.clear();                    
                it -= numuc;
            }
        }
        else
            substr += *it;

        ++it;
    }

    return (substr.size() >= resstr.size() && found_chars.size() == numuc) ? substr : resstr;
}

void testUCSubstr() {

    vector<string> cases{ 
        "",
        "a",
        "ab",
        "abc",
        "hello",
        "ababcd",
        "cdcbcbababcd",
        "1212121212",
        "0981212121212",
        "0981212121212980",
        "aaabbccccccdd",
        "aboooooabfab"
    };

    for (const auto& v : cases)
        cout << "\nCase: " << v << ", max substr: " << findLongestUCSubstr(v, 3);
}

int main5(int, char**) {
    cout << "\n *** main-5 ***";

    //testTree();
    //testUCSubstr();
    return 0;
}
