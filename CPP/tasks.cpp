#include "stdafx.h"
#pragma hdrstop

size_t StrLen(const char* pstr)
{
	const char* beg = pstr;
	while (*pstr)
		pstr++;

	return pstr - beg;
}

void TestStrLen()
{
	size_t len1 = StrLen("");
	size_t len2 = StrLen("1");
	size_t len3 = StrLen("1234567890");
}

void RegexpTest()
{
	vector<string> svals = { "+", "-", "", "12", "-12", "+12", ".12", "-.12", "+.12", "0.12", "-0.12", "+0.12", "1.2", "-1.2", "+1.2", 
		"1.", "-1.", "+1."};

	vector<pair<string, bool>> vals;
	for_each(svals.begin(), svals.end(), 
		[&vals](const string& val) 
		{	
			vals.push_back(pair<string, bool>(val, regex_match(val, regex("^[+-]?[0-9]*[.]?[0-9]+$"))));
		} );

}

int cnt = 0;

void task(int id)
{
	cout << "\nStart task: " << id;
	for (size_t i = 0; i < 1000000; i++)
	{
		++cnt;
		--cnt;
	}
	cout << "\nEnd task: " << id;
}

void ThreadTest()
{
	cout << "\nStart threads, cnt: " << cnt;

	const size_t numth = 50;
	vector<thread> threads;

	for (size_t i = 0; i < numth; i++)
		threads.push_back(thread(task, i + 1));

	for (size_t i = 0; i < numth; i++)
		threads[i].join();

	cout << "\nEdn threads, cnt: " << cnt;

}

template<typename T>
T myatoi(const char* str, const char** err = nullptr)
{
	if (str == nullptr || *str == 0)
	{
		if (err != nullptr)
			*err = "Empty or null string";

		return 0;
	}

	T    res = 0;
	bool neg = false;
	const char* p = str;

	while (*p > 0)
	{
		if (neg == false && p == str && *p == '-')
			neg = true;

		else if (*p >= '0' && *p <= '9')
		{
			T prev = res;
			res = res * 10 + (neg ? '0' - *p : *p - '0');

			if (neg)
			{
				if (err != nullptr && res > prev)
				{
					*err = "Negative overflow";
					return res;
				}
			}
			else
				if (err != nullptr && res < prev)
				{
					*err = "Positive overflow";
					return res;
				}
		}

		else
		{
			if (err != nullptr)
				*err = "Wrong character found";
			return res;
		}

		++p;
	}

	if (err != nullptr)
		*err = "";

	return res;
}

void TestMyAtoi()
{
	vector<string> nums{ "", "0", "1", "123", "001", "0010", "1000", "-123", "1-2", "12sdf234.345", "23784627834678234", "-23894298734981" };
	nums.push_back("------------");
	nums.push_back(to_string(numeric_limits<int32_t>::min()));
	nums.push_back(to_string(numeric_limits<int32_t>::max()));
	nums.push_back(to_string(numeric_limits<uint32_t>::min()));
	nums.push_back(to_string(numeric_limits<uint32_t>::max()));
	nums.push_back(to_string(numeric_limits<int64_t>::min()));
	nums.push_back(to_string(numeric_limits<int64_t>::max()));
	nums.push_back(to_string(numeric_limits<uint64_t>::min()));
	nums.push_back(to_string(numeric_limits<uint64_t>::max()));

	for (auto str : nums)
	{
		const char* err = nullptr;
		uint64_t res = myatoi<uint64_t>(str.c_str(), &err);
		cout << "\n" << str << " --> " << res << " " << (err == nullptr ? "" : err);
	}
}

class TaskClass
{
	int n = 0;
	thread th;
	mutex& mx;

public:

	TaskClass(mutex& mxv, int nv, int i) : mx(mxv), n(nv)
	{
		th = thread(bind(&TaskClass::Task, this, i));
	}

	void Task(int i)
	{
		for (int j = i; j <= i * i; j++)
		{
			lock_guard<mutex> lock(mx);
			cout << endl << n << ". " << "j = " << j;
		}
	}

	~TaskClass()
	{
		th.join();
	}

};

void TestTask()
{
	mutex mx;
	TaskClass tc1(mx, 1, 50);
	TaskClass tc2(mx, 2, 90);
}

void StringTest()
{
	char* str1 = "qwerty";
	wchar_t* wstr1 = L"qwerty";
	uint8_t pwstr[20];
	memcpy(pwstr, wstr1, sizeof(pwstr));
	wstring wstr(wstr1);

	wcout << "\nwstr: " << wchar_t('A');

	size_t wsize = wstr.size();
	for (size_t i = 0; i < wsize; ++i)
		wcout << wchar_t(towupper(wstr[i]));
}

void HashTablesTest()
{
	struct MyVal;
	typedef unordered_map<string, MyVal> mymap_t;
	typedef unordered_map<mymap_t, int> mp2_t;

	struct MyVal {
		int val; 
	};

	mymap_t um1;
	//mp2_t um2;
	mymap_t::hasher hf = um1.hash_function();
	size_t hval = hf("val1");
	um1.insert(mymap_t::value_type("val1", MyVal{ 1 }));
	um1.insert(mymap_t::value_type("val2", MyVal{ 2 }));
	um1.insert(mymap_t::value_type("val3", MyVal{ 3 }));

	um1["val4"].val = 4;
}

void PrintFibo(size_t num)
{
	size_t a = 0;
	size_t b = 1;

	for (size_t i = 0; i <= num; ++i)
	{
		cout << i << ": " << a << endl;
		size_t t = a;
		a += b;
		b = t;
	}
}

typedef std::chrono::time_point<std::chrono::system_clock> mytime_t;
double ClockAngle(mytime_t ct)
{
	double ahm = numeric_limits<double>::signaling_NaN();
	time_t tmt = system_clock::to_time_t(ct);
	return ahm;
}

int wmtest(vector<int> ar)
{
	if (ar.empty())
		return 0;

	size_t size = ar.size();
	int curscor = 1;
	int oldval = 0;
	int cursum = 0;

	cout << "curscor: ";
	for (size_t i = 0; i < size; i++)
	{
		if (i > 0 && ar[i] > oldval)
			curscor++;
		else
			curscor = 1;

		oldval = ar[i];
		cursum += curscor;
		cout << curscor << ", ";
	}

	return cursum;
}

int main(int argc, char* argv[])
{
	//ClockAngle(system_clock::now());
	vector<int> ar{2, 4, 2, 6, 1, 7, 8, 9, 2, 1}; 
	int i1 = wmtest(ar);
	cout << i1;
	string t;
	cin >> t;
	return 0;
}

