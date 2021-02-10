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

string printInterval(interval_t intv)
{
    return "(" + std::to_string(intv.first) + ", " + std::to_string(intv.second) + ")";
}

void testIntervals()
{
    set<interval_t> ints1{ {1, 3}, { 3, 7 }, {2, 4} };
    set<interval_t> ints2{ {-11, 2}, { 3, 17 }, {6, 10} };


    for (auto v1 : ints1) 
        for (auto v2 : ints2) 
        {
            cout << "\n " << printInterval(v1) << ", " << printInterval(v2);
            cout << "\n  overlap: " << isIntervalOverlapped(v1, v2);
            cout << "\n  merged : " << printInterval(mergeIntervals(v1, v2));
    }
}

int main10(int argc, char** argv)
{
    cout << "\n *** main-10 ***";
    //testCards();
    //testSubstringsCount();
    //testLRU();
    testIntervals();

    return 0;
}