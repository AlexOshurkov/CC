#include "precomp.hpp"

using namespace std;

class bitset_t
{
	uint8_t*  _bitarr = nullptr;
	size_t _maxbits = 0;

public:

	bitset_t(size_t maxbits) : _maxbits(maxbits)
	{
		size_t size = maxbits / 8 + (maxbits % 8 ? 1 : 0);
		_bitarr = new uint8_t[size];
		std::memset(_bitarr, 0, size);
	}

	~bitset_t()
	{
		if (_bitarr != nullptr)
			delete[] _bitarr;
	}

	void set(size_t bit)
	{
		if (bit >= _maxbits)
			return;

		_bitarr[bit / 8] |= (1 << (bit % 8));
	}

	void reset(size_t bit)
	{
		if (bit >= _maxbits)
			return;

		_bitarr[bit / 8] &= ~(1 << (bit % 8));
	}

	bool get(size_t bit)
	{
		if (bit >= _maxbits)
			return false;

		return (_bitarr[bit / 8] & (1 << (bit % 8))) != 0;
	}
};

void TestArr()
{
}

set<string> SplitString(const string& str, const string& delim)
{
	regex rg(delim);
	sregex_token_iterator it(str.begin(), str.end(), rg, -1);
	return set<string>(it, sregex_token_iterator());
}

vector <string> missingWords(string s, string t)
{
	set<string> s1(SplitString(s, " "));
	set<string> s2(SplitString(t, " "));
	set<string> s3; //  missed words
	
	for (auto s : s1)
		if (s2.find(s) == s2.end())
			s3.insert(s);

	for (auto s : s2)
		if (s1.find(s) == s1.end())
			s3.insert(s);

	return vector<string>(s3.begin(), s3.end());
}

int findPairs(vector <int> nums, int k) 
{

	sort(nums.begin(), nums.end());
	nums.erase(unique(nums.begin(), nums.end()), nums.end());

	int cnt = 0;
	for (auto num : nums)
		if (binary_search(nums.begin(), nums.end(), num + k))
			++cnt;

	return cnt;
}

size_t FiboNum(size_t num)
{
	size_t a = 0;
	size_t b = 1;
	size_t i = 0;

	while (i++ < num)
	{
		size_t ta = a;
		a += b;
		b = ta;
	}

	return a;
}

void TestFibo()
{
	for (size_t i = 0; i <= 20; i++)
		cout << i << " = " << FiboNum(i) << endl;
};

template <typename T> 
class Queue
{
	struct Node
	{
		T val;
		Node* prev = nullptr;
		Node* next = nullptr;
	};

	Node* front = nullptr;
	Node* back = nullptr;

public:

	void PushBack(const T& val)
	{
		Node* pback = back;
		back = new Node();
		back->val = val;
		back->next = pback;

		if (pback != nullptr)
			pback->prev = back;

		if (front == nullptr)
			front = back;
	}

	const T* Back() const
	{
		return &back->val;
	}

	const T* Front() const
	{
		return &front->val;
	}

	void PopFont()
	{
		if (front == nullptr)
			return;

		Node* pfront = front;
		
		front = front->prev;

		if (front != nullptr)
			front->next = nullptr;

		if (back == pfront)
			back = nullptr;
		
		delete pfront;
	}
};

void TestQueue()
{
	Queue<int> q1;

	const int* f = nullptr;
	const int* l = nullptr;

	f = q1.Front();
	l = q1.Back();

	q1.PushBack(1);
	f = q1.Front();
	l = q1.Back();

	q1.PushBack(2);
	f = q1.Front();
	l = q1.Back();

	q1.PushBack(3);
	f = q1.Front();
	l = q1.Back();

	q1.PopFont();
	f = q1.Front();
	l = q1.Back();

	q1.PopFont();
	f = q1.Front();
	l = q1.Back();

	q1.PopFont();
	f = q1.Front();
	l = q1.Back();

	q1.PopFont();
	f = q1.Front();
	l = q1.Back();

	q1.PushBack(1);
	f = q1.Front();
	l = q1.Back();

	q1.PushBack(2);
	f = q1.Front();
	l = q1.Back();

	q1.PushBack(3);
	f = q1.Front();
	l = q1.Back();
}

typedef vector<size_t> MyVec;

MyVec GetRandomVec(size_t numElements)
{
	MyVec vec(numElements, 0);
	random_device rd;
	default_random_engine engine(rd());
	uniform_int_distribution<MyVec::value_type> dist(0, 1000);

	for_each(vec.begin(), vec.end(), [&dist, &engine](MyVec::value_type& x) { x = dist(engine);  });

	return vec;
}

void BubbleSort(MyVec& vec)
{
	bool isrun = true;
	while (isrun)
	{
		isrun = false;
		for (size_t i = 1; i < vec.size(); ++i)
			if (vec[i] < vec[i - 1])
			{
				swap(vec[i], vec[i - 1]);
				isrun = true;
			}
	}
}

void QuickSortImpl(MyVec& vec, size_t beg, size_t end);

void QuickSort(MyVec& vec)
{
	QuickSortImpl(vec, 0, vec.size() - 1);
}

void QuickSortImpl(MyVec& vec, size_t beg, size_t end)
{
	size_t b = beg;
	size_t e = end;
	size_t midval = vec[(b + e) / 2];

	while (b <= e)
	{
		while (vec[b] < midval)
			b++;

		while (vec[e] > midval)
			e--;

		if (b <= e)
		{
			swap(vec[b], vec[e]);
			b++;
			e--;
		}
	}

	if (beg < e)
		QuickSortImpl(vec, beg, e);

	if (b < end)
		QuickSortImpl(vec, b, end);
}

class Tree
{
public:

	class Node
	{
	public:

		Node(char v) : val(v) {}

		Node* l = nullptr;
		Node* r = nullptr;

		char val = 0;
	};	
	
	typedef vector<char> Elements;
	typedef pair<char, char> TwoEls;

	Node root;

	Tree(char val) : root(val) {}

	void AddElement(int val)
	{

	}

	bool IsExist(int v)
	{
		return false; 
	}

	bool CheckBST() const
	{
		return CheckBstImpl(&root);
	}

	bool CheckBstImpl(const Node* n) const
	{
		static const Node* prev = nullptr;

		if (n == nullptr)
			return true;

		if (!CheckBstImpl(n->l))
			return false;

		if (prev != nullptr && n->val <= prev->val)
			return false;
		
		prev = n;
		return CheckBstImpl(n->r);		
	}

	Elements GetByPreorder() const
	{
		Elements el;
		Preorder(el, &root);
		return el;
	}

	void Preorder(Elements& el, const Node* n) const
	{
		if (n == nullptr)
			return;

		el.push_back(n->val);

		Preorder(el, n->l);
		Preorder(el, n->r);
	}

	Elements GetByInorder() const
	{
		Elements el;
		Inorder(el, &root);
		return el;
	}

	void Inorder(Elements& el, const Node* n) const
	{
		if (n == nullptr)
			return;

		Inorder(el, n->l);
		el.push_back(n->val);
		Inorder(el, n->r);
	}

	Elements GetByPostorder() const
	{
		Elements el;
		Postorder(el, &root);
		return el;
	}

	void Postorder(Elements& el, const Node* n) const
	{
		if (n == nullptr)
			return;

		Postorder(el, n->l);
		Postorder(el, n->r);
		el.push_back(n->val);
	}

	void PreorderIter(Elements& el, const Node* n) const
	{

	}

	void InorderIter(Elements& el, const Node* n) const
	{
		stack<const Node*> st;

		while (!st.empty() || n != nullptr)
		{
			if (n == nullptr)
			{
				n = st.top();
				el.push_back(n->val); // eq. print
				n = n->r;
			}
			else
			{
				st.push(n);
				n = n->l;
			}
		}
	}

	void PostorderIter(Elements& el, const Node* n) const
	{

	}

	Elements GetByPreorderIter() const
	{
		Elements el;
		PreorderIter(el, &root);
		return el;
	}

	Elements GetByInorderIter() const
	{
		Elements el;
		InorderIter(el, &root);
		return el;
	}

	Elements GetByPostorderIter() const
	{
		Elements el;
		PostorderIter(el, &root);
		return el;
	}
};

void TestTree1()
{
	Tree tr('F');
	tr.root.l = new Tree::Node('B');
	tr.root.r = new Tree::Node('G');

	tr.root.l->l = new Tree::Node('A');
	tr.root.l->r = new Tree::Node('D');

	tr.root.l->r->l = new Tree::Node('C');
	tr.root.l->r->r = new Tree::Node('E');

	tr.root.r->r = new Tree::Node('I');
	tr.root.r->r->l = new Tree::Node('H');

	Tree::Elements elements1 = tr.GetByPreorder();
	Tree::Elements elements2 = tr.GetByInorder();
	Tree::Elements elements3 = tr.GetByPostorder();

	Tree::Elements elements4 = tr.GetByPreorderIter();
	Tree::Elements elements5 = tr.GetByInorderIter();
	Tree::Elements elements6 = tr.GetByPostorderIter();

	bool bst_check = tr.CheckBST();

};

/*
Task description

A zero - indexed array A consisting of N integers is given.An equilibrium index of this array 
is any integer P such that 0 ≤ P < N and the sum of elements of lower indices is equal to the 
sum of elements of higher indices, i.e.
	A[0] + A[1] + ... + A[P−1] = A[P + 1] + ... + A[N−2] + A[N−1].
	Sum of zero elements is assumed to be equal to 0. This can happen if P = 0 or if P = N−1.

	For example, consider the following array A consisting of N = 8 elements:

	A[0] = -1
	A[1] = 3
	A[2] = -4
	A[3] = 5
	A[4] = 1
	A[5] = -6
	A[6] = 2
	A[7] = 1
	P = 1 is an equilibrium index of this array, because:

	A[0] = −1 = A[2] + A[3] + A[4] + A[5] + A[6] + A[7]
	P = 3 is an equilibrium index of this array, because :

	A[0] + A[1] + A[2] = −2 = A[4] + A[5] + A[6] + A[7]
	P = 7 is also an equilibrium index, because :

	A[0] + A[1] + A[2] + A[3] + A[4] + A[5] + A[6] = 0
	and there are no elements with indices greater than 7.

	P = 8 is not an equilibrium index, because it does not fulfill the condition 0 ≤ P < N.

	Write a function :

int solution(vector<int> &A);
that, given a zero - indexed array A consisting of N integers, returns any of its equilibrium 
indices.The function should return −1 if no equilibrium index exists.

For example, given array A shown above, the function may return 1, 3 or 7, as explained above.

Assume that :

N is an integer within the range[0..100, 000];
each element of array A is an integer within the range[−2, 147, 483, 648..2, 147, 483, 647].
Complexity:

expected worst - case time complexity is O(N);
expected worst - case space complexity is O(N), beyond input storage(not counting the storage required 
for input arguments).
Elements of input arrays can be modified.
*/
int DemoTest(vector<int> A)
{
	vector<int64_t> a1;
	vector<int64_t> a2;
	int64_t sum1 = 0;
	int64_t sum2 = 0;

	vector<int>::const_reverse_iterator it = A.rbegin();

	for (auto n : A)
	{
		sum1 += n;
		sum2 += *it;
		++it;
		a1.push_back(sum1);
		a2.push_back(sum2);
	}

	reverse(a2.begin(), a2.end());
	const size_t size = a1.size();
	for (size_t i = 0; i < size; i++)
		if (a1[i] == a2[i])
			return static_cast<int>(i);

	return -1;
}

void ReverseVec(vector<int>& vec)
{
	if (vec.empty())
		return;

	vector<int>::iterator beg = vec.begin();
	vector<int>::iterator end = --vec.end();

	while (beg < end)
	{
		swap(*beg, *end);
		++beg;
		--end;
	}
}


int main1() {
	return 0;
}