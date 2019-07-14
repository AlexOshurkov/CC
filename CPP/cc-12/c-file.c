
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int MultipleByTwo(int num)
{
	return num * 2;
}

typedef int (*MyFuncType)(int);

void MyForEach(int* arr, size_t len, MyFuncType func)
{
	if (arr == 0)
		return;

	for (size_t i = 0; i < len; ++i)
		arr[i] = func(arr[i]);
}

void TestMyForEach()
{
	int* arr = 0;// = { 1, 3, 5, 7, 9 };
	MyForEach(arr, 10, MultipleByTwo);
}

typedef struct Node Node;

struct Node
{
	Node* left;
	Node* right;
	int  val;
};

Node* CreateDblList(int* arr, size_t len)
{
	Node* root = 0;
	Node* list = 0;

	if (arr == 0)
		return root;

	for (size_t i = 0; i < len; ++i)
	{
		Node* curr = malloc(sizeof(Node));
		curr->left = 0;
		curr->right = 0;
		curr->val = arr[i];

		if (list == 0)
			list = curr;
		else
		{
			curr->left = list;
			list->right = curr;
			list = curr;
		}

		if (root == 0)
			root = curr;
	}

	return root;
}

void TestDblList()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
	Node* list = CreateDblList(arr, sizeof(arr) / sizeof(arr[0]));
}

//-----------------------------------------------------------------------------
#define NUM_IDS 8
#define MAX_ALIAS_NAME 64

static int ids[NUM_IDS];
static int curr_alias = -1;

typedef struct {
	char* alias;   /* '\0'-terminated C string */
	int   specific_id;
} aliasID;

static int GetNumberOfAliases()
{
	return NUM_IDS;
}

int* GetSomeIDs()
{
	for (size_t i = 1; i <= NUM_IDS; ++i)
		ids[i - 1] = i * 10 + i;

	return ids;
}

void BeginReadAliases()
{
	curr_alias = 0;
}

aliasID* GetNextAlias(void)
{
	if (curr_alias < 0)
		return 0;
	else if (curr_alias < NUM_IDS)
	{
		aliasID* alias = malloc(sizeof(aliasID));
		alias->specific_id = ids[curr_alias];
		alias->alias = malloc(MAX_ALIAS_NAME);

		sprintf(alias->alias, "Alias name: %u", ids[curr_alias]);
		++curr_alias;
		return alias;
	}
	else
	{
		curr_alias = -1;
		return 0;
	}
}

void PrintAliases()
{
	int num_aliases = GetNumberOfAliases();
	BeginReadAliases();
	aliasID* alias = GetNextAlias();

	printf("\nNumber of aliases: %i", num_aliases);

	while (alias != 0)
	{
		printf("\nAlias ID: %u, \"%s\"", alias->specific_id, alias->alias);
		alias = GetNextAlias();
	}
}