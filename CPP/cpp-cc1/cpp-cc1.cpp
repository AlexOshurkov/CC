// cpp-cc1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;

void FizzBuzz(uint16_t beg, uint16_t end)
{
	for (uint16_t i = beg; i <= end; i++)
	{
		cout.width(3);
		cout << i << ": ";
		if (i % 3 == 0)
			cout << "Fizz";
		if (i % 5 == 0)
			cout << "Buzz";
		cout << endl;
	}
}

long getdist(long* rgb1, long* rgb2)
{
	long r = rgb1[0] - rgb2[0];
	long g = rgb1[1] - rgb2[1];
	long b = rgb1[2] - rgb2[2];

	return r * r + g * g + b * b;
}

const char* testcolor(const char* bits)
{
	long rgb[] = { 0, 0, 0 };
	long drgb[][3] = { { 255, 0, 0 }, { 0, 255, 0 }, { 0, 0, 255 } };
	const char* ans[] = { "Red", "Green", "Blue" };

//	Getting RGB values
	for (int i = 0; i < 24; i++)
	{
		int col = i / 8;
		rgb[col] <<= 1;
		rgb[col] += bits[i] == '1' ? 1 : 0;
	}

	unordered_set<long> dist;
	long mindist = 0;
	int mindistpos = -1;


//	Checking distance
	for (int j = 0; j < 3; j++)
	{
		long distval = getdist(drgb[j], rgb);

		if (dist.find(distval) == dist.end())
		{
			dist.insert(distval);

			if (distval < mindist || mindistpos == -1)
			{
				mindist = distval;
				mindistpos = j;
			}
		}
		else
			return "Ambigous";
	}
	
	return ans[mindistpos];
}

int maxdiff(vector<int> v)
{
	if (v.empty())
		return -1;

	int lvmin = 0;
	int nvmin = 0;
	int lvmax = 0;

	for (unsigned int i = 0; i < v.size(); i++)
	{
		if (v[i] > v[lvmax])
		{
			lvmax = i;
			lvmin = nvmin;
		}

		else if (v[i] < v[nvmin])
			nvmin = i;
	}

	return lvmax > lvmin ? v[lvmax] - v[lvmin] : -1;
}

struct list_t
{
	list_t* pnext = 0;
	int val = 0;

	list_t(list_t* next, int value) : pnext(next), val(value) {}
};

void reverse_list(list_t** list)
{
	list_t* root = *list;
	list_t* prev = nullptr;

	while (root)
	{ 
		list_t* curr = root;
		list_t* pnext = root->pnext;
		curr->pnext = prev;
		prev = curr;
		root = pnext;
	}

	*list = prev;
}

char UpperChar(char ch)
{
	return ch >= 'a' && ch <= 'z' ? ch - ('a' - 'A') : ch;
}

void UpperStr(char* str)
{
	while (*str)
	{
		*str = UpperChar(*str);
		str++;
	}
}

bool IsPangram(char* str)
{
	UpperStr(str);
	char flags[26];
	int sumuniq = 0;
	memset(flags, 0, sizeof(flags[0]) * sizeof(flags));


	while (*str)
	{
		char curpos = *str - 'A';

		if (*str < 'A' || flags[curpos])
			;
		else
		{
			flags[curpos] = 1;
			sumuniq++;

			if (sumuniq == 26)
				return true;
		}
		str++;
	}

	return sumuniq >= 26;
}



bool IsFunnyStr(const string& str)
{
	if (str.size() < 2)
		return false;

	string::const_iterator         it1 = str.begin();
	string::const_reverse_iterator it2 = str.rbegin();
	int sum = 0;

	do
	{
		char ch1 = *it1;
		char ch2 = *it2;

		it1++;
		it2++;

		if (it1 != str.end())
			if (abs(*it1 - ch1) == abs(*it2 - ch2))
				sum++;

	} while (it1 != str.end());

	return str.size() == sum + 1;
}

string TimeConv(const string& str)
{
	bool isam = *(str.rbegin() + 1) == 'A';
	int hh = stoi(str.substr(0, 2));

	if (isam && hh == 12)
		hh = 0;
	else if (!isam && hh < 12)
		hh += 12;

	string ret = (hh < 10 ? "0" : "") + to_string(hh) + str.substr(2);
	return ret.substr(0, str.size() - 2);
}

int DiagDiff(const vector<vector<int>>& arr)
{
	const size_t size = arr.size();
	int retval = 0;

	for (size_t i = 0; i < size; i++)
		retval += arr[i][i] - arr[size - i - 1][i];

	return retval;
}

pair<float, float> GetPlusMinus(const vector<int>& arr)
{
	float pcnt = 0;
	float ncnt = 0;

	for (int v : arr)
	{
		if (v > 0)
			pcnt++;

		else if (v < 0)
			ncnt++;
	}

	return pair<float, float>(pcnt / arr.size(), ncnt / arr.size());
}

void PrintStairs(size_t height)
{
	for (size_t i = 1; i <= height; i++)
		cout << string(height - i, ' ') << string(i, '#') << endl;
}

int NumDeletes(const string& str)
{
	if (str.empty())
		return 0;

	auto it = str.cbegin();
	auto prevch = *it++;
	auto numdel = 0;


	for (; it != str.cend(); it++)
		if (*it == prevch)
			numdel++;
		else
			prevch = *it;

	return numdel;
}

int GetPairs(vector<size_t> arr, size_t k)
{
	if (arr.empty())
		return 0;

	int ans = 0;
	sort(begin(arr), end(arr));

	const size_t size = arr.size();

	for (size_t i = 0; i < size - 1; i++)
	{
		for (size_t j = i + 1; j < size; j++)
		{
			if (arr[j] > arr[i] + k)
				break;
			else if (arr[j] == arr[i] + k)
			{
				ans++;
				break;
			}
		}
	}


	return ans;
}

int GetPairs2(vector<int> arr, int k)
{
	if (arr.empty())
		return 0;

	int ans = 0;
	unordered_set<int> us;

	for (auto val : arr)
	{
		if (us.find(val - k) != us.end())
			ans++;

		if (us.find(val + k) != us.end())
			ans++;

		us.insert(val);
	}

	return ans;
}

bitset<32> CheckChars(const string& str)
{
	bitset<32> bs;
	for (unsigned char ch : str)
		bs.set(ch - 'a');

	return bs;
}

bool IsTwoStrings(const string& str1, const string& str2)
{
	bitset<32> bs1 = CheckChars(str1);
	bitset<32> bs2 = CheckChars(str2);

	for (size_t i = 0; i < bs1.size(); i++)
		if (bs1.test(i) && bs2.test(i))
			return true;

	return false;
}

class EncloseChecker 
{
	vector<pair<char, char>> _br;  //  enclosing chars (ex. braces)
	stack <char>             _brs; // 

	bool IsLeftBr(char ch)
	{
		for (auto v : _br)
			if (v.first == ch)
				return true;

		return false;
	}

	bool IsRightBr(char ch)
	{
		for (auto v : _br)
			if (v.second == ch)
				return true;

		return false;
	}

	bool IsPair(char ch1, char ch2)
	{
		for (auto v : _br)
			if (v.first == ch1 && v.second == ch2)
				return true;				

		return false;
	}

public:
	EncloseChecker()
	{
		_br = { { '(', ')' }, { '[', ']' }, { '{', '}' }, { '<', '>' } };
	}

	EncloseChecker(vector<pair<char, char>> br) : _br(br) {};

	bool Check(const string& str)
	{
		for (auto ch : str)
			if (IsLeftBr(ch))
				_brs.push(ch);

			else if (IsRightBr(ch))
			{
				if (_brs.empty())
					return false;

				else if (IsPair(_brs.top(), ch))
					_brs.pop();

				else
					return false;
			}

		return _brs.empty();
	}
};

struct TNode
{
	int val = 0;

	TNode* ln = nullptr;
	TNode* rn = nullptr;
};

bool CheckBst(const TNode& node)
{
	return (node.ln == nullptr ? true : CheckBst(*node.ln) && node.val >= node.ln->val) &&
		   (node.rn == nullptr ? true : CheckBst(*node.rn) && node.val < node.rn->val);

};

int _tmain(int argc, _TCHAR* argv[])
{
	{ //  braces
		string s1 = "(<(<(<>)>]>)";
		string s2 = "<{([<{([<([<{([<{([])}>])}>])}>])}>])}>";

		string s3 = "({}}";

		bool b1 = EncloseChecker().Check(s1);
		bool b2 = EncloseChecker().Check(s2);
		bool b3 = EncloseChecker().Check(s3);
	}

	{ //	BST
		TNode root;
		bool chb = CheckBst(root);
		int t = chb;
	}

	int n;
	cin >> n;
	for (int i = 0; i < n; i++) 
	{
		string str1, str2;
		cin >> str1 >> str2;
		cout << (IsTwoStrings(str1, str2) ? "YES" : "NO") << endl;
	}

	
	return 0;
	// old tests
	const char* ans = testcolor("000000000000001000000011");
	
	vector<int> v1 = { 1,2,3,4,5};
	int ans2 = maxdiff(v1);
	ifstream inpfile("c:\\file2.dat");

    map <string, int> m1;

	while (true)
	{
		string line;

		getline(inpfile, line);

		if (inpfile.fail())
			break;
		else
		{
			line.erase(remove(line.begin(), line.end(), ' '), line.end());
		}
	}

	// FizzBuzz(1, 100);

	list_t* root = new list_t(0, 1);
	list_t* list = root;

	for (int i = 2; i <= 10; i++)
	{
		list->pnext = new list_t(0, i);
		list = list->pnext;
	}

	reverse_list(&root);


	return 0;
}

