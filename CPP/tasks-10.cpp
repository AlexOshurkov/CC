#include "stdafx.h"
#pragma hdrstop

class card_t
{
public:
    typedef pair<string, string> prop_t;
    typedef unordered_map<prop_t::first_type, prop_t::second_type> props_t;

    card_t(const std::initializer_list<prop_t>& props)
    {
        for (const auto& prop : props)
            _props.insert(prop);
    }

    const props_t& getProps() const
    {
        return _props;
    }


private:
    props_t _props;
};

bool isCardSet(const vector<card_t>& cards)
{
    if (cards.empty())
        return false;

    if (cards.size() == 1)

        return true;

    size_t pvsize = 0;

    for (const auto& prop : cards[0].getProps())
    {
        unordered_set<string> vals;

        for (const auto& card : cards)
        {
            const auto& props = card.getProps();

            if (props.size() != cards[0].getProps().size())
                return false;

            card_t::props_t::const_iterator it = props.find(prop.first);

            if (it == props.end())
                return false;

            vals.insert(it->second);
        }

        if (vals.size() != 1 && vals.size() != cards.size())
            return false;

        if (pvsize == 0)
            pvsize = vals.size();

        else if (vals.size() != pvsize)
            return false;
    }

    return true;
}


void testCards() {

    card_t cd1 {
        {"color", "red"},
        {"count", "1"}
    };

    card_t cd2 {
        {"color", "green"},
        {"count", "2"}
    };

    card_t cd3 {
        {"color", "red"},
        {"count", "2"}
    };

    cout << "\n case 1: " << isCardSet({ cd1, cd2 });
    cout << "\n case 2: " << isCardSet({ cd2, cd3 });
}

int getSubstringsCount(const string& str, const char* t) {

    if (str.empty() || t == nullptr || *t == 0)
        return -1;

    int tlen = std::strlen(t);
    int numt = 0;
    int chmatches = 0;

    for (const auto ch : str) {

        if (ch == t[chmatches]) {
            ++chmatches;
        }
        else
            chmatches = 0;

        if (chmatches == tlen) {
            ++numt;
            chmatches = 0;
        }
    }

    return numt;
}

void testSubstringsCount() {

    string s{ "abcdeabcdefgabefgugubebea" };
    vector <const char*> templ{ 0, "", "sdf", "a", "ab", "abc", "de" };
    cout << "\n testSubstringsCount";
    cout << "\n counting substrings in string: " << s;
 
    for (const auto pt : templ) 
        cout << "\n  substring: \"" << (pt ? pt : "null") << "\" found " << getSubstringsCount(s, pt) << " times";
  
}

template <typename T>
class LRUCache {
    typedef list<T> list_t;
    typedef unordered_map<T, typename list_t::iterator> map_t;
    list_t m_list;
    map_t m_vals;
    size_t m_maxel = 0;

public:

    LRUCache(size_t maxel) :
        m_maxel(maxel)
    {}

    void put(T val) {
        map_t::const_iterator it = m_vals.find(val);
        
        if (it == m_vals.end()) {
            if (m_vals.size() >= m_maxel) {
                m_vals.erase(*m_list.rbegin());
                m_list.pop_back();
            }

            m_list.push_front(val);
            m_vals[val] = m_list.begin();
        }
        else {
            if (val != *m_list.begin()) {
                m_list.erase(it->second);
                m_list.push_front(val);
                m_vals[val] = m_list.begin();
            }
        }
    }

    void print() const {
        for (const auto& v : m_list)
            cout << v << " ";
    }
};

void testLRU() {
    vector<const char*> cases{ "", "abc", "abca", "abbccac" };

    for (const auto& vcase : cases) {
        cout << "\n case: " << vcase;

        LRUCache<char> lcache{ 3 };
        for (auto& ch : string(vcase))
            lcache.put(ch);

        cout << "\n cache: ";
        lcache.print();
        cout << "\n";
    }
}

typedef pair<int, int> interval_t;
typedef set<interval_t> intervals_t;

bool isIntervalOverlapped(interval_t int1, interval_t int2)
{
    if (int2.first < int1.first)
        swap(int1, int2);

    return int1.second >= int2.first;
}

interval_t mergeIntervals(interval_t int1, interval_t int2)
{
    if (int2.first < int1.first)
        swap(int1, int2);
    
    if (int1.second < int2.first)
        return interval_t(0, 0);

    return interval_t(int1.first, int1.second > int2.second ? int1.second : int2.second);
}

bool isIntValid(const interval_t& intv)
{
    return intv.first < intv.second;
}

string printInterval(interval_t intv)
{
    return "(" + std::to_string(intv.first) + "," + std::to_string(intv.second) + ")";
}

string printIntervals(const intervals_t& ints)
{
    stringstream ss;

    ss << "[";
    for (const auto& v : ints)
        ss << (v == *ints.begin() ? "" : ", ") << printInterval(v);
    ss << "]";

    return ss.str();
}

intervals_t mergeIntervals1(const intervals_t ints, interval_t intv)
{
    intervals_t nints;

    for (const auto& v : ints)
    {
        if (isIntValid(intv) && isIntervalOverlapped(v, intv)) {
            nints.insert(mergeIntervals(v, intv));
            intv = interval_t{ 0,0 };
            continue;
        }
        else {
            if (nints.empty() || !isIntervalOverlapped(*nints.rbegin(), v))
                nints.insert(v);
            else {
                interval_t lint = *(--nints.end());
                nints.erase(--nints.end());
                nints.insert(mergeIntervals(v, lint));
            }
        }
    }

    return nints;
 }

void testIntervals()
{
    intervals_t ints1{ {0,2}, {5,7}, {9, 11} };
    cout << "\n Base interval: " << printIntervals(ints1);

    for (int i1 = -1, i2 = -1; i1 < 12 || i2 < 12; ) {
        if (i2 < 12)
            ++i2;
        else
            ++i1;

        interval_t newint{ i1, i2 };
        cout << "\n    Interval: " << printInterval(newint);
        cout << "\n    Merged interval: " << printIntervals(mergeIntervals1(ints1, newint));
    }
}

size_t calcFiboR(size_t n) {
    
    static size_t ncache[100];

    if (n <= 1)
        return n;

    if (ncache[n] == 0)
        ncache[n] = calcFiboR(n - 1) + calcFiboR(n - 2);

    return ncache[n];
}

size_t calcFibo(size_t n) {

    size_t a = 0, b = 1;

    while (n > 0) {
--n;
size_t ta = a + b;
a = b;
b = ta;
    }

    return a;
}

void testFiboR() {

    for (size_t i = 0; i < 60; ++i)
        cout << "\n  Fibo [" << i << "]: rec: " << calcFiboR(i) << ", iter: " << calcFibo(i);

}

typedef unordered_map<float, int> valmap_t;

// codility
int solution(vector<int>& X, vector<int>& Y) {
    // write your code in C++14 (g++ 6.2.0)

    valmap_t vm; // map of values and occurences
    int maxocc = 0; // current max occurrence

    vector<int>::const_iterator itx = X.begin();
    vector<int>::const_iterator ity = Y.begin();

    while (itx != X.end()) {

        float newval = float(*itx) / float(*ity);
        valmap_t::iterator mit = vm.find(newval);
        if (mit == vm.end()) {
            vm.insert(pair<float, int>(newval, 1));
            if (maxocc == 0)
                maxocc = 1;
        }
        else {
            mit->second++;
            if (maxocc < mit->second)
                maxocc = mit->second;
        }

        ++itx;
        ++ity;
    }
    return maxocc;
}

//codility
int solution2(vector<int>& A) {
    // write your code in C++14 (g++ 6.2.0)
    int bitcalc[sizeof(int) * 8]; // assume 32bit integers, 32 should be something like sizeof(int) * 8 for platform independency 

    std::memset(bitcalc, 0, sizeof(bitcalc));

    int maxsubs = 0;
    for (auto v : A) {
        int bitnum = 0;
        while (v > 0) {
            if (v & 1)
                ++bitcalc[bitnum];

            if (bitcalc[bitnum] > maxsubs)
                maxsubs = bitcalc[bitnum];
            ++bitnum;

            v >>= 1;
        }
    }
    return maxsubs;
}

// print all substrings if any words have substitution
typedef list<string> strq_t;
typedef unordered_map<string, strq_t> wordmap_t;

void printAllWordsImpl(strq_t pref, strq_t postf, const wordmap_t& wordmap);
void printAllWords(string str, wordmap_t& wordmap) {
    strq_t pref;
    strq_t postf;
    stringstream ss(str);

    while (!ss.eof()) {
        string sval;
        ss >> sval;
        postf.push_back(sval);
    }

    printAllWordsImpl(pref, postf, wordmap);
}

void printAllWordsImpl(strq_t pref, strq_t postf, const wordmap_t& wordmap) {

    if (postf.empty()) {
        cout << "\n";

        for (const auto& prefv : pref)
            cout << prefv << " ";
    } 
    else {

        wordmap_t::const_iterator wmit = wordmap.find(postf.front());
        if (wmit == wordmap.end()) {
            pref.push_back(postf.front());
            postf.pop_front();
            printAllWordsImpl(pref, postf, wordmap);
        }
        else {
            postf.pop_front();
            for (const auto& rword : wmit->second) {
                pref.push_back(rword);
                printAllWordsImpl(pref, postf, wordmap);
                pref.pop_back();
            }
        }
    }
}

void testPrintAllWords() {
    wordmap_t wordmap{ {"cc", {"cc1", "cc2"} }, {"dd", {"dd1", "dd2"}} };
    printAllWords("aa bb cc dd ee cc", wordmap);
}


unordered_set<string> permcheck;

void printPermutationImpl(string pref, string postf) {

    if (postf.empty()) {
        if (permcheck.find(pref) == permcheck.end())
            permcheck.insert(pref);
        else
            throw std::exception(("The permutation is already exist: " + pref).c_str());
        cout << "\n" << pref;

    }
    else {
        for (size_t pos = 0; pos < postf.size(); ++pos) {

            string npostf = postf;
            printPermutationImpl(pref + postf[pos], npostf.erase(pos, 1));
        }
    }

}
void printPermutations(string str) {
    permcheck.clear();
    printPermutationImpl("", str);
    cout << "\nNumber of unique perm: " << permcheck.size();
}

void testPrintPermutations() {
    string str = "1234";
    printPermutations(str);
}

int main10(int argc, char** argv)
{
    cout << "\n *** main-10 ***";

    //testCards();
    //testSubstringsCount();
    //testLRU();
    //testIntervals();
    //testFiboR();
    //testPrintAllWords();
    //testPrintPermutations();

    return 0;
}