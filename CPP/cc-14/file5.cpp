#include "precomp.hpp"

using namespace std;

#pragma warning (disable:4455)

void TestString() {

	wstring ws1(L"1qwerty"s);
	int i = ws1[0] - '0';
	int d1 = ws1.length();
	int d2 = ws1.size();
	int dummy = 0;
}

	class myclass {
		int i = 0;
	public:

		myclass(int v) : i(v) {}
		myclass operator+ (const myclass& v1) {
			return i + v1.i;
		}

		friend myclass operator-(const myclass& v1, const myclass& v2);
		int getval() const { return i; }
	};

	myclass operator-(const myclass& v1, const myclass& v2) {
		return v1.i - v2.i;
	};

	myclass operator""mc(const char* p, size_t len) {
		return myclass(std::stoi(p));
	}

	
void TestClasses() {

	myclass c1(10);
	myclass c2(20);
	auto c3 = c2 - c1;
	auto c4 = "123"mc.getval();

}

uint32_t CreateHash(const string& str)
{
	if (str.empty())
		return 0;

	uint32_t res = 0;

	for (auto ch : str)
		res ^= (res << 1) ^ ch;

	return res;
}

void TestHash()
{
	vector<uint32_t> test;
	test.push_back(CreateHash(""));
	test.push_back(CreateHash("1"));
	test.push_back(CreateHash("2"));
	test.push_back(CreateHash("2"));
	test.push_back(CreateHash("abc"));
	test.push_back(CreateHash("acb"));
	test.push_back(CreateHash("cba"));
	test.push_back(CreateHash("jk234-089isdvbt678sadfg8o23f79gb78gf6278913f2391456c 3874905786ocf378 4"));
	test.push_back(CreateHash("jk234-089isdvbt678sadfg8o23f79gb78gf6278931f2391456c 3874905786ocf378 4"));
	test.push_back(CreateHash("jk234-089isdvbt678sadfg8o23f79gb78gf6278913f2391456c 3874905786ocf378 "));
	test.push_back(CreateHash("jk334-089isdvbt678sadfg8o23f79gb78gf6278913f2391456c 3874905786ocf378 4"));



}

void finalPrice(const vector<int>& vals)
{
	const size_t size = vals.size();
	vector<int> d(size, 0);  // discounts
	stack<size_t> savedpr;  // stack for big prices

	size_t i = 0;  // pos for array
	
	for (i = 0; i < size; ++i)
	{
		while (!savedpr.empty() && vals[savedpr.top()] >= vals[i])
		{
			d[savedpr.top()] = vals[i];
			savedpr.pop();
		}

		savedpr.push(i);
	}

	int sum = 0;
	stringstream ss;

	for (i = 0; i < size; ++i)
	{
		sum += vals[i] - d[i];

		if (d[i] == 0)
			ss << i << " ";
	}

	cout << sum << endl;
	cout << ss.str() << endl;

}


int verifyItems(vector < string > origItems, 
	vector < float > origPrices, 
	vector < string > items, 
	vector < float > prices) {

	if (origItems.size() != origPrices.size() || items.size() != prices.size())
		return 0;

	map<string, float> orig_map;
	vector<string>::const_iterator it_orig_items  = origItems.begin();
	vector<float>::const_iterator  it_orig_prices = origPrices.begin();

	for (; it_orig_items != origItems.end();)
	{
		orig_map[*it_orig_items] = *it_orig_prices;
		++it_orig_items;
		++it_orig_prices;
	}
	
	vector<string>::const_iterator it_items = items.begin();
	vector<float>::const_iterator  it_prices = prices.begin();
	int cnt = 0;  // counter for Alex's "mistakes"

	for (; it_items != items.end();)
	{
		if (orig_map[*it_items] != *it_prices)
			++cnt;

		++it_items;
		++it_prices;
	}

	return cnt;

}

#pragma 
struct foo1
{
	char c1[5];
	int i;
};

struct foo2
{
	char c1[9];
};

struct foo3
{
	foo1 f1;
	foo2 f2;
};

