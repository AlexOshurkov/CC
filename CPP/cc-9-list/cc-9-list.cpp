// cc-9-list.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;


struct node_t {
	int val;
	node_t* pnext;

	node_t() : val(0), pnext(0) {}
};

int len_word(const string& s)
{
	if (s.empty())
		return 0;

	int wlen = 0;  // last word length


	return wlen;
}

void check_anagrams(const vector<string>& first_words, const vector<string>& second_words) 
{

	for (size_t i = 0; i < first_words.size() && second_words.size(); i++) {
		char w1[256];
		char w2[256];
		::memset(w1, 0, sizeof(w1)*sizeof(w1[0]));
		::memset(w2, 0, sizeof(w1)*sizeof(w2[0]));

		string s1 = first_words[i];
		string s2 = second_words[i];

		for (size_t p1 = 0; p1 < s1.size(); p1++)
			w1[s1[p1]]++;
		for (size_t p2 = 0; p2 < s2.size(); p2++)
			w2[s2[p2]]++;

		bool flag = true;

		for (size_t pp = 0; pp < 256; pp++)
			if (w1[pp] != w2[pp]) {
				flag = false;
				break;
			}

		cout << (flag ? "1" : "0") << endl;
	}

	

}
	struct ListNode{
		int val;
	ListNode* next;
};

ListNode* getLastKthNodeImpl(ListNode* head, int k, ListNode* node)
{
	if (head == 0)
		return k ? 0 : node;

	if (k)
		return getLastKthNodeImpl(head->next, k - 1, node);
	else
		return getLastKthNodeImpl(head->next, k, node->next);
}

ListNode* getLastKthNode(ListNode* head, int k)
{
	return getLastKthNodeImpl(head, k, head);
}

ListNode* reverse_list(ListNode* head)
{
	ListNode* prev = 0;
	ListNode* next = 0;

	while (head)
	{
		next = head->next;
		head->next = prev;
		prev = head;
		head = next;
	}

	return prev;
}

int main(int argc, _TCHAR* argv[])
{
	int l = 0;
	l = len_word("");
	l = len_word("sdfsd");
	l = len_word("dsfs wer");
	l = len_word("     ");
	l = len_word("s ssdf     ");

	vector<string> vs;
	bool res = false;
	res = check_braces("");
	res = check_braces("[][[]]((([]))){[({[()]})]}");
	res = check_braces("([])]");
	res = check_braces(")(){}");
	res = check_braces("[]({})");
	res = check_braces("(234[dfg]3)");
	
	print_perm("112");

	int i = 0;
	ListNode* ln = new ListNode();
	ListNode* beg = ln;
	for (i = 2; i > 0; i--) {
		ln->val = i;
		ln->next = i > 1 ? new ListNode() : 0;
		ln = ln->next;
	}

	ListNode* rlist = reverse_list(beg);

	ListNode* n = 0;
	n = getLastKthNode(beg, 1);
	n = getLastKthNode(beg, 2);
	n = getLastKthNode(beg, 3);
	n = getLastKthNode(beg, 4);

	n = getLastKthNode(beg, 0);
	n = getLastKthNode(beg, 10);


	string s1;
	string s2 = "12345";
	string s3 = "123";
	string s4 = "1";

	reverse_str(s1);
	reverse_str(s2);
	reverse_str(s3);
	reverse_str(s4);

	char buf[100];
	::memset(buf, 0, 100);
	strcpy(buf, "12 34 5");
	repl_str(buf, ' ', "***");

	::memset(buf, 0, 100);
	strcpy(buf, "12345");
	repl_str(buf, ' ', "***");

	::memset(buf, 0, 100);
	strcpy(buf, " 12 34 5");
	repl_str(buf, ' ', "***");

	::memset(buf, 0, 100);
	strcpy(buf, "12 34 5 ");
	repl_str(buf, ' ', "***");

	::memset(buf, 0, 100);
	strcpy(buf, "  12  34  5  ");
	repl_str(buf, ' ', "***");

	unsigned char x = 0x55;

	double a = 0x12345678;
	double b = 0x87654321;

	swap_vals((uint64_t&)a, (uint64_t&)b);

	return 0;
}

