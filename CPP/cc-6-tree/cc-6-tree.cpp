// cc-6-tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

struct node_t {
	int data;
	node_t* l;
	node_t* r;

	node_t() : data(0), l(0), r(0) {}
	node_t(int v) : data(v), l(0), r(0) {}
};

void add_node(node_t* n, int v) 
{
	if (n == 0) {
		n = new node_t(v);
		return;
	}

	if (v < n->data)
		add_node(n->l, v);
	else if (v > n->data)
		add_node(n->r, v);
	else
		n->data = v;
}

node_t* find_node(node_t* n, int v) {

	if (n) {
		if (n->data == v)
			return n;
		else
			return v < n->data ? find_node(n->l, v) : find_node(n->r, v);
	}
	else
		return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	node_t* root = new node_t(10);
	add_node(root, 15);
	add_node(root, 5);

	add_node(root, 12);
	add_node(root, 13);
	add_node(root, 11);

	node_t* n = 0;
	n = find_node(root, 14);

	n = find_node(root, 11);
	n = find_node(root, 12);
	n = find_node(root, 13);
	n = find_node(root, 15);
	n = find_node(root, 5);

	return 0;
}

