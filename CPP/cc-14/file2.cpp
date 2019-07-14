#include "precomp.hpp"

using namespace std;


vector<int> GetRandomVector1(int size)
{
	vector<int> vec(size, 0);
	random_device rd;
	default_random_engine eng(rd());
	uniform_int_distribution<int> distr(1, size);

	for (int& v : vec)
		v = distr(eng);

	return vec;
}

vector<int> GetRandomVector2(int size)
{
	vector<int> vec(size, 0);

	int i = 0;
	for (int& v : vec)
		v = ++i;

	random_device rd;
	default_random_engine eng(rd());
	shuffle(vec.begin(), vec.end(), eng);

	return vec;
}

void QuickSort1Impl(vector<int>& vec, int beg, int end)
{
	int mval = vec[(beg + end) / 2];
	int b = beg;
	int e = end;

	while (b <= e)
	{
		while (vec[b] < mval)
			++b;

		while (vec[e] > mval)
			--e;

		if (b <= e) {
			swap(vec[b], vec[e]);
			++b;
			--e;
		}
	}

	if (beg < e)
		QuickSort1Impl(vec, beg, e);

	if (b < end)
		QuickSort1Impl(vec, b, end);
}

void QuickSort1(vector<int>& vec)
{
	if (vec.empty())
		return;

	QuickSort1Impl(vec, 0, vec.size() - 1);
}

void BubbleSort(vector<int>& vec) {
	
	if (vec.empty())
		return;

	bool is_unsorted = true;

	while (is_unsorted) {
		is_unsorted = false;
		vector<int>::iterator it1 = vec.begin();
		vector<int>::iterator it2 = it1 + 1;

		for (; it2 != vec.end(); ++it1, ++it2)
			if (*it1 > *it2) {
				swap(*it1, *it2);
				is_unsorted = true;
			}
	}
}

void TestBubbleSort() {
	for (int i = 0; i < 100; ++i) {
		vector<int> v1;
		vector<int> v2 = vector<int>(1, 0);
		vector<int> v3 = GetRandomVector1(2);
		vector<int> v4 = GetRandomVector1(1000);

		BubbleSort(v1);
		BubbleSort(v2);
		BubbleSort(v3);
		BubbleSort(v4);

		bool b1 = is_sorted(v1.begin(), v1.end());
		bool b2 = is_sorted(v2.begin(), v2.end());
		bool b3 = is_sorted(v3.begin(), v3.end());
		bool b4 = is_sorted(v4.begin(), v4.end());

		if (b1 && b2 && b3 && b4)
			continue;
		else
			throw exception("Sorting failed!!!!!");

	}
}

void TestQuickSort()
{
	for (int i = 0; i < 100; ++i)
	{
		vector<int> v1;
		vector<int> v2 = vector<int>(1, 0);

		vector<int> v3 = GetRandomVector1(2);
		vector<int> v4 = GetRandomVector2(1000);
		vector<int> v5 = GetRandomVector2(10000);

		QuickSort1(v3);
		QuickSort1(v4);
		QuickSort1(v5);

		bool b1 = is_sorted(v3.begin(), v3.end());
		bool b2 = is_sorted(v4.begin(), v4.end());
		bool b3 = is_sorted(v5.begin(), v5.end());

		if (b1 && b2 && b3)
			continue;
		else
			throw exception("Sorting failed!!!!!");

	}
}

struct Item
{
	int val;
	Item* next = nullptr;
	Item(int v, Item* n) : val(v), next(n) {}
};

Item* ReverseList(Item* it)
{
	Item* pit = nullptr;

	while (it != nullptr)
	{
		Item* nit = it->next;
		it->next = pit;
		pit = it;
		it = nit;
	}

	return pit;
}

Item* ReverseListRecImpl(Item* it, Item* pit)
{
	if (it == nullptr)
		return pit;
	else
	{
		Item* nit = it->next;
		it->next = pit;
		pit = it;
		it = nit;
	}

	return ReverseListRecImpl(it, pit);
}

Item* ReverseListRec(Item* it)
{
	return ReverseListRecImpl(it, nullptr);
}

void TestReverseList()
{
	Item it ( 1, new Item(2, new Item(3, nullptr)));
	Item* rit = ReverseListRec(&it);
}

int main2()
{
	TestReverseList();
	return 0;
}
