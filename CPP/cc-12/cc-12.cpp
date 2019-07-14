// cc-12.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

bool CheckUniqueChars(const string& str)
{
	bool flags[256000000];
	::memset(flags, false, sizeof(flags));

	for (auto ch : str)
		if (flags[ch])
			return false;
		else
			flags[ch] = true;

	return true;
}

template<typename T>
class Stack
{
	struct node_t
	{
		T val;
		node_t* next = nullptr;
		node_t(T v) : val(v) {}
	};

	node_t* front = nullptr;
	
public:

	void Add(const T& val)
	{
		node_t* newNode = new node_t(val);
		if (front == nullptr)
			front = newNode;
		else
		{
			newNode->next = front;
			front = newNode;
		}
	}

	bool isEmpty()
	{
		return front == nullptr;
	}

	T Top()
	{
		if (front != nullptr)
			return front->val;
		else
			return T();
	}

	void Pop()
	{
		if (front == nullptr)
			return;

		node_t* newfront = front->next;
		delete front;
		front = newfront;
	}

	virtual ~Stack()
	{
		while (!isEmpty())
			Pop();
	}
};

void TestStack()
{
	struct mytype_t
	{
		mytype_t() {}
		mytype_t(int)
		{
			cout << "Constructor" << endl;
		}
	};

	Stack<mytype_t*> st;
	st.Top();
	st.Add(new mytype_t(111));
	st.Add(new mytype_t(222));
	st.Add(new mytype_t(333));

}

extern "C"
void TestMyForEach();

extern "C"
void TestDblList();

extern "C"
int* GetSomeIDs();

extern "C"
void PrintAliases();


void TestContainers()
{
	typedef pair<int, string> mypair_t;
	typedef map<int, string> map_t;
	typedef vector<mypair_t> vec_t;

	map_t map;
	vec_t vec;

	auto vec_comp = [](mypair_t lhs, mypair_t rhs) { return lhs.first < rhs.first;  };
	
	for (int i = 1; i <= 10; i++)
	{
		if (i == 5)
			continue;

		mypair_t mp(i, "Value " + std::to_string(i));
		map.insert(mp);
		vec.push_back(mp);
	}

	map_t::iterator lit = map.lower_bound(2);
	map_t::iterator uit = map.upper_bound(2);

	lit = map.lower_bound(5);
	uit = map.upper_bound(5);

	lit = map.lower_bound(11);
	uit = map.upper_bound(11);

	//vec_t::iterator lit2 = lower_bound(vec.begin(), vec.end(), 2, vec_comp);
	//vec_t::iterator uit2 = upper_bound(vec.begin(), vec.end(), 2, vec_comp);

	//lit2 = lower_bound(vec.begin(), vec.end(), 5, vec_comp);
	//uit2 = upper_bound(vec.begin(), vec.end(), 5, vec_comp);

	//lit2 = lower_bound(vec.begin(), vec.end(), 11, vec_comp);
	//uit2 = upper_bound(vec.begin(), vec.end(), 11, vec_comp);

}

class Tree
{
	struct Node
	{
		int val = 0;
		Node* l = nullptr;
		Node* r = nullptr;
		Node(int v, Node* pl = nullptr, Node* pr = nullptr) : val(v), l(pl), r(pr) {}
	};

	Node* root = nullptr;

	void Add(Node** n, int v)
	{
		if (*n == nullptr)
			*n = new Node(v);

		else if (v < (*n)->val)
			Add(&(*n)->l, v);

		else
			Add(&(*n)->r, v);
	}

	bool IsExist(Node** n, int v)
	{
		if (*n == nullptr)
			return false;
		return false;
	}

public:

	void Add(int v)
	{
		Add(&root, v);
	}

	void Remove()
	{

	}

	bool IsExist(int v) const
	{

	}

	vector<int> GetAll() const
	{

	}
};

void TestTree()
{
	Tree tree;
	tree.Add(100);
	tree.Add(200);
	tree.Add(50);
	tree.Add(75);
	tree.Add(150);
	tree.Add(10);
	tree.Add(180);

}

class align
{

	int i1 = 0x11223344;
	int i2 = 0x55667788;
	unsigned char uc1 = 0xaa;
	unsigned char uc2 = 0xbb;
	int i3 = 0x10000001;
	unsigned char uc3 = 0xdd;
	int i5 = 0x20000002;
};

void TestRandom()
{
	random_device rd;
	knuth_b re(rd());
	uniform_int_distribution<int> dist(3, 4);

	for (int i = 0; i < 100; i++)
		cout << "\n " << i + 1 << ": " << dist(re);
}


class MyClass
{
	static mutex mtx;
	void ThreadFunc(int max, const char* str)
	{
		for (int i = 0; i < max; ++i)
		{
			{
				lock_guard<mutex> l(mtx);
				cout << endl << i << ": " << str;
			}
			std::chrono::milliseconds ms(1000);
			this_thread::sleep_for(ms);
		}
	}

	thread th; 
public:
	MyClass(int i, const char* str)
	{
		//th = thread(bind(&MyClass::ThreadFunc, this, i, str));
		th = thread([this, i, str]() { this->ThreadFunc(i, str);  });
	}

	~MyClass()
	{
		th.join();
	}
};

mutex MyClass::mtx;

void TestThread()
{
	MyClass mc1(10, "THread 1");
	MyClass mc2(5, "THread 2");
}

int main()
{
	TestThread();
    return 0;
}

