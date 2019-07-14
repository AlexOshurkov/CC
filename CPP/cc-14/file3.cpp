#include "precomp.hpp"

using namespace std;

struct wrap_str {
	char* res = nullptr;

	wrap_str(const char* beg, unsigned int len) {
		res = new char[len + 1];
		memset(res, 0, len + 1);
		memcpy(res, beg, len);
	}

	operator const char* const () {
		return res;
	}

	~wrap_str() {
		delete[] res;
	}
};

wrap_str LongestWord(const char* str) {
	const char* beg = 0;
	const char* end = str;
	const char* mbeg = 0;
	unsigned int max = 0;

	while (end && *end) {

		if (*end == ' ')
			beg = 0;
		else
		{
			if (beg == 0)
				beg = end;

			if (end - beg + 1u > max) {
				max = end - beg + 1;
				mbeg = beg;
			}
		}
		++end;
	}

	return wrap_str(mbeg, max);
}

string LongestWordStd(const string& str) 
{
	string res;
	string::const_iterator mit = str.end();
	string::const_iterator it1 = str.end();
	string::const_iterator it2 = str.begin();
	size_t max = 0;

	while (it2 != str.end()) {
		if (*it2 == ' ')
			it1 = str.end();
		else {
			if (it1 == str.end())
				it1 = it2;

			if (it2 - it1 + 1u > max) {
				max = it2 - it1 + 1;
				mit = it1;
			}
		}
		++it2;
	}

	return string(mit, mit + max);
}

unsigned int NumWords(const char* str) {
	unsigned int count = 0;

	const char* beg = 0;
	const char* end = str;

	while (end && *end) {

		if (*end == ' ')
			beg = 0;
		else
			if (beg == 0) {
				beg = end;
				++count;
			}
		++end;
	}

	return count;
}

void TestWords() {
	cout << "Test case  1: " << LongestWordStd("") << endl;
	cout << "Test case  2: " << LongestWordStd("   1  ") << endl;
	cout << "Test case  3: " << LongestWordStd("1     ") << endl;
	cout << "Test case  4: " << LongestWordStd("   1") << endl;
	cout << "Test case  5: " << LongestWordStd("1    2   333 44") << endl;
	cout << "Test case  6: " << LongestWordStd("1    222   333 44") << endl;


	cout << "Test case  6: " << NumWords(0) << endl;
	cout << "Test case  7: " << NumWords("") << endl;
	cout << "Test case  8: " << NumWords("1") << endl;
	cout << "Test case  9: " << NumWords("   1") << endl;
	cout << "Test case 10: " << NumWords("1    2   333 44") << endl;
}

int main3() {
	TestWords();
	return 0;
}




