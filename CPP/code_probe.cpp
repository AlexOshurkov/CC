#include "stdafx.h"
#pragma hdrstop

using namespace std;
using namespace placeholders;


vector<float> ReadVals(const string& fname)
{
	ifstream inp(fname);
	vector<float> vals;
	vals.assign(istream_iterator<float>(inp), istream_iterator<float>());
	return vals;
}

typedef pair<string, string> MyPair;

vector<MyPair> ReadPairs(const string& fname)
{
	ifstream inp(fname);
	
	vector<MyPair> vals;
	string key;
	string val;

	vector<string> str;
	while (!inp.eof())
	{
		inp >> key;
		inp >> val;
		vals.push_back(MyPair(key, val));
	}

	return vals;
}

void WriteVals(const string& fname, const vector<float>& vals)
{
	ofstream out(fname);
	for (auto val : vals)
		out << val << "\n";
}

void StreamTest()
{
	vector<string> vals(SplitString("+12 -323 2.34;\n546\n;abc\ndef", "[\n][0-9]+[\n]"));

}

class FNTest
{
	vector<int> vals;

public:
	void AddVal(int v)
	{
		vals.push_back(v);
	}
};

void FunctionTest()
{
	FNTest fnt; 
	vector<int> vals{ 1, 2, 3 };
	function<void(int)> f1 = bind(&FNTest::AddVal, ref(fnt), _1);
	for_each(vals.begin(), vals.end(), f1);
}


uint64_t Fibonacci(uint64_t max)
{
	uint64_t a = 0;
	uint64_t b = 1;
	int pass = 0;

	while (pass++ < max)
	{
		uint64_t t = a + b; 
		a = b;		
		b = t;
	}

	return a;
}

bool IsLEndian()
{
	unsigned short ival = 0x1234;
	return *(char*)&ival == 0x34 ;
}

string GenRandomString(size_t strLen)
{
	string str(strLen, ' ');
	random_device rnddev;
	default_random_engine rndeng(rnddev());
	uniform_int_distribution<unsigned int> rnddist('A', 'Z');

	for (auto& ch : str)
		ch = rnddist(rndeng);
	 
	return str;
}

void GenFileWithRandomStrings(const char* fname, size_t strLen, size_t strNum)
{
	ofstream f(fname, ios_base::app);
	ostream_iterator<string> it(f);

	for (size_t j = 0; j < strNum; j++)
	{
		string line;
		line.reserve(strLen * 1000000 + 1000000);
		for (size_t i = 0; i < 1000000; ++i)
		{
			line += GenRandomString(strLen);
			line += "\n";
		}

		*it = line;
	}
}

bool BucketSort(const char* srcFname, const char* dstFname, size_t numLines)
{
	std::remove(dstFname);
	ifstream finp(srcFname);
	ofstream fout(dstFname, ios_base::app);
	istream_iterator<string> itinp(finp);
	ostream_iterator<string> itout(fout);

	if (finp.fail())
		return false;

	size_t buckets = 0;
	

//	Sort within buckets
	while (!finp.eof())
	{
		vector<string> lines; 
		lines.reserve(numLines);
		
		for (size_t i = 0; i < numLines && !finp.eof(); i++, ++itinp)
			lines.push_back(*itinp);

		if (lines.empty())
			break;

		static size_t linelen = lines[0].size() + 1;

		sort(lines.begin(), lines.end());
		string line;
		line.reserve(numLines * linelen);
		for (auto str : lines)
		{
			line += str;
			line += '\n';
		}

		buckets++;
		*itout = line;
	}

	cout << "buckets: " << buckets;
	return true;
}
