#include "precomp.hpp"

using namespace std;

struct Node
{
	int val = 0;
	Node* next = nullptr;

	Node(int v) : val(v) {}
};

void DelHead(Node*& head)
{
	if (head == nullptr)
		return;

	Node* new_head = head->next;
	delete head;
	head = new_head;
}

void TestDelHead()
{
	Node* n1 = new Node(1);
	n1->next = new Node(2);
	n1->next->next = new Node(3);

	DelHead(n1);
	DelHead(n1);
	DelHead(n1);
}

void TestBounds()
{
	map<int, string> m;
	set<int> s;

	m[10] = "10";
	m[20] = "20";
	m[30] = "30";

	s.insert(10);
	s.insert(20);
	s.insert(30);

	map<int, string>::const_iterator low_map = m.lower_bound(30);
	map<int, string>::const_iterator upp_map = m.upper_bound(30);

	set<int>::const_iterator low_set = s.lower_bound(30);
	set<int>::const_iterator upp_set = s.upper_bound(30);
	;
}

typedef vector<size_t> MyVec;

MyVec GetRandomVec(size_t numElements);

void TestSort()
{
	MyVec vec = GetRandomVec(10);
	MyVec vec2{} ;

	sort(vec.begin(), vec.end(), less<size_t>());
	MyVec::difference_type cnt = count_if(vec.begin(), vec.end(), bind1st((less<size_t>()), 300));

	bool res = none_of(vec.begin(), vec.end(), bind2nd((greater<size_t>()), 1000));
	copy(vec.begin(), vec.end(), vec2.begin());
}

struct MyList
{
	vector<int> vec;
	list<double> list;

	MyList() = default;
	explicit MyList(initializer_list<int> vec_, initializer_list<double> list_)
	{
		vec.insert(vec.end(), vec_.begin(), vec_.end());
		list.insert(list.end(), list_.begin(), list_.end());
	}
	explicit MyList(initializer_list<int> vec_)
	{
		vec.insert(vec.end(), vec_.begin(), vec_.end());
	}

	explicit MyList(initializer_list<double> list_)
	{
		list.insert(list.end(), list_.begin(), list_.end());
	}
};

class MyClass
{
	int i;
	float f;
public:

	MyClass() = default;
	MyClass(int i_, float f_) : i(i_), f(f_) {}
};

class MyClass2 : public MyClass
{
	using MyClass::MyClass;
};

void TestInitializersList()
{
	MyList l1;
	MyList l2 {  1,2,3 };
	MyList l3{  1.1,2.2,3.3  };

	MyClass2 mc1;
    MyClass2 mc2{ 1, 2.2f };
	MyClass2 mc3{ 1, 3.3f };

}

vector<int> merge(const vector<int>& v1, const vector<int>& v2)
{
	vector<int>::const_iterator it1 = v1.begin();
	vector<int>::const_iterator it2 = v2.begin();
	vector<int> res;

	while (it1 != v1.end() && it2 != v2.end())
	{
		if (*it1 < *it2)
		{
			res.push_back(*it1);
			++it1;
		}
		else
		{
			res.push_back(*it2);
			++it2;
		}
	}

	for (; it1 != v1.end(); ++it1)
		res.push_back(*it1);

	for (; it2 != v2.end(); ++it2)
		res.push_back(*it2);

	return res;
}

//-------------------------------------------------------------------------
template <typename T>
vector<T> str_to_vec(const string& str)
{
	stringstream ss{ str };
	istream_iterator<int> beg{ ss };
	istream_iterator<int> end;
	return vector<T> { beg, end };
}

vector<int> SortVectors(list<string> inplines)
{
	vector<int> res;
	list<string>::const_iterator it = inplines.begin();

	while (it != inplines.end())
	{
		res = merge(res, str_to_vec<int>(*it));
		++it;
	}

	return res;
}

void TestSortVectors()
{
	vector<int> v1{ SortVectors({}) };
	vector<int> v2{ SortVectors({""}) };
	vector<int> v3{ SortVectors({ "","" }) };
	vector<int> v4{ SortVectors({ "3","1" }) };
	vector<int> v5{ SortVectors({ "1" }) };
	vector<int> v6{ SortVectors({ "","1" }) };
	vector<int> v7{ SortVectors({ "3","" }) };
	vector<int> v8{ SortVectors({ "3 5 7 8 9","1 11 22 33" }) };
	vector<int> v9{ SortVectors({ "3 5 7 8 9","1 11 22 33", "3 12 17 21" }) };
}

int main7(int, char**)
{
	return 0;
}