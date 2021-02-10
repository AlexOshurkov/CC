#include "stdafx.h"
#pragma hdrstop


void testModernCPP() {

    mutex omtx;
    cout << "\n >>> testModernCPP <<<";

    int arr1[]{ 1,2,3,4,5 };


    auto calb1 = [arr1, &omtx](auto n) {
        auto eln = 0;
        for (auto it = cbegin(arr1); it != cend(arr1); ++it) {
            {
                lock_guard<mutex>  l(omtx);
                cout << "\narr (" << n << "): " << *it;
            }
            ++eln;
            this_thread::sleep_for(chrono::milliseconds(n * 100));
        }
        return eln;
    };

    auto fut1 = async(launch::async, calb1, 5);
    auto fut2 = async(launch::async, calb1, 10);

    fut1.wait();
    fut2.wait();

    cout << "\nfut1: " << fut1.get();
    cout << "\nfut2: " << fut2.get();

    map<int, string> m1{ {1, "one"}, {2, "two"} };
}
 

string longestSubStr(const string& str) 
{
    unordered_set<char> hash_set;

    auto it1 = cbegin(str);
    auto it2 = cbegin(str);
    auto it1l = it1;
    auto it2l = it2;

    while (it2 != str.cend())
    {
        if (hash_set.find(*it2) == cend(hash_set))
        {
            if (std::distance(it1, it2) > distance(it1l, it2l))
            {
                it1l = it1;
                it2l = it2;
            }

            hash_set.insert(*it2);
            ++it2;
        }
        else
        {
            hash_set.erase(*it1);
            ++it1;
        }
    }

    if (it2l != cend(str))
        ++it2l;

    return string(it1l, it2l);
}

void testLongestSubstr() {
    cout << "\n >>> testLongestSubstr <<<";
    vector<string> cases{ "", "a", "aa", "aaa", "ab", "aba", "abc", "ababc", "abcabcdabcdeabc"};

    for (const auto& v : cases) 
        cout << "\n case: " << v << " --> " << longestSubStr(v);
}

int StreamLogs(vector<string> S) {
    int sum = 0;
    unordered_map<string, vector<int>> logrecs;
    unordered_map<string, int> logtotal;

    string id_longest;
    int time_longest;

    for (const auto& sline : S)
    {
        // we don't validate string length and format, although it's required for real task
        int hh = std::stoi(sline.substr(0, 2));
        int mm = std::stoi(sline.substr(3, 2));
        int ss = std::stoi(sline.substr(6, 2));
        string id = sline.substr(9);

        int sttotal = ss + 60 * mm + 3600 * hh;
        logtotal[id] += sttotal;
        logrecs[id].push_back(sttotal);

        if (id_longest.empty() || time_longest < logtotal[id])
        {
            id_longest = id;
            time_longest = logtotal[id];
            // cout << "\n long: " << id << ", " << time_longest;
        }

        //cout << "\n " << i << ": " << hh << ", " << mm << ", " << ss << ", " << id;
    }

    int total_time = 0;
    for (const auto& logline : logrecs) {

        for (const auto logtime : logline.second)
        {
            int logprice = 0;
            if (logtime < 180) // less 3 minutes
                logprice = logtime * 4;
            else 
            {
                logprice = logtime / 60 * 225;
                logprice += logtime % 60 == 0 ? 0 : 225; // check remainder of 60 sec , ie started minute
            }

            if (logline.first == id_longest)
                logprice *= 0.5;

            total_time += logprice;
        }
    }

    return total_time;
}

void testRivian1() {
    cout << "\n >>> testRivian1 <<<";
    vector<string> ar { "00:01:25,123-45-6789", "00:03:01,122-33-4444", "00:03:00,123-45-6789" };
    cout << "\n total: " << StreamLogs(ar);
}


namespace test {

    struct date_t
    {
        int m_day = 0;
        string m_month;
        int m_year = 0;

        static int StrMonthToInt(const string& val)
        {
            static unordered_map<string, int> mvals{
                {"Jan", 1},
                {"Feb", 2},
                {"Mar", 3},
                {"Apr", 4},
                {"May", 5},
                {"Jun", 6},
                {"Jul", 7},
                {"Aug", 8},
                {"Sep", 9},
                {"Oct", 10},
                {"Nov", 11},
                {"Dec", 12}
            };

            return mvals[val];
        }

        date_t() = default;
        date_t(const string& day, const string& month, const string& year) :
            m_day (std::stoi(day)),
            m_month(month),
            m_year(std::stoi(year))
        {
        }

        bool operator < (const date_t& cdate) const
        {
            if (cdate.m_year < m_year)
                return true;
            else if (cdate.m_year == m_year)
            {
                if (StrMonthToInt(cdate.m_month) < StrMonthToInt(m_month))
                    return true;
                else if (cdate.m_month == m_month)
                    return cdate.m_day < m_day;
            }

            return false;
        }

        string to_string() const
        {
            return std::to_string(m_day) + " " + m_month + " " + std::to_string(m_year);
        }
    };

    struct file_filter_t
    {
        string user_name;
        unsigned long max_size;
        char perm;
    };

    class file_t
    {
    public:
        file_t(const string& str) // deserilize one line
        {
            std::regex regexp(" +");
            std::sregex_token_iterator it_beg(str.begin(), str.end(), regexp, -1);
            std::sregex_token_iterator it_end;
            
            m_user = *it_beg;
            m_perm = *++it_beg;
            string day = *++it_beg;
            string mon = *++it_beg;
            string year = *++it_beg;
            m_date = date_t(day, mon, year);
            m_size = std::stoul(*++it_beg);
            m_name = *++it_beg;
        }

        bool operator < (const file_t ft) const
        {
            return ft.m_date < m_date;
        }

        bool check_filter(const file_filter_t ff)
        {
            return m_user == ff.user_name && m_size < ff.max_size&& m_perm.find(ff.perm) != string::npos;
        }

        string get_user() const { return m_user; }
        string get_perm() const { return m_perm; }
        date_t get_date() const { return m_date; }
        unsigned long  get_size() const { return m_size; }
        string get_name() const { return m_name; }

    private:
        string m_user;
        string m_perm;
        date_t m_date;
        unsigned long m_size = 0;
        string m_name;
    };

    string solution(const string& str)
    {
        std::stringstream ss(str);
        std::string sline;

        set<file_t> files;
       
        file_filter_t ff{ "admin", 14 * (1 << 20), 'x' };
        while (std::getline(ss, sline, '\n')) 
        {
            file_t ft(sline);
            if (ft.check_filter(ff))
                files.emplace(ft);
        }

        return files.empty() ? "NO FILES" : files.begin()->get_date().to_string();
    }

}




void testFiles()
{
    string str = 
        "admin  -wx 29 Sep 1983        833 source.h\n"
        "admin  r-x 23 Jun 2003     854016 blockbuster.mpeg\n"
        "admin  --x 02 Jul 1997        821 delete - this.py\n"
        "admin  -w- 15 Feb 1971      23552 library.dll\n"
        "admin  --x 15 May 1979  645922816 logs.zip\n"
        "jane   --x 04 Dec 2010      93184 old - photos.rar\n"
        "jane   -w- 08 Feb 1982  681574400 important.java\n"
        "admin  rwx 26 Dec 1952   14680064 to - do - list.txt";

    string str2 = "admin  -wx 29 Sep 1983        833 source.h\nadmin  r-x 23 Jun 2003     854016 blockbuster.mpeg\nadmin  --x 02 Jul 1997        821 delete-this.py\nadmin  -w- 15 Feb 1971      23552 library.dll\nadmin  --x 15 May 1979  645922816 logs.zip\njane   --x 04 Dec 2010      93184 old-photos.rar\njane   -w- 08 Feb 1982  681574400 important.java\nadmin  rwx 26 Dec 1952   14680064 to-do-list.txt";
    cout << test::solution(str2);
}

int minCharDel(const string& str)
{
    unordered_map<int, vector<char>> chars_map;
    int chars_num[256];
    memset(chars_num, 0, sizeof(chars_num[0]) * 256);

    for (auto ch : str)
        ++chars_num[ch];

    for (int i = 0; i < 256; ++i)
        if (chars_num[i] > 0)
            chars_map[chars_num[i]].push_back(i);

    return 0;
}

void testMinCharDel()
{
    vector<string> cases{
        "aaaabbbb"
    };

    for (auto& v : cases)
        cout << "\n" << v << " --> " << minCharDel(v);
}


int binString(const string& S) {

    if (S.empty())
        return 0;

    size_t cnt = 0;

    auto it = S.begin();
    while (it != S.end() && *it == '0')
        ++it;
    
    while (it != S.end())
    {
        if (*it == '0')
            ++cnt;
        else
            cnt += 2;

        ++it;
    }

    return cnt > 0 ? cnt - 1 : 0;
}


struct base_t
{
    
    typedef set<pair<float, float>> areas_t;
    areas_t att;

    float base_len = 10;

    auto findOverlap(float pos) const
    {
        if (att.empty())
            return att.end();
        pair<float, float> new_area (pos, pos + 1.0f );
        auto it = att.lower_bound(new_area);
        
        if (it == att.end())
        {
            if (new_area.second > att.rbegin()->second)
            {


            }
        }
    }

    void attack(float pos)
    {
        
    }

    bool isOver() const
    {
        if (att.size() == 1)
            return att.begin()->first <= 0 && att.begin()->second >= base_len;

        return false;
    }
};

template<class T>
bool getSecondLargest(const vector<T>& arr, T& out_val)
{
    T v1{ numeric_limits<T>::min() };
    T v2{ numeric_limits<T>::min() };
    bool b1 = false;
    bool b2 = false;

    for (const auto& v : arr)
    {
        if (v > v2)
        {
            if (b2)
            {
                v1 = v2;
                b1 = true;
            }

            v2 = v;
            b2 = true;
        }
        else if (v > v1 && v < v2)
        {
            v1 = v;
            b1 = true;
        }
    }

    if (b1 && b2)
    {
        out_val = v1;
        return true;
    }

    return false;
}

void testGetSecondLargest()
{
    vector<vector<int>> tcases{
        {},
        {1},
        {1,1},
        {2,1},
        {3,1,2},
        {10,20,15,11,11,20,24,11,24,10}
    };

    for (auto& tcase : tcases)
    {
        cout << "\n case: ";
        for (auto& v : tcase)
            cout << v << ", ";

        int outv = numeric_limits<int>::min();
        bool r = getSecondLargest(tcase, outv);
        cout << " --> " << r << ", res: " << outv;
    }
}

void testBinString()
{
    cout << "\n solution " << binString(string(""));
    cout << "\n solution " << binString(string("0"));
    cout << "\n solution " << binString(string("000"));
    cout << "\n solution " << binString(string("0011100"));
    cout << "\n solution " << binString(string("111"));
    cout << "\n solution " << binString(string("1111010101111"));
    cout << "\n solution " << binString(string(400000, '1'));
}

struct gclass {

    gclass() {
        cout << "\ngclass::ctor";
    }
    ~gclass() {
        cout << "\ngclass::dtor";
    }
};

void printShift() {
    uint32_t v1 = 1;
    uint32_t v2 = 0x80000000;

    cout << hex;

    while (v1 && v2) {
        cout << "\nv1 = " << v1 << "; v2 = " << v2;
        v1 <<= 1;
        v2 >>= 1;
    }
}

// # -  cooment
//  sep: \n
//  

class ClassA  
{
public:
    string val;

    ClassA(const string& str) :
        val(str)
    {
        
        cout << "\n Class::ctor: ";

        
    }
};

template<class T>
class Reader
{
    istream& m_stream;
public:

    Reader(std::istream& stream) :
        m_stream(stream)
    {}

    T getNext(bool blockingRead)
    {
        if (m_stream.bad())
            throw std::exception("Nothing to read");

        char ch = 0;
        string sline; // dat

        for (int max_att = 20; max_att > 0; )
        {
            m_stream.clear();
            m_stream.get(ch); // dat --> 0

            while (ch != 0)
            {
                if (ch == '\n')
                    break;

                cout << "\n rd ch: " << ch;
                sline.push_back(ch); 

                m_stream.get(ch);

                if (m_stream.bad() || m_stream.eof())
                {
                    ch = 0;
                    break;
                }                    
            }
            if (!blockingRead)
                --max_att;

            if (ch == '\n')
                return T(sline);

            else if (m_stream.eof()) {
                m_stream.clear();
                this_thread::sleep_for(1s);
                continue;
            }

            else if (m_stream.bad())
                throw std::exception("file IO error");

        }

        throw std::exception("max att reached");

    }
};

/*
* data1\n
* data2\n
* data3\n
*/

// writer - insert 2 milliseconds
// reader - 1 milliseconds 

/*
* err: no newline found !!!
* err: no newline found !!!
* SUCCESS: ClassA created: data1
* err: no newline found !!!
* err: no newline found !!!
* SUCCESS: ClassA created: dat
* err: no newline found !!!
* err: no newline found !!!
* SUCCESS: ClassA created: a2
*/

#include <fstream>

void testStreamer()
{
    cout << "\n>>> testStreamer <<<";

    char* data = "data1\ndata2\ndata3\n";
    ofstream ofs("data.dat", ios_base::binary | fstream::trunc);

    if (ofs.bad())
    {
        cout << "\n file open error";
        return;
    }

    ifstream ifs("data.dat", ios_base::binary);

    Reader <ClassA> rd(ifs);

    thread th1([&]() {
        while (*data) {
            char ch = *data;
            ofs << ch;
            ofs.flush();
            ++data;
            this_thread::sleep_for(2s);
        }
        });

    thread th2([&]() {
        int n = 0;
        int nt = 0;

        while (n < 3 && nt < 20) {
            cout << "\n read [" << nt << "] ";
            ++nt;
            try {
                ClassA cla = rd.getNext(false);
                cout << "\nRead object: " << cla.val;
                ++n;
            }
            catch (const std::exception& e) {
                cout << "\nexception: " << e.what();
            }

            this_thread::sleep_for(1s);
        }

        });

    th1.join();
    th2.join();

}
struct tb_t {
    virtual void f() {
        cout << "\ntb_t::f";
    }

    void p1() { f(); };
};

struct tch_t : public tb_t {
    void f() {
        cout << "\ntch_t::f";
    }
    void p2() { f(); };

};



int main9(int argc, char** argv)
{
    cout << "\n *** main-9 ***";
    //testModernCPP();
    //testLongestSubstr();
    //testRivian1();
    //testFiles();
    //testMinCharDel();
    //testGetSecondLargest();
    //printShift();

    //testStreamer();


    return 0;
}
